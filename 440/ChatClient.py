import socket
import sys
import threading
import json
from datetime import datetime

args = sys.argv

## This function validates whether the passed arguments from the command
## line are correct or not, returning an error and promptly exiting if not
def validate_args(args):
    if len(args) != 5:
        print("Usage: ChatClient.py <hostname/ip> <port> <nickname> <client_id>")
        exit(1)

    hostname = args[1] 
    try: 
        socket.inet_aton(hostname) 
    except socket.error: 
        try: 
            hostname = socket.gethostbyname(hostname)
        except socket.gaierror:
            print("ERR - arg 1") 
            exit(1)

    port = int(args[2])
    try: 
        if port < 1 or port > 65535:
            raise ValueError
    except ValueError:
        print("ERR - arg 2")
        exit(1)

    nickname = args[3]
    if not nickname:
        print("ERR - arg 3")
        exit(1)

    client_id = args[4]
    if not client_id:
        print("ERR - arg 4")
        exit(1)

    return hostname, port, nickname, client_id    

## Class with the entire chat client, handling all the functions required to
## successfully run and communicate with the server and other users
class ChatClient: 
    ## Constructor class to provide each user with a unique identifier
    def __init__(self, hostname, port, nickname, client_id):
        ## Parameters required to make the selection
        self.hostname = hostname
        self.port = port
        self.nickname = nickname
        self.client_id = client_id

        ## Get the times for when the connection is established
        self.current_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        self.start_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

        ## Counters for the size and number of messages sent and received
        self.msgrecv = 0
        self.msgsent = 0
        self.charrecv = 0
        self.charsent = 0

    ## Function that establishes connection with the server handling the threads and sockets, and with 
    ## successful connection, calls the send_messages function which allows the user to send messages
    def connect_to_server(self): 
        try: 
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.socket.connect((self.hostname, self.port))

            print(f"ChatClient started with server IP: {self.hostname}, port: {self.port}, nickname: {self.nickname}, client ID: {self.client_id}, Date/Time: {self.current_time}")
            self.validate_nickname()

            threading.Thread(target = self.receive_messages, daemon = True).start()

            self.send_messages()
        except Exception as e: 
            print("ERR - arg ", e)

    ## Function to check whether the nickname passed through the command line is already being used
    def validate_nickname(self): 
        validation_message = {
            "type": "nickname",
            "nickname": self.nickname,
            "clientID": self.client_id,
            "timestamp": self.current_time
        }

        self.socket.sendall(json.dumps(validation_message).encode('utf-8'))
        response_from_server = json.loads(self.socket.recv(1024).decode('utf-8'))

        if response_from_server.get("type") == "error": 
            print(response_from_server) 
            sys.exit() 
        elif response_from_server.get("type") == "accept":
            pass

    ## Function which allows the user to receive messages from other users with the server
    ## being a midpoint, received as a .json file which is decoded with information that
    ## needs to be validated to successfully receive it client-side
    def receive_messages(self): 
        while True: 
            try: 
                server_message = self.socket.recv(1024).decode('utf-8')

                if not server_message: 
                    break

                json_file = json.loads(server_message)

                if json_file["type"] == "broadcast": 
                    nickname = json_file.get("nickname")
                    message_time = json_file.get("timestamp")
                    message = json_file.get("message")

                    if nickname and message_time and message:
                        print(f"{message_time} :: {nickname}: {message}")
                        self.msgrecv = self.msgrecv + 1
                        self.charrecv = self.charrecv + len(message)
                    else: 
                        print("Received message format is incorrect:", json_file)
                else:
                    print(server_message)
            except KeyboardInterrupt: 
                print("\nExiting chat.")
                self.socket.close()
                break 

    ## Handles the sending of messages, as well as the disconnect option, allowing
    ## the user to send messages to the server to be broadcasted and received
    ## by other users that are connected and disconnect by closing the socket
    ## and maintaining the thread for the server 
    def send_messages(self): 
        print("Enter message: \n")
        while True:
            try: 
                message = input() 
                if message == "disconnect":
                    self.disconnect_from_server() 
                    end_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                    print(f"Summary: start: {self.start_time}, end: {end_time}, msg sent:{self.msgsent}, msg rcv:{self.msgrecv}, char sent:{self.charsent}, char rcv:{self.charrecv}")
                    sys.exit(0) 
                else:
                    message = {
                        "type": "message",
                        "nickname": self.nickname,
                        "message": message,
                        "timestamp": self.current_time
                    }

                    self.socket.sendall(json.dumps(message).encode('utf-8'))
                    self.msgsent = self.msgsent + 1
                    self.charsent = self.charsent + len(message)
            except Exception as e:
                print("Error sending message:", e)
                self.socket.close()

    ## Sends the disconnect message to the server for it to successfully handle
    ## the disconnect request
    def disconnect_from_server(self):
        disconnect_message = {
            "type" : "disconnect",
            "nickname": self.nickname,
            "clientID": self.client_id
        }

        self.socket.send(json.dumps(disconnect_message).encode('utf-8'))
        self.socket.close()

def main(): 
    ## Call validate function to make sure passed parameters are valid
    hostname, port, nickname, client_id = validate_args(args)
    
    ## Start the server with the parameters
    client = ChatClient(hostname, port, nickname, client_id)
    client.connect_to_server()
    
if __name__ == "__main__":
    main()

