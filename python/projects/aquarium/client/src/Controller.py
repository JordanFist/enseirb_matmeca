from Client import Client

import sys
import os
import re
import queue
from Config import Config
import threading
from FishManager import FishManager
from tkinter import *
#CLASSE INCOMPLETE

PERIOD=200 #checking intreval in ms

## TODO:
#Traiter la réception des informations
#--ajouter un symbole pour différencier entre les messages
#--utiliser after de Tkinter pour programmer un appel tous les 200ms


class Controller:

    def __init__(self, CONFIG_FILE="../affichage.cfg"):
        """
        Start the GUI and the asynchronous threads. We are in the main
        (original) thread of the application, which will later be used by
        the GUI as well. We spawn a new thread for the worker (I/O).
        """
        #parsing configuration file
        self.__config = Config(CONFIG_FILE)

        # Creating task queues
        self.__recvQueue = queue.Queue(0)
        self.__sendQueue = queue.Queue(0)

        #Initializing Client
        self.__initClient(CONFIG_FILE)

        #add method for processing

        self.__ioThread = threading.Thread(target=self. __processIO)
        self.__ioThread.start(  )

        msg= "getFishesContinuously"
        self.__sendQueue.put(msg)
        self.manager = FishManager()


        # self.manager.addFish("PoissonClown", 50, 50, 10, 12)
        # self.manager.startFish("PoissonClown")"""

        # Start the periodic call in the GUI to check if the queue contains
        # anything
        self.__periodicCall(  )

    def __initClient(self, config):

        self.client= Client(self.__config.get_address(),
                            self.__config.get_port(),
                            self.__config.get_id(),
                            self.__recvQueue,
                            self.__sendQueue)

    def push(self, msg):
        self.__sendQueue.put(msg)

    def __periodicCall(self):
        """
        Check every 200 ms if there is something new in the queue.
        """
        #tells the fishmanager part to process what's in the queue if any
        # self.manager.processIncoming(  )
        while (not(self.__recvQueue.empty())):
            msg  = self.__recvQueue.get()
            tmp = re.split(' ', msg)
            fishes = []

            if tmp[0] == "Greetings":
                self.__log = tmp[1] + ".txt"
                file = open(self.__log, "w")
                cmd = "\"python3 PrintData.py " + self.__log + "\""
                os.system('xterm -geometry 100x10+300+900 -sb -e ' + cmd + '&')
                print(msg)

            if tmp[0] == "list":
                file = open(self.__log, "w")
                file.write(msg)
                msg = re.split('\[', msg)
                for m in msg[1:]:
                    tmp = re.split(' |, |,|x|\]', m)
                    name = tmp[0]
                    (px, py, dx, dy, height, width, tps) = (int(tmp[2]), int(tmp[3]), int(tmp[4]), int(tmp[5]), int(tmp[6]), int(tmp[7]), int (tmp[8]))
                    param = (name, (px, py), (dx, dy), (height, width), tps)
                    fishes.append(param)
                self.manager.handleMessage(fishes)

            if (tmp[0] == "OK:" or tmp[0] == "OK" or tmp[0] == "NOK" or tmp[0] == "pong"):
                print(msg)


            if (tmp[0] == 'bye'):
                print(msg)
                file.close()
                os.remove(self.__log)
                os._exit(0)

        #using the tkinter after method to schedule a perdiodic call 200ms from now
        self.manager.getMaster().after(200, self.__periodicCall)

    def __processIO(self):
        """
        This is where we handle the asynchronous I/O on sockets. It runs on a new thread.
        """
        self.client.run()

    def endApplication(self):
        print('exit')
        self.running = 0
        self.manager.stop()
        self.client.stop()

#root = Tkinter.Tk( )
# faut lancer le prompt aussi
#client = Controller()
#root.mainloop(  )
