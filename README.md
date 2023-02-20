# Simple-UDP-Chat-Application

A simple UDP client-server chat application written in c. This program is built to run on UNIX-like operating systems (linux, macOS, ...).


## Downloading

****Clone From github:**** &nbsp;&nbsp; $ git clone https://github.com/jacob-leider/Simple-UDP-Chat-Application.git


## Compilation

To compile the server and the client code, submit the following two commands into a UNIX shell:

<centered>$ cc chat_server -o server</centered>

<p style="text-align: center;">$ cc chat_client -o client</p>

****Server:**** &nbsp;&nbsp; $ cc chat_server -o server

****Client:**** &nbsp;&nbsp; $ cc chat_client -o client


## Running

In any UNIX environment, run a server by specifying a port for the server to run on. To run a client, specify the IP address of the server as well as the port.


****Running the Server:**** &nbsp;&nbsp; $ ./server \<PORT\>

****Running a Client:**** &nbsp;&nbsp; $ ./client \<SERVER-IP\> \<PORT\>


## Command Line Arguments

****PORT:**** It is suggested to run the server on a port greater than or equal to 1024, as ports 0-1023 are "privilaged" in the sense that they are reserved for common TCP/IP applications.

****SERVER-IP:**** The server's IP address should be specified in standard dotted-decimal format

<p style="text-align: center;">xxx.xxx.xxx.xxx</p>








