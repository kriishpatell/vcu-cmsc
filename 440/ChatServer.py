import socket
import sys
import threading
import json
from datetime import datetime

args = sys.argv
current_users = []

## This function validates whether the passed arguments from the command
## line are correct or not, returning an error and promptly exiting if not
def validate_args(args):
    if len(args) != 2:
        print("Usage: ChatServer.py <port>")
        exit(1)

    port = int(args[1])
    try: 
        if port < 1 or port > 65535:
            raise ValueError
    except ValueError:
        print("ERR - arg 1")
        exit(1)

    return port

## Class with the entire chat server, handling users that attempt to connect
## with the server. Also handles messages received from users and communicates
## them with other connected users
class ChatServer:
    ## Constructor to initialize the values for the server
    def __init__(self, hostname, port):
        self.hostname = hostname
        self.port = port
        self.server_socket = None
        self.start_server() 

    ## Initializes the server based off IP address and port number
    def start_server(self):
        try: 
            self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.server_socket.bind((self.hostname, self.port))
            self.server_socket.listen(5) 

            print(f"ChatServer started with server IP: {self.hostname}, port: {self.port} ...\n")
            
            self.accept_connection()
        except Exception as e:
            print("ERR: cannot create ChatSever socket using port number", self.port)

    ## Accepts connections from users based off client socket
    def accept_connection(self):
        while True: 
            client_socket, _ = self.server_socket.accept() 
            threading.Thread(target=self.accept_user, args=(client_socket,)).start() 

    ## Handles whether the user can successfully connect to the server based on parameters, 
    ## for example, reused nicknames. If successful, display connection status. 
    def accept_user(self, socket):
        try: 
            while True: 
                client_message = socket.recv(2048).decode('utf-8')
                if not client_message:
                    break

                message = json.loads(client_message) 
                action = message["type"]
                current_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

                if action == "nickname":
                    nickname = message["nickname"]
                    client_id = message["clientID"]

                    if any(nickname == client[0] for client in current_users):
                        error = {"type": "error", "message": "Nickname already in use"}
                        socket.sendall(json.dumps(error).encode('utf-8'))
                        socket.close()
                    else: 
                        accept = {"type": "accept"}
                        socket.sendall(json.dumps(accept).encode('utf-8'))
                        print(f"{current_time}:: {nickname}: connected.")

                        current_users.append((nickname, socket))
                        self.listen_for_message(socket, client_id) 
        except OSError as e:
            print("Error:", e) 

    ## Listens for messages from the users based on the client socket, receiving
    ## .json files and decoding them to be broadcasted and displayed on other 
    ## client ends. Also handles the disconnect call, allowing the user to 
    ## successfully terminate the connection from the server 
    def listen_for_message(self, socket, client_id):
        nickname = None
        try: 
            while True: 
                client_message = socket.recv(2048).decode('utf-8')

                if not client_message:
                    break

                json_file = json.loads(client_message)
                if json_file["type"] == "disconnect":
                    current_time  = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                    nickname = json_file["nickname"]
                    print(f"{current_time}:: {nickname}: disconnected.\n")
                    
                    break

                if json_file["type"] == "message": 
                    current_time = json_file.get("timestamp")
                    nickname = json_file.get("nickname")
                    message = json_file.get("message")

                    broadcast = {
                        "type": "broadcast", 
                        "nickname": nickname, 
                        "message": message, 
                        "timestamp": current_time
                    }

                    print(f"Received: IP: {self.hostname}, Port: {self.port}, Client-Nickname: {nickname}, ClientID:{client_id}, Date/time:{current_time}, Msg-Size:{len(message)}")
                    print("Broadcasted:", ', '.join([client[0] for client in current_users if client[1] is not socket]))
                    print()

                    for client in current_users:
                        if client[1] is not socket: 
                            client[1].sendall(json.dumps(broadcast).encode('utf-8'))
        except json.decoder.JSONDecodeError as e: 
            print("Error decoding JSON:", e)
        except Exception as e:
            print("Error:", e)
        finally: 
            if nickname: 
                self.remove_client(nickname, socket) 

    ## Checks if the client socket has been terminated and removes the user from 
    ## the list of current users connected to the server 
    def remove_client(self, nickname, socket):
        for i, client in enumerate(current_users):
            if client[0] == nickname and client[1] == socket: 
                del current_users[i] 
                break 

def main():
    ## Get paramters for the server
    hostname = '10.0.0.1'
    port = validate_args(args)

    ## Start the server
    server = ChatServer(hostname, port)

if __name__ == "__main__":
    main()