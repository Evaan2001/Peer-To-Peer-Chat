<p  align="center">
<img  src="https://github.com/Evaan2001/Images_For_ReadMe/blob/main/P2PChat.png"
width = "900"/>

</p>
<h3 align="center">
Here's my implementation of a peer-to-peer (P2P) chat network – networks that don't require a central server. Try it out!
</h3>

<div align="center">

In the early days of networking, it was a common practice to connect users through 1 central server. However, if that central server was compromised (say by cyber-security attacks) or if it needed to be temporarily paused (maybe for hardware maintenance/upgrades), the entire network would have to shut down. That's when P2P networks came where each client (user) serves as an independent server, thus eliminating the need for and minimizing the risks associated with just 1 central server
</div>

<h2 align="center"> 
Instructions / Getting Started
</h2>


##### Things to note:

1. This chat network only works across a LAN (Local Area Network) system; no internet capabilities yet! If you want to test this out and don't have a LAN set up, you can start multiple terminal windows in your device and each of those terminal windows can serve as 1 user (more on this below).
2. The basic syntax for joining as a client is `./p2pchat <username> [<peer> <port number>]`. If your device is a member of a LAN system, the `peer` value would be your device's LAN ID/name. If you are starting multiple terminal windows in your non-LAN device, your `peer` will be `localhost`.

##### How to run:

1. First open a terminal window and run `./p2pchat start`. This will initialize the network and display a server port number. Note it down!
2. Now open another terminal window.
3. Suppose you want your username to be SharpCactus. You can join the network by running `./p2pchat SharpCactus localhost <port number>`, where `port number` is the server port number displayed in the first terminal number
4. Subsequent users can also join the network from their own terminal windows with one caveat – their usernames have to be unique.


<h2 align="center"> 
Files
</h2>

<p  align="center">
Here's what you'll find –
</p>

1. *Demo_Images* – A list of images I used to test my algorithm 
2. *app-venv* – The virtual environment I used to develop this app
3. *functions.py* – A file that has a bunch of helper functions I used frequently (including my string processing functions for OCR'ed text)
4. *images_processed.txt* – A text file that records how many images my web-app has processed in the last week
5. *packages.txt* – list of Linux dependencies outside the Python environment to be installed by Streamlit using apt-get for app deployment
6. *requirements.txt* – list of python packages to be installed by Streamlit for app deployment
7. *streamlit_app.py* – python script that manages the front-end of the app and calls the relevant algorithm/function contained in *functions.py*
