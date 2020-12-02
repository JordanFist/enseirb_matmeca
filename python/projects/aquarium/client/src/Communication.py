import socket
import time
HOST = '127.0.0.1'  # The server's hostname or IP address
PORT = 65432        # The port used by the server

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:

    s.connect((HOST, PORT))
    while True:
        for i in range(100):

            t='i=' + str(i)
            s.sendall(t.encode())
            data = s.recv(1024)
            print('Received', repr(data))
            time.sleep(2)
        #data = conn.recv(1024)
        #if not data:
            #break
        #conn.sendall(data)

print('Received', repr(data))
