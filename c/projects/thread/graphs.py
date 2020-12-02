from subprocess import call
from time import time
import matplotlib.pyplot as pl

"""plot un graph comparant les perf de pthread et notre implémentation 
"""

def plotperf(test, argc, start, stop, labelx, labely, plot_number):
    call(["make", "clean"])
    call(["make"])

    x = []
    y = []
    z = []

    exec = [test]
    execvar = exec.copy()
    for i in range(start, stop+1):
        execvar = exec.copy()
        for j in range(argc):
            execvar.append(str(i))
        t = time()
        call(execvar)
        y.append(time() - t)
        x.append(i)

    call(["make", "clean"])
    call(["make","pthreads"])

    exec = ["taskset", "-c", "1", test]
    execvar = exec.copy()
    for i in range(start, stop+1):
        execvar = exec.copy()
        for j in range(argc):
            execvar.append(str(i))
        t = time()
        call(execvar)
        z.append(time() - t)

    pl.subplot(plot_number)
    pl.plot(x,y, label = 'notre implémentation')
    pl.plot(x,z, label = 'pthread')
    pl.ylabel(labely)
    pl.xlabel(labelx)
    pl.legend()

plotperf("./build/22-create-many-recursive", 2, 1, 400, "Nombre de threads crées", "Temps de calcul", 221)
plotperf("./build/61-mutex", 1, 1, 50, "Nombre de mutex crées", "Temps de calcul", 222)
plotperf("./build/51-fibonacci", 1, 1, 25, "Valeur de fibo calculée", "Temps de calcul", 223)
plotperf("./build/32-switch-many-join", 2, 1, 200, "Nombre de threads crées et join", "Temps de calcul", 224)
pl.show()