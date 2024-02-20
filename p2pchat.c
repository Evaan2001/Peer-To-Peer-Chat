#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "linked_list.c"
#include "socket.h"
#include "ui.h"
#include "message.h"

// Keep the username in a global so we can access it from the callback
const char* username;

// Store the peers current server is connected to
user_list_t user_list; 

// Lock for user_list
pthread_mutex_t user_lock = PTHREAD_MUTEX_INITIALIZER;

// Thread function that constantly checks to see if a given peer has sent a message
void* client_receive_message(void* args){

  // keep track of messages sent by the below client
  int client_socket_fd = *((int *) args);
  char * sender_username = NULL;
  char * message = NULL;

  while(true){
    // receive the username then message
    sender_username = receive_message(client_socket_fd);
    if(sender_username == NULL){
      ui_display("ERROR", "Couldn't receive message (client_receive_message.1)");
      delete_user(&user_list, client_socket_fd);
      break;
    } else {
      message = receive_message(client_socket_fd);
      if(message == NULL){
        ui_display("ERROR", "Couldn't receive message (client_receive_message.2)");
        continue;
      }
    }

    // remove the client if the message is quit
    if(strcmp(message, ":quit") == 0 || strcmp(message, ":q") == 0){
      pthread_mutex_lock(&user_lock);
      delete_user(&user_list, client_socket_fd);
      pthread_mutex_unlock(&user_lock);
      break;
    }

    // display on current screen
    ui_display(sender_username, message);

    // Send this message to every peer in our list except client_socket_fd
    node_t* current_node = user_list.head;

    while(current_node != NULL){
      if(current_node->value != client_socket_fd){

        // send the username then the message
        int rc = send_message(current_node->value, (char *)sender_username);
        if (rc == -1) {
          ui_display("ERROR", "Couldn't send message (client_receive_message.3)");
          delete_user(&user_list, current_node->value);
          break;
        } else {
          rc = send_message(current_node->value, (char *)message);
          if (rc == -1) {
            ui_display("ERROR", "Couldn't send message (client_receive_message.4)");
          } 
        }
      } 
      current_node = current_node->next;
    }
  }

  return NULL;
}


// Thread function that continously checks for connections
void* connect_peer(void* args){
  // Wait for a client to connect
  int server_socket_fd = *((int *) args);
  while(true){
    int client_socket_fd = server_socket_accept(server_socket_fd);
    if (client_socket_fd == -1) {
      ui_display("ERROR", "Couldn't accept connection (connect_peer.1)");
      continue;
    }

    // Reserve space to pass the file descriptor to the thread
    int* client_socket_fd_ptr = malloc(sizeof(int));
    *client_socket_fd_ptr = client_socket_fd;

    // Add client's socket_fd to our user list
    pthread_mutex_lock(&user_lock);
    list_push(&user_list, client_socket_fd);
    pthread_mutex_unlock(&user_lock);

    // create a thread for each accepted client
    pthread_t client_thread; // thread to receive messages from peers

    if (pthread_create(&client_thread, NULL, client_receive_message, client_socket_fd_ptr)) {
      perror("failed to create thread");
      exit(EXIT_FAILURE);
    }
  }
}


// This function is run whenever the user hits enter after typing a message
void input_callback(const char* message) {

  if (strcmp(message, ":quit") == 0 || strcmp(message, ":q") == 0) {
    // loop through our linked list to send quit to connected peers
    node_t* current_node = user_list.head;

    while(current_node != NULL){
      // send the username then the message
      int rc = send_message(current_node->value, (char *)username);
      if (rc == -1) {
        ui_display("ERROR", "Couldn't send quit message (input_callback.1)");
      } else {
        send_message(current_node->value, (char *)message);
        if (rc == -1) {
          ui_display("ERROR", "Couldn't send quit message (input_callback.2)");
        }
      }
      current_node = current_node->next;
    }

    // End the program
    ui_exit();

  } else {
    ui_display(username, message);

    // loop through our linked list to send the typed message to connected peers
    node_t* current_node = user_list.head;

    while(current_node != NULL){
      // send the username then the message
      int rc = send_message(current_node->value, (char *)username);
      if (rc == -1) {
        ui_display("ERROR", "Couldn't send message (input_callback.3)");
      } else {
        send_message(current_node->value, (char *)message);
        if (rc == -1) {
          ui_display("ERROR", "Couldn't send message (input_callback.)");
          exit(EXIT_FAILURE);
        }
      }
      current_node = current_node->next;
    }
  }
}

int main(int argc, char** argv) {
  // Make sure the arguments include a username
  if (argc != 2 && argc != 4) {
    fprintf(stderr, "Usage: %s <username> [<peer> <port number>]\n", argv[0]);
    exit(1);
  }

  // Save the username in a global
  username = argv[1];

  list_init(&user_list);
  // Set up a server socket to accept incoming connections

  // Open a server socket
  unsigned short port = 0;
  int server_socket_fd = server_socket_open(&port);
  if (server_socket_fd == -1) {
    perror("Server socket was not opened");
    exit(EXIT_FAILURE);
  }

  // Change int port to a char port_ch to be used with ui_display
  char port_ch[6];
  int rc = sprintf(port_ch, "%u", port);
  if(rc < 0){
    perror("failed to snprintf port");
    exit(EXIT_FAILURE);
  }

  // Start listening for connections, with a maximum of one queued connection
  if (listen(server_socket_fd, 1)) {
    perror("listen failed");
    exit(EXIT_FAILURE);
  }

  pthread_t connect_thread;

  if (pthread_create(&connect_thread, NULL, connect_peer, &server_socket_fd)) {
    perror("failed to create thread");
    exit(EXIT_FAILURE);
  }

  // Did the user specify a peer we should connect to?
  if (argc == 4) {
    // Unpack arguments
    char* peer_hostname = argv[2];
    unsigned short peer_port = atoi(argv[3]);

    // Connect to another peer in the chat network
    int socket_fd = socket_connect(peer_hostname, peer_port);
    if (socket_fd == -1) {
      perror("Failed to connect");
      exit(EXIT_FAILURE);
    }

    // Add client's socket_fd to our user list
    pthread_mutex_lock(&user_lock);
    list_push(&user_list, socket_fd);
    pthread_mutex_unlock(&user_lock);

    // create a thread for each accepted client
    pthread_t server_thread; // thread to receive messages from peers

    if (pthread_create(&server_thread, NULL, client_receive_message, &socket_fd)) {
      perror("failed to create thread");
      exit(EXIT_FAILURE);
    }

  }

  // Set up the user interface. The input_callback function will be called
  // each time the user hits enter to send a message.
  ui_init(input_callback);

  // Once the UI is running, you can use it to display log messages
  ui_display("SERVER", port_ch);

  // Run the UI loop. This function only returns once we call ui_stop() somewhere in the program.
  ui_run();

  return 0;
}
