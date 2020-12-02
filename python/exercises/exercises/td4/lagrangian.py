import numpy as np
import matplotlib.pyplot as pl
from newton_raphson import *

#1.
#Representation des differentes forces sous forme de fonction 

def force_elastique(x, x0, k):
    return np.array([-k * (x - x0)])

def force_centrifuge(X, k, Xi = np.array([0., 0.])):
    return np.array([k * (X[0] - Xi[0]), k * (X[1] - Xi[1])])

def force_gravitationnelle(X, k, Xi = np.array([0., 0.])):
    if (X[0] == Xi[0] and X[1] == Xi[1]):
        return np.array([0., 0.])
    return np.array([-k * (X[0] - Xi[0]) / ((X[0] - Xi[0]) ** 2 + (X[1] - Xi[1]) ** 2) ** 1.5, -k * (X[1] - Xi[1]) / (((X[0] - Xi[0]) ** 2 + (X[1] - Xi[1]) ** 2) ** 1.5)])

#2.
#Representation de 2 planetes via la fonction simulation

def simulation(X):
    barycentre = np.array([0.01 / (1 + 0.01), 0.])
    return (force_gravitationnelle(X, 1, np.array([0., 0.])) + force_gravitationnelle(X, 0.01, np.array([1., 0.])) + force_centrifuge(X, 1 ,barycentre))

#On trouve la meme chose que sur le sujet
#print(simulation(np.array([1.5,0.])))

#3.
#On trouve L5
#print(newtonRaphson2(simulation, np.array([0.5,-0.8])))
L5 = newtonRaphson2(simulation, np.array([0.5,-0.8]))

#On trouve L4
#print(newtonRaphson2(simulation, np.array([0.5,0.8])))
L4 = newtonRaphson2(simulation, np.array([0.5,0.8]))

#On trouve L3
#print(newtonRaphson2(simulation, np.array([-1.1,0.])))
L3 = newtonRaphson2(simulation, np.array([-1.1,0.]))

#On trouve L2
#print(newtonRaphson2(simulation, np.array([0.9,0.])))
L2 = newtonRaphson2(simulation, np.array([0.9,0.]))
#on devrait obtenir x = 0.99 si on fait le rapport des masses le probleme c'est que newton_raphson est une methode approchée.

#On trouve L1
#print(newtonRaphson2(simulation, np.array([1.1,0.])))
L1 = newtonRaphson2(simulation, np.array([1.1,0.]))


X = np.linspace(-1, 1, 300)
Y = [sqrt(1 - x ** 2) for x in X]
Y2 = [-sqrt(1 - x ** 2) for x in X]

Xlagrangian = [L1[0], L2[0], L3[0], L4[0], L5[0]]
Ylagrangian = [L1[1], L2[1], L3[1], L4[1], L5[1]] 

Xlagrangian_expected = [0.99, 1.01]
Ylagrangian_expected = [0, 0]

Xplanet = [0, 1]
Yplanet = [0, 0]

Xreality1 = [0, L4[0], 1]
Yreality1 = [0, L4[1], 0]

Xreality2 = [0, L5[0], 1]
Yreality2 = [0, L5[1], 0]

Xexpectation1 = [0, 0.5, 1]
Yexpectation1 = [0, sqrt(3)/2, 0]

Xexpectation2 = [0, 0.5, 1]
Yexpectation2 = [0, sqrt(3)/2, 0]

pl.plot(X, Y, color="black")
pl.plot(X, Y2, color="black")
pl.plot(Xexpectation1, Yexpectation1, color="green", label="expected")
pl.plot(Xexpectation2, Yexpectation2, color="green")
pl.plot(Xreality1, Yreality1, color="orange", label="reality")
pl.plot(Xreality2, Yreality2, color="orange")
pl.scatter(Xlagrangian_expected, Ylagrangian_expected, color="green", s = 100)
pl.scatter(Xlagrangian, Ylagrangian, s = 100, label="lagrangian points")
pl.scatter(Xplanet, Yplanet, s = 100, color="red", label="planets")
pl.axis("equal")
pl.axhline(y = 0, color="black")
pl.axvline(x = 0, color="black")
pl.legend()
pl.show()
