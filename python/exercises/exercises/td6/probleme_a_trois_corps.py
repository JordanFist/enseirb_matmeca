import numpy
import scipy.integrate
import matplotlib.pyplot as plt
import Euler

def f_2_corps(t, Z):
    G = 1
    mA = 1
    xA = 0
    yA = 0
    return numpy.array([
        [Z[2,0]],
        [Z[3,0]],
        [G * mA * (xA - Z[0,0]) / pow(pow(Z[0,0] - xA, 2) + pow(Z[1,0] - yA, 2), 3./2)],
        [G * mA * (yA - Z[1,0]) / pow(pow(Z[0,0] - xA, 2) + pow(Z[1,0] - yA, 2), 3/2)]
    ])

y = Euler.meth_epsilon(numpy.array([[0], [100], [0.1], [0]]), 0, 7000, 1, f_2_corps, Euler.step_euler)

Xb = []
Yb = []

for i in range(len(y)):
    Xb.append(y[i][0,0])
    Yb.append(y[i][1,0])

plt.plot(Xb, Yb)
plt.show()

def xB_cercle(t):
    return numpy.cos(t)

def yB_cercle(t):
    return numpy.sin(t)

def f_3_corps(t, Z):
    G = 1
    mA = 1
    mB = 0.01
    xA = 0
    yA = 0
    return numpy.array([
        [Z[2,0]],
        [Z[3,0]],
        [G * mA * (xA - Z[0,0]) / pow(pow(Z[0,0] - xA, 2) + pow(Z[1,0] - yA, 2), 3/2) + G * mB * (xB_cercle(t) - Z[0,0]) / pow(pow(Z[0,0] - xB_cercle(t), 2) + pow(Z[1,0] - yB_cercle(t), 2), 3/2)],
        [G * mA * (yA - Z[1,0]) / pow(pow(Z[0,0] - xA, 2) + pow(Z[1,0] - yA, 2), 3/2) + G * mB * (yB_cercle(t) - Z[1,0]) / pow(pow(Z[0,0] - xB_cercle(t), 2) + pow(Z[1,0] - yB_cercle(t), 2), 3/2)]
    ])

init = 0
end = 10

y = Euler.meth_epsilon(numpy.array([[0.5], [0.866], [0], [0.5]]), init, end, 0.1, f_3_corps, Euler.step_euler)

def rot(t):
    return numpy.array([
        [numpy.cos(t), numpy.sin(t)],
        [-numpy.sin(t), numpy.cos(t)]
    ])

B = []

temp_step = (end - init) / len(y)
for i in range(len(y)):
    B.append(numpy.dot(rot(init + i*temp_step), numpy.array([[xB_cercle(init + i*temp_step)],[yB_cercle(init + i*temp_step)]])))

C = []

for i in range(len(y)):
    C.append(numpy.dot(rot(init + i*temp_step), numpy.array([[y[i][0,0]],[y[i][1,0]]])))

Xc = []
Yc = []
for i in range(len(y)):
    Xc.append(C[i][0,0])
    Yc.append(C[i][1,0])

plt.plot(Xc, Yc)
plt.scatter([1], [0])
plt.plot([0], [0])
plt.show()
