<p  align="center">
<img  src="https://github.com/Evaan2001/Images_For_ReadMe/blob/main/P2PChat.png"
width = "900"/>

</p>
<h3 align="center">
Here's my implementation of a peer-to-peer (P2P) chat network – networks that don't require a central server. Try it out!
</h3>

<div align="center">

In the early days of networking, it was a common practice to connect users through 1 central server. However, if that central server was compromised (say by cyber-security attacks) or if it needed to be temporarily paused (maybe for hardware maintenance/upgrades), the entire network would have to shut down. That's when P2P networks came where each client (user) serves as an independent server, thus eliminating the need for and minimizing the risks associated with just 1 central server. For some FAQs on the P2P network design, check out the [Questions.txt](https://github.com/Evaan2001/Peer-To-Peer-Chat/blob/main/QUESTIONS.txt) file in this repo.
</div>

<h2 align="center"> 
Instructions / Getting Started
</h2>


##### Things to note:

1. This chat network only works on 1 device or across a LAN (Local Area Network) setup; no internet capabilities yet! If you want to test this out and don't have a LAN setup, you can start multiple terminal windows in your device and each of those terminal windows can serve as 1 user (more on this below).
2. Every user is a client and a network, and each user's server is connected to each other user's network.
3. Whenever any server is connected, we get a server port number. Because each user is a network, we will get a unique server port number whenever we create a user.
4. The basic syntax for joining as a client is `./p2pchat <username> <peer> <port number>`. If your device is a member of a LAN system, the `peer` value would be your device's LAN ID/name. If you are starting multiple terminal windows in 1 device, your `peer` will be `localhost` and `<port number>` can be any of the server port numbers you got when creating the users.

##### How to run:

1. First open a terminal window.
2. Run `./p2pchat <username1>` and substitute username1 with whatever usernmae you want. This creates user-1's client and server (remember each user is a network client & server.)
3. The UI changes and displays a server port number. Note it down!
4. Now open another terminal window. We will create user-2 and connect it to user-1's existing network
5. Suppose you want your new username to be SharpCactus. You can join user-1's network by running `./p2pchat SharpCactus localhost <port number>`, where `port number` is the server port number displayed in the first terminal number
6. You can now begin chatting
7. Subsequent users can also join the network from their own terminal windows by `./p2pchat new-username localhost <port number>` where <>
8. To exit, type `:quit` or `:q`. 


<h2 align="center"> 
Files
</h2>

<p  align="center">
Here's what you'll find –
</p>

1. *p2pchat* – This is the final executable – the final compiled program – that you can conveniently run from your terminal. If you see permission errors, run `make clean` to remove the current `./p2pchat`, and recompile the code by running `make all`. This will create a new `p2pchat` executable and can run this.
2. *p2pchat.c* – contains uses of all of the user interface functions such as connecting to servers, sending/receiving messages, etc.
3. *ui.c* – The functions that build and update our user interface are declared in ui.c.
4. *ui.h* – Header file for ui.c.
5. *socket.h* – header file in POSIX standards that provides declarations for network socket operations (listening, opening, and closing)
6. *message.c* – functions that facilitate message exchange between client and server by reading and sending messages with a prefixed length, ensuring agreement on message format.
7. *message.h* – header for message.c
8. *linked_list.c* – My implementation of a linked-list.
9. *Makefile* – Makefile for this repository. 
