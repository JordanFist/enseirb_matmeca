import sys
import re
from Controller import Controller

class Prompt:

    def __init__(self):
        self.__commands = ['addFish', 'startFish', 'status', 'delFish', 'getFishes', 'getFishesContinuously', 'ping', 'log']
        self.__controller = Controller()

    def run(self):
        """The prompt's main loop and the only public method"""
        while(1):
            self.__wait_command()

    def __wait_command(self):
        """When called, waits for user to input a line and processes it"""
        command = input('$ ')
        if command == "":
            return
        l= command.split()
        c = l[0]
        if c not in self.__commands:
            print(c + " is not a known command")
        else:
            s = ' '.join(l[1:])
            if (c == self.__commands[-1]):
                if s != "out":
                    print("NOK")
                else:
                    self.__controller.push(command)
                    # self.__controller.endApplication()
                    # sys.exit(0)

            elif (c == self.__commands[0]):
                regex = re.compile("\s*([a-zA-Z])+\sat\s[0-9]+x[0-9]+,\s[0-9]+x[0-9]+,\s([a-zA-Z])+")
                if not(bool(regex.match(s)) and len(s.split()) == 5):
                    print("NOK")
                else:
                    self.__controller.push(command)
                    self.__controller.push("getFishes")

            elif c == self.__commands[2] or c == self.__commands[4] or c == self.__commands[5] or c == self.__commands[6]:
                if (s != ""):
                    print("NOK")
                else:
                    self.__controller.push(command)

            else:
                if (s == ""):
                    print("NOK")
                else:
                    self.__controller.push(command)
                    self.__controller.push("getFishes")
