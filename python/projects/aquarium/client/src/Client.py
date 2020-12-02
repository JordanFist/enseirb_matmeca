import sys
import socket
import selectors
import types
from queue import Queue
import time

class Client:

    def __init__(self,host, port, id, recvQueue, sendQueue):
        self.__host = host
        self.__port = int(port)
        self.__id = id
        self.__receiveSelector = selectors.DefaultSelector()
        self.__sendSelector = selectors.DefaultSelector()
        self.__toSend=sendQueue
        self.__received=recvQueue
        self.__buffer=''
        self.start()


    def start(self):
        server_addr = self.__host, self.__port
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        sock.connect_ex(server_addr)
        hello = "hello as " + str(self.__id)
        sock.sendall(hello.encode())
        # sock.recv(1024)
        #hello = "getFishesContinuously"
        # sock.sendall(hello.encode())
        #Here, we do all which has to happen before lunching the mainloop, demander l'id par exemple
        sock.setblocking(False)
        self.__receiveSelector.register(sock, selectors.EVENT_READ)
        self.__sendSelector.register(sock, selectors.EVENT_WRITE)
        print("Connection established with server")

    def __processReceving(self, key, mask):
        sock = key.fileobj

        if mask & selectors.EVENT_READ:
            recv_data= sock.recv(1024)
            if recv_data:
                self.__buffer += recv_data.decode()

            if not recv_data:
                # print("closing connection")
                self.__receiveSelector.unregister(sock)
                self.__sendSelector.unregister(sock)
                sock.close()

    def __processSending(self, key, mask):
        sock = key.fileobj

        if mask & selectors.EVENT_WRITE:
            while not self.__toSend.empty():
                msg = self.__toSend.get()
                # print("sending: ", msg)
                sent = sock.sendall(msg.encode())

    def run(self):

        try:
            while True:
                events = self.__receiveSelector.select(timeout=1)
                if events:
                    for key, mask in events:
                        self.__processReceving(key, mask)

                tmp = self.__buffer.split('$')
                while len(tmp) >1:
                    self.__received.put(tmp[0])
                    # print("added to queue")
                    self.__buffer= '$'.join(tmp[1:])
                    tmp = self.__buffer.split('$')

                events = self.__sendSelector.select(timeout=1)
                if events:
                    for key, mask in events:
                        self.__processSending(key, mask)
                time.sleep(0)

        except KeyboardInterrupt:
            print("caught keyboard interrupt, exiting")
        finally:
            self.__receiveSelector.close()
            self.__sendSelector.close()


    def stop(self):
        raise SystemExit()
