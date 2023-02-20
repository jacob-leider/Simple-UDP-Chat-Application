# Simple-UDP-Chat-Application

A simple UDP client-server chat application written in c. This program is built to run on UNIX-like operating systems (linux, macOS, ...).

## Compilation

****Server:**** &nbsp;&nbsp; $ cc chat_server -o server

****Client:**** &nbsp;&nbsp; $ cc chat_client -o client

## Running

In any UNIX environment, run a server by specifying a port for the server to run on. To run a client, specify the IP address of the server as well as the port.


****Running the Server:**** &nbsp;&nbsp; $ ./server \<PORT\>

****Running a Client:**** &nbsp;&nbsp; $ ./client \<SERVER-IP\> \<PORT\>




