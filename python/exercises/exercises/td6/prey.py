import numpy as np
import matplotlib.pyplot as plt
import Euler

def Malthus(t,Z):
    a = 0.7
    b = 0.5
    gamma = a - b
    return np.array([[gamma * Z[0,0]]])

def Verhulst(t,Z):
    a = 0.8
    b = 0.2
    gamma = a - b
    kappa = a/b
    return np.array([[gamma * Z[0,0] * (1 - Z[0,0] / kappa)]])

def Lotka_Volterra(t,Z):
    a = 0.5
    b = 0.5
    c = 0.5
    d = 0.5
    return np.array([
        [Z[0,0] * (a - b * Z[1,0])],
        [Z[1,0] * (c * Z[0,0] - d)]
    ])

init = 0
end = 100

y = Euler.meth_epsilon(np.array([[3]]), init, end, 0.1, Malthus, Euler.step_euler)

Mal = []
for i in range(len(y)):
    Mal.append(y[i][0,0])

plt.plot(np.linspace(init, end, len(y)), Mal)
plt.show()

y = Euler.meth_epsilon(np.array([[3]]), init, end, 0.1, Verhulst, Euler.step_euler)

Ver = []
for i in range(len(y)):
    Ver.append(y[i][0,0])

plt.plot(np.linspace(init, end, len(y)), Ver)
plt.show()

y = Euler.meth_epsilon(np.array([[8],[2]]), init, end, 0.1, Lotka_Volterra, Euler.step_euler)

Lot_a = []
Lot_b = []
for i in range(len(y)):
    Lot_a.append(y[i][0,0])
    Lot_b.append(y[i][1,0])

plt.plot(np.linspace(init, end, len(y)), Lot_a)
plt.plot(np.linspace(init, end, len(y)), Lot_b)
plt.show()
