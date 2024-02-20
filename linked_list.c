#include <stdio.h>
#include <stdlib.h>
#include "ui.h"

#define LIST_EMPTY -1

typedef struct node {
  int value;
  struct node* next;
} node_t;

typedef struct user_list {
  node_t* head;
} user_list_t;

void list_init(user_list_t* list) {
  list->head = NULL;
}

// Insert a node at the top of the list 
// (the top position is irrelevant as we can add a node wherever)
void list_push(user_list_t* list, int value) {
  node_t* new_node = malloc(sizeof(node_t));
  new_node->value = value;
  new_node->next = list->head;
  list->head = new_node;
}

// Removes the user with client_socket_fd from list
int delete_user(user_list_t* list, int client_socket_fd) {

    // we don't have to check if the list is empty
    // as we need a user to call delete_user.
    int deleted_client_fd = -1;
  
    if(list->head->next == NULL){ // if we have a singleton list
        if(list->head->value == client_socket_fd){
            deleted_client_fd = list->head->value;
            free(list->head);
            list->head = NULL;
        }
        return deleted_client_fd;
    }

    node_t* previous_node = list->head;
    node_t* current_node = previous_node->next;

    // if the first node is the one to be removed
    if(previous_node->value == client_socket_fd){
      deleted_client_fd = previous_node->value;
      list->head = current_node;
      free(previous_node);
      return deleted_client_fd;
    }

    // check the rest of the list
    while(current_node != NULL){
        if(current_node->value == client_socket_fd){
            deleted_client_fd = current_node->value;
            previous_node->next = current_node->next;
            free(current_node);
            break;
        }
        previous_node = previous_node->next;
        current_node = current_node->next;
    }
    
    return deleted_client_fd;
}
