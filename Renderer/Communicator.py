import socket
import json
from Point import Point

class Communicator:
    def __init__(self, server_ip, server_port):
        self.server_ip = server_ip
        self.server_port = server_port
        self.client_socket = None

    def connect(self):
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client_socket.connect((self.server_ip, self.server_port))

    def send_message(self, message):
        if self.client_socket is not None:
            self.client_socket.send(message.encode())
            
    def recv_message(self):
        if self.client_socket is not None:
            return self.client_socket.recv(1024)

    def close(self):
        if self.client_socket is not None:
            self.client_socket.close()
    
    def convertJsonToList(self, jsonStr):
        points = json.loads(jsonStr)
        list_of_points = [Point(point['x'], point['y'], point['velocity'], point['acceleration'], point['mass'], point['radius']) for point in points]
        return list_of_points        

