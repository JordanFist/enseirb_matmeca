#!/usr/bin/python3

from PIL import Image
import sys

class Drawable:
    __RESSOURCES_PATH = '../ressources/'
    __BACKGROUND_PATH = __RESSOURCES_PATH + "aquarium.jpg"
    __FISH_PATH = __RESSOURCES_PATH + "fish.png"
    __background = None
    __fish = None
    
    @staticmethod
    def getBackground():
        if (Drawable.__background == None):
            try:
                Drawable.__background = Image.open(Drawable.__BACKGROUND_PATH)
            except IOError:
                print("Unable to load background")
                sys.exit(1)
            return Drawable.__background
        else:
            return Drawable.__background

    @staticmethod
    def getFish():
        if (Drawable.__fish == None):
            try:
                Drawable.__fish = Image.open(Drawable.__FISH_PATH)
            except IOError:
                print("Unable to load fish")
                sys.exit(1)
            return Drawable.__fish
        else:
            return Drawable.__fish

