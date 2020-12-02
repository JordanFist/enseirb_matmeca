import socket

class Client:
    hote = "127.0.0.1"
    port = 7989
    BUFFER_SIZE = 200

    def __init__(self):
        self.sock = None
        self.conn = True
        self.buffer = None

    def deconnect(self):
        self.conn = False

    def askDeconnection(self):
        self.sock.send(("END").encode())

    def run(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((self.hote, self.port))

        while (1):
            message=input("")
            self.sock.send(message.encode())
            print(self.sock.recv(self.BUFFER_SIZE).decode())
        print ("Socket closed")
        self.sock.close()

client = Client()
client.run()
