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
 
<p  align="center">

`./p2pchat start`
</p>

`./p2pchat start`


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
