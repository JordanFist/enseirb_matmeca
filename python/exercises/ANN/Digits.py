import sys
from Images import *
from Node import *
from matplotlib import pyplot as plt
import numpy as np

ROUNDS = 100
PERCENTAGE = 0.66
LR = 0.001
MIN_ERROR = 80
CHILD_SAFETY = 10

class Digits:
    def __init__(self, trainingImages, trainingLabels, validationImages):
        self.images = Images(trainingImages, trainingLabels, PERCENTAGE)
        self.network4 = Node(4, LR)
        self.network7 = Node(7, LR)
        self.network8 = Node(8, LR)
        self.network9 = Node(9, LR)
        self.vImages = Images(validationImages, "", 1)
        #self.vImages = Images(validationImages, "validation-labels.txt", 1)

    def trainOnce(self, network):
        error = np.inf
        i = 0
        while error > MIN_ERROR and CHILD_SAFETY > i:
            self.images.shuffle()
            for _ in range(ROUNDS):
                network.train(self.images)
            error = self.network4.test(self.images)
            i += 1

    def train(self):
        self.trainOnce(self.network4)
        self.trainOnce(self.network7)
        self.trainOnce(self.network8)
        self.trainOnce(self.network9)

    def predict(self, image):
        result = self.network4.label
        score = self.network4.predict(image)
        tmp = self.network7.predict(image)
        if tmp > score:
            result = self.network7.label
            score = tmp
        tmp = self.network8.predict(image)
        if tmp > score:
            result = self.network8.label
            score = tmp
        tmp = self.network9.predict(image)
        if tmp > score:
            result = self.network9.label
        return result

    def results(self):
        for image in self.vImages.images:
            print(self.predict(image))

    def test(self):
        score = 0
        for image in self.vImages.images:
            guess = self.predict(image)
            score += 1 if guess == image.label else 0
        print(score / len(self.vImages.images))


digits = Digits(sys.argv[1], sys.argv[2], sys.argv[3])
digits.train()
digits.results()
#digits.test()

