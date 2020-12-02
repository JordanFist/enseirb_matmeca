#!/usr/bin/python3

from Fish import Fish
from Window import Window
from ResizingCanvas import ResizingCanvas
from math import sqrt

class FishManager:

    def __init__(self):
        self.__lastMessages = []
        self.__fishes = []
        self.__window = Window()
        self.__canvas = ResizingCanvas(self)
        self.__canvas.pack(fill = 'both', expand = 'yes')

    """ Returns the window """
    def getWindow(self):
        return self.__window

    """ Returns the master of the window """
    def getMaster(self):
        return self.__window.master

    """ Returns all the fishes in the canvas """
    def getFishes(self):
        return self.__fishes

    """ Computes the new coordinates according to the coordinates in percentage """
    def percentageToCoordinates(self, x, y):
        return (x * self.__window.getWidth() / 100, y * self.__window.getHeight() / 100)

    """ Returns True if the message is already handled """
    def isAlreadyHandled(self, msg1, msg2):
        if ((msg1[0] == msg2[0]) and (msg1[2] == msg2[2])):
            return True
        return False

    """ Deletes the last remaining fish """
    def shouldBeDeleted(self):
        for msg in self.__lastMessages:
            fish = self.findName(msg[0])
            if (fish != None and fish.getCurrentDestination() == (None, None)):
                self.__lastMessages.remove(msg)

    """ Sorts the new messages received """
    def updateMessages(self, newMessages):
        for lastMsg in self.__lastMessages:
            check = False
            #if (newMessages == []):
            #    self.shouldBeDeleted()
            for newMsg in newMessages:
                if self.isAlreadyHandled(lastMsg, newMsg):
                    newMessages.remove(newMsg)
                    check = True
                    break
            if (check == False):
                fish = self.findName(lastMsg[0])
                if (fish != None and (fish.getCurrentDestination()[0], fish.getCurrentDestination()[1]) != self.percentageToCoordinates(lastMsg[2][0], lastMsg[2][1])):
                    self.__lastMessages.remove(lastMsg)
                    #if (fish.getCurrentDestination() == (None, None)):
                    #    self.__lastMessages.remove(lastMsg)

        for newMsg in newMessages:
            check = True
            for lastMsg in self.__lastMessages:
                if (self.isAlreadyHandled(newMsg, lastMsg)):
                    check = False
            if (check == True):
                self.__lastMessages.append(newMsg)

        return newMessages

    #    if (fish.dest.last() == None):
    #def isValidDestination(self, fish, dest):
    #        return True
    #    fishDest = (fish.dest.last()[0], fish.dest.last()[1])
    #    finalDest = self.percentageToCoordinates(dest[0], dest[1])
    #    if (fishDest != finalDest):
    #        return True
    #    return False

    """ Handled the new sorted messages received """
    def handleMessage(self, fishes):
        fishes = self.updateMessages(fishes)
        for msg in fishes:
            #print("handle", msg)
            fish = self.findName(msg[0])
            if (fish != None):
                if (fish.isSwimming()):
                    #print('1')
                    self.addDestination(msg[0], (msg[2][0], msg[2][1]), msg[4])
                else:
                    #print('2')
                    if (msg[1] != msg[2]):
                        #print("2bis")
                        self.addDestination(msg[0], (msg[2][0], msg[2][1]), msg[4])
                        self.startFish(msg[0])
            else:
                # if (msg[1] == msg[2]):
                # print('3')
                self.addFish(msg[0], msg[1][0], msg[1][1], msg[3][0], msg[3][1])
                if (msg[1] != msg[2]):
                    self.addDestination(msg[0], (msg[2][0], msg[2][1]), msg[4])
                    self.startFish(msg[0])

        for fish in self.__fishes:
            if not (self.findMessage(fishes, fish.getName())):
                # print("4")
                self.delFish(fish.name)

    """ Adjusts the delay of the fish """
    def adjustDelay(self, fish):
        xf, yf = fish.getCurrentDestination()
        xi, yi = fish.getPosition()
        d = sqrt((xf - xi) ** 2 + (yf - yi) ** 2)
        v = 20 * fish.getSpeed()
        tDelay = d / v
        # print("delay", tDelay)
        return tDelay

    """ Checks if the destination is valid """
    def isValidDestination(self, fish ,dest):
        if (fish.getOldestDestination() == dest):
            return False
        return True


    """ Adds a new destination in the fish """
    def addDestination(self, name, dest, temps):
        fish = self.findName(name)
        #print("dest", self.percentageToCoordinates(dest[0], dest[1]))
        if (fish != None):
            #print("fish1",end='')
            #fish.dest.display()
            if (self.isValidDestination(fish, dest)):
                xf, yf = self.percentageToCoordinates(dest[0], dest[1])
                if (fish.dest.isEmpty()):
                    xi, yi = fish.getPosition()
                else:
                    xi, yi = fish.getOldestDestination()
                d = sqrt((xf - xi) ** 2 + (yf - yi) ** 2)
                v = d / temps / 20
                if (v != 0):
                    if not (fish.dest.isEmpty()):
                        tDelay = self.adjustDelay(fish)
                        if (temps - tDelay > 0):
                            v = d / (temps - tDelay) / 20

                    # print('rateDelay', fish.rateDelay)

                    fish.addDestination((xf, yf, v))

            else:
                print(name + " doesn't exist")


    """ Starts the fish """
    def startFish(self, name):
        fish = self.findName(name)
        if (fish != None):
            fish.setSpeed(fish.getSpeed())
            fish.computeMovement()
            fish.turnInRightDirection(self.__canvas)
            fish.move(self.__canvas)
        else:
            print(name + " doesn't exist")

    """ Adds the fish in the canvas """
    def addFish(self, name, px, py, pheight, pwidth):
        if (self.findName(name) == None):
            x, y = self.percentageToCoordinates(px, py)
            width, height = self.percentageToCoordinates(pwidth, pheight)

            fish = Fish(name, x, y, height, width)
            self.__canvas.drawFish(fish)
            self.__fishes.append(fish)
        else:
            print("A fish is already named " + name)

    """ Deletes the fish in the canvas """
    def delFish(self, name):
        fish = self.findName(name)
        if (fish != None):
            self.__canvas.eraseFish(fish)
            self.__fishes.remove(fish)
        else:
            print(name + " doesn't exist")

    """ Returns the fish if he is in the canvas """
    def findName(self, name):
        for fish in self.__fishes:
            if (fish.name == name):
                return fish
        return None

    """ Return True if the fish is found in the new messages """
    def findMessage(self, fishes, name):
        for msg in self.__lastMessages:
            if (msg[0] == name):
                return True
        return False

    def quit(self):
        self.__window.quit()
