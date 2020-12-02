import numpy as np
from math import tanh


class Node:
    def __init__(self, label, lr=0.001):
        self.SIZE = 28
        self.label = label
        self.weight = np.zeros(self.SIZE ** 2)
        self.lr = lr

    def predict(self, image):
        data = np.dot(image.pixels, self.weight)
        a = data.sum()
        a = tanh(a)
        return a

    def train(self, images):
        for i in range(images.getIndex()):
            a = self.predict(images.get(i))
            y = 1 if images.get(i).label == self.label else -1
            error = y - a
            self.weight += self.lr * error * images.get(i).pixels

    def test(self, images):
        error = 0
        for i in range(images.getIndex(), images.size()):
            a = self.predict(images.get(i))
            y = 1 if images.get(i).label == self.label else -1
            error += abs(y - a)
        return error


