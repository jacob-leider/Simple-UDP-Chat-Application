# Simple-UDP-Chat-Application

A simple UDP client-server chat application written in c. This program is built to run on UNIX-like operating systems (linux, macOS, ...).


## Downloading

****Clone From github:**** &nbsp;&nbsp; $ git clone https://github.com/jacob-leider/Simple-UDP-Chat-Application.git


## Compilation

To compile the server and the client code, submit the following two commands into a UNIX shell:

****Server:**** &nbsp;&nbsp; $ cc chat_server -o server

****Client:**** &nbsp;&nbsp; $ cc chat_client -o client


## Running

In any UNIX environment, run a server by specifying a port for the server to run on. To run a client, specify the IP address of the server as well as the port. For more detail on the formatting of command line arguments, see the "Command Line Arguments" section.


****Running the Server:**** &nbsp;&nbsp; $ ./server \<PORT\>

****Running a Client:**** &nbsp;&nbsp; $ ./client \<SERVER-IP\> \<PORT\>


## Usage

Once a client is running, simply type a message followed by [RETURN]. The message will be displayed to all active clients preceded by the sender's IP address and port number. Kill the process running the client to exit the program.


## Command Line Arguments

****PORT:**** It is suggested to run the server on a port greater than or equal to 1024, as ports 0-1023 are "privilaged" in the sense that they are reserved for common TCP/IP applications.

****SERVER-IP:**** The server's IP address should be specified in standard dotted-decimal format "xxx.xxx.xxx.xxx".








