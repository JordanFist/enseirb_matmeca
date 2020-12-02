#!/usr/bin/python3

from Drawable import Drawable
from tkinter import Canvas
from PIL import Image, ImageTk

class ResizingCanvas(Canvas):
    __ORIGIN = (0, 0)

    def __init__(self, fishManager):
        Canvas.__init__(self, fishManager.getMaster(), highlightthickness = 0)

        self.backgroundCopy = Drawable.getBackground()
        self.background = None
        self.bind("<Configure>", lambda event, arg=fishManager: self.resizeImages(event, arg))
        self.update()

    """ Draws the fish in the canvas """
    def drawFish(self, fish):
        fish.image = fish.imageCopy.resize(fish.getSize())
        fish.photo = ImageTk.PhotoImage(fish.image)
        fish.fish = self.create_image(fish.getPosition(), anchor='nw', image = fish.photo)

    """ Erases the fish in the canvas """
    def eraseFish(self, fish):
        self.delete(fish.fish)
        if fish.swimming is not None:
            self.after_cancel(fish.swimming)
            fish.swimming = None

    """ Turns the fish in the right direction in the canvas """
    def changeFishDirection(self, fish):
        self.delete(fish.image)
        fish.image = fish.image.transpose(Image.FLIP_LEFT_RIGHT)
        fish.imageCopy = fish.imageCopy.transpose(Image.FLIP_LEFT_RIGHT)
        fish.photo = ImageTk.PhotoImage(fish.image)
        fish.fish = self.create_image(fish.getPosition(), anchor='nw', image = fish.photo)

    """ Moves the fish in the canvas """
    def updateFishPosition(self, fish):
        self.move(fish.fish, fish.dx, fish.dy)

    """ Resizes the fish and the background in the canvas """
    def resizeImages(self, event, fishManager):
        backgroundSize = (event.width, event.height)
        fishManager.getWindow().setDimensions()
        if self.bbox("bg") != self.__ORIGIN + backgroundSize:
            self.delete(self.background)
            self.background = self.backgroundCopy.resize(backgroundSize)
            self.backgroundPhoto = ImageTk.PhotoImage(self.background)
            self.create_image(self.__ORIGIN, anchor="nw", image=self.backgroundPhoto)

            for fish in fishManager.getFishes():
                if not (fish.dest.isEmpty()):
                    fish.computeMovement()
                fish.reconfigure(fishManager.getWindow())
                self.delete(fish.image)
                fish.image = fish.imageCopy.resize(fish.getSize())
                fish.photo = ImageTk.PhotoImage(fish.image)
                fish.fish = self.create_image(fish.getPosition(), anchor='nw', image = fish.photo)


