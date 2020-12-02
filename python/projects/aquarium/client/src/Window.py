#!/usr/bin/python3

from tkinter import Frame

class Window(Frame):
  
    def __init__(self):
        super().__init__() 
        self.initUI()
        
    def initUI(self):
        self.master.title("Aquarium")

        screenWidth = self.master.winfo_screenwidth() 
        screenHeight = self.master.winfo_screenheight() 
        self.width = screenWidth - screenWidth / 4
        self.height = screenHeight - screenHeight / 3
        self.lastWidth = self.width
        self.lastHeight = self.height
        xWindow = screenWidth / 8
        yWindow = screenHeight / 6
        self.master.geometry(("%dx%d+%d+%d") % (self.width, self.height, xWindow, yWindow))

    def getHeight(self):
        return self.height
    
    def getWidth(self):
        return self.width

    def getLastWidth(self):
        return self.lastWidth

    def getLastHeight(self):
        return self.lastHeight

    def setDimensions(self):
        self.lastWidth = self.width
        self.lastHeight = self.height
        self.width = self.master.winfo_width()
        self.height = self.master.winfo_height()