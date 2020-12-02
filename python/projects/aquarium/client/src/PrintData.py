import time
import sys

t = time.clock()
file_name = sys.argv[1]

while (1):
    if (time.clock() - t >= 1):
        file = open(file_name, "r")
        print(file.read())
        file.close()
        t=time.clock()
