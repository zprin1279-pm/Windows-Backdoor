# Windows Backdoor
A Hidden and Undetectable Remote Access Tool written in C++ and Server in Python3

This program utilizes the standard winsock library for sending and receiving data back and forth between the server and client. The server can manage multiple connections at once with the use of multi-threading having an easy time switching to other remote machines simply in order to control it from a command line view.
<br/><br/>
Constants in Client Program:
- <b>timeout</b>: Client doesn't receive any data within a certain time period, ultimately restarting the program to retry connecting to the server.

# Client Requirements
-  Operating System: Windows
-  Compiler: C++ MinGW 64-Bit

# View
![](images/connection_commands.png)<br/>
![](images/commands.png)<br/>
![](images/clients.png)<br/>
![](images/console.png)

# Usage
- Run the 'server.py' file on your own machine you would like to control the remote client from.
- Run the compiled 'backdoor.exe' file (backdoor.cpp) on your targets machine with the specified server IP Address to establish a connection on an unoccupied port.

# Compile C++ Program
- g++ backdoor.cpp -mwindows -o backdoor -lws2_32 -lstrmiids -lole32 -loleaut32 -static-libgcc -static-libstdc++ -static

# Contributing
- Feel free to submit any possible bugs as I'll be glad to respond to anyone and help with whatever's needed to help fix and improve this program.

# Disclaimer
- This program is for educational purposes only! Use at your own risk.
