#!/usr/bin/python3

from Drawable import Drawable
from Queue import Queue
from random import randint
from numpy import sign
from math import sqrt
from time import time

class Fish:
    __LEFT_DIRECTION = 0
    __RIGHT_DIRECTION = 1
    __DOWN_DIRECTION = 0
    __UP_DIRECTION = 1
    __PERIOD = 50 #Le poisson parcourt 1pixel/50ms donc 20pixels/1s
    __INITIAL_SPEED = 1

    def __init__(self, name, posX, posY, height, width):
        self.name = name
        self.height = self.initHeight = height
        self.width = self.initWidth = width
        self.posX = posX
        self.posY = posY
        self.direction = (self.__LEFT_DIRECTION, self.__DOWN_DIRECTION)
        self.speed = self.__INITIAL_SPEED
        self.dest = Queue()
        self.imageCopy = Drawable.getFish()
        self.image = Drawable.getFish()
        self.photo = None
        self.fish = None
        self.swimming = None
        self.rateDelay = 0.5
        self.tf = self.ti = time()

    """ Computes dx and dy, the little distance traveled during the call of the move method """
    def computeMovement(self):
        x = (self.dest.peek()[0] - self.posX)
        y = (self.dest.peek()[1] - self.posY)
        if (x != 0 and y != 0):
            if (abs(x) > abs(y)):
                ratio = abs(x / y)
                dx = self.speed * ratio / (sqrt(ratio ** 2 + 1))
                dy = self.speed / (sqrt(ratio ** 2 + 1))
            else:
                ratio = abs(y / x)
                dx = self.speed / (sqrt(ratio ** 2 + 1))
                dy = self.speed * ratio / (sqrt(ratio ** 2 + 1))
            self.dx = dx * sign(x)
            self.dy = dy * sign(y)
        elif (x == 0):
            self.dx = 0
            self.dy = self.speed * sign(y)
        elif (y == 0):
            self.dy = 0
            self.dx = self.speed * sign(x)

    """ Returns the oldest destination added """
    def getOldestDestination(self):
        if (self.dest.last() == None):
            return (None, None)
        return (self.dest.last()[0], self.dest.last()[1])

    """ Returns the current destination """
    def getCurrentDestination(self):
        if (self.dest.peek() == None):
            return (None, None)
        return (self.dest.peek()[0], self.dest.peek()[1])

    """ Returns the name of the fish """
    def getName(self):
        return self.name

    """ Returns True if the fish is swimming """
    def isSwimming(self):
        return self.swimming != None

    """ Sets the speed of the fish """
    def setSpeed(self, speed):
        self.speed = speed

    """ Returns the speed of the fish """
    def getSpeed(self):
        return self.dest.peek()[2]

    """ Returns the size of the fish """
    def getSize(self):
        return (int(self.width), int(self.height))

    """ Return the position of the fish """
    def getPosition(self):
        return (int(self.posX), int(self.posY))

    """ Adds a new destination to the fish """
    def addDestination(self, dest):
        self.dest.push(dest)

    """ Reconfigures variables for resizing the fish """
    def reconfigure(self, window):
        wscale = window.getWidth() / window.getLastWidth()
        hscale = window.getHeight() / window.getLastHeight()
        self.width *= wscale
        self.height *= hscale
        self.posX *= wscale
        self.posY *= hscale
        if not (self.dest.isEmpty()):
            self.dest.changeTop((self.dest.peek()[0] * wscale, self.dest.peek()[1] * hscale, self.getSpeed()))

    """ Updates the position of the fish """
    def updatePosition(self, canvas):
        self.posX = canvas.coords(self.fish)[0]
        self.posY = canvas.coords(self.fish)[1]

    """ Turns the fish in the right direction according to this destination """
    def turnInRightDirection(self, canvas):
        if (((self.direction[1] == self.__UP_DIRECTION) and (self.posY < self.dest.peek()[1])) or ((self.direction[1] == self.__DOWN_DIRECTION) and (self.posY > self.dest.peek()[1]))):
            self.direction = (self.direction[0], (self.direction[1] + 1) % 2)
        if (((self.direction[0] == self.__LEFT_DIRECTION) and (self.posX < self.dest.peek()[0])) or ((self.direction[0] == self.__RIGHT_DIRECTION) and (self.posX > self.dest.peek()[0]))):
            self.direction = ((self.direction[0] + 1) % 2, self.direction[1])
            canvas.changeFishDirection(self)
    """ Returns True if the fish is on the way or False if he is arrived """
    def isOnTheWay(self):
        return ((self.direction == (self.__LEFT_DIRECTION, self._Fish__UP_DIRECTION)) and (self.posX >= self.dest.peek()[0]) and (self.posY >= self.dest.peek()[1])
            or ((self.direction == (self.__LEFT_DIRECTION, self._Fish__DOWN_DIRECTION)) and (self.posX >= self.dest.peek()[0]) and (self.posY <= self.dest.peek()[1]))
            or ((self.direction == (self.__RIGHT_DIRECTION, self._Fish__UP_DIRECTION)) and (self.posX <= self.dest.peek()[0]) and (self.posY >= self.dest.peek()[1]))
            or ((self.direction == (self.__RIGHT_DIRECTION, self._Fish__DOWN_DIRECTION)) and (self.posX <= self.dest.peek()[0]) and (self.posY <= self.dest.peek()[1]))
            )

    """ Updates the fish position in the canvas and sets the new destination when the fish is arrived """
    def move(self, canvas):
        if not (self.dest.isEmpty()):
            if (self.isOnTheWay()):
                canvas.updateFishPosition(self)
                self.updatePosition(canvas)
            else:
                self.tf = time()
                # print("time", self.tf - self.ti)
                self.ti = time()
                self.dest.pop()
                if not (self.dest.isEmpty()):
                    self.setSpeed(self.getSpeed())
                    self.computeMovement()
                    self.turnInRightDirection(canvas)

            self.swimming = canvas.after(self.__PERIOD, self.move, canvas)
        else:
            self.swimming = canvas.after(self.__PERIOD, self.waitForMove, canvas)

    def waitForMove(self, canvas):
        if (self.dest.isEmpty()):
            self.swimming = canvas.after(self.__PERIOD, self.waitForMove, canvas)
        else:
            self.setSpeed(self.getSpeed())
            self.computeMovement()
            self.turnInRightDirection(canvas)
            self.swimming = canvas.after(self.__PERIOD, self.move, canvas)
