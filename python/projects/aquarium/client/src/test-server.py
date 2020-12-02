import socket
from Config import Config
CONFIG_FILE="../affichage.cfg"
c = Config(CONFIG_FILE)
s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((c.get_address(), int(c.get_port()) ))
s.listen(100)
conn, addr = s.accept()
try:
    print('Connected by', addr)
    while True:
        data = conn.recv(1024)
        if not data:
            break
        print(data.decode())
        print("Message rebound: " + data.decode())
        conn.sendall(data)
except KeyboardInterrupt:
    print("caught keyboard interrupt, exiting")
finally:
    s.shutdown(0)
    s.close()
