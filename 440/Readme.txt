Krish Patel V00996444

To compile the programs, firstly start off by running the server. You can do this by running this command: 

	"python ChatServer.py <port>" 

The server is created on IP address 10.0.0.1, with the port number being whatever is passed in the command line
To close the server, press "CTRL+C" 

To establish a connection to the server as a user, run this command: 
 
	"python ChatClient.py <hostname> <port> <nickname> <clientID>" 

The hostname should be the same as the server (10.0.0.1), as well as the port number. The program will detect if there are duplicate nicknames, to ensure that each user is unique. 
To disconnect from the server, type "disconnect"
