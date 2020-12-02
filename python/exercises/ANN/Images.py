import numpy as np
from Image import *
import random


class Images:
    def __init__(self, imageFilePath, labelFilePath, offsetTest):
        self.SIZE = 28
        self.offsetTest = offsetTest
        self.images = []
        self.read(imageFilePath, labelFilePath)

    def read(self, imageFilePath, labelFilePath):
        imageFile = open(imageFilePath)
        if labelFilePath != "":
            labelFile = open(labelFilePath)
        for imageLine in imageFile:
            if labelFilePath != "":
                labelLine = labelFile.readline()
            if imageLine[0] != "#" and len(imageLine) >= 2 * self.SIZE:
                pixels = np.array(list(map(float, imageLine.split())))
                pixels *= 0.001
                if labelFilePath != "":
                    image = Image(pixels, int(labelLine))
                else:
                    image = Image(pixels, 0)
                self.images.append(image)
        imageFile.close()
        if labelFilePath != "":
            labelFile.close()

    def getIndex(self):
        return int(self.size() - self.offsetTest * len(self.images))

    def get(self, index):
        return self.images[index]

    def size(self):
        return len(self.images)

    def shuffle(self):
        random.shuffle(self.images)
