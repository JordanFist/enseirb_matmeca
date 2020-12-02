#!/usr/bin/python3

class Queue:
    def __init__(self):
        self.__queue = []

    def isEmpty(self):
        return (self.size() == 0)

    def push(self, item):
        self.__queue.insert(0, item)

    def pop(self):
        return self.__queue.pop()

    def peek(self):
        if not (self.isEmpty()):
            return self.__queue[len(self.__queue) - 1]
        return (None, None)

    def last(self):
        if not (self.isEmpty()):
            return self.__queue[0]
        return (None, None)

    def changeTop(self, item):
        self.pop()
        self.__queue.append(item)

    def size(self):
        return len(self.__queue)

    def display(self):
        for item in self.__queue:
            print(item)

