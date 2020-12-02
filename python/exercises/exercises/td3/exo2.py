import numpy as np
import matplotlib.pyplot as pl
from math import *
from partie1 import *
import copy

A = np.matrix([[1], [2]])

def norme(Q1):
    somme = 0
    for i in range(len(Q1)):
        somme += Q1[i, 0] ** 2
    return (sqrt(somme))

def complementaireHH(Q1, i):
    R1 = np.zeros(np.shape(Q1))
    R1[i, 0] = norme(Q1)
    return R1

def recopie_gauche(Q1, i):
    R = copy.deepcopy(Q1)
    for k in range(i):
        R[k] = 0
    return R

def recopie_droite(Q2, i):
    R = (copy.deepcopy(Q2)).T
    for k in range(i):
        R[k] = 0
    return R

def bidiagonalise(A):
    (n, m) = np.shape(A)
    Qleft = np.eye(n, m)
    Qright = np.eye(n, m)
    BD = A
    for i in range (n - 1):
        Q1 = recopie_gauche(BD[0:n, i], i) 
        Q1 = creerHH(Q1, complementaireHH(Q1, i))
        Qleft = mat_mat(Qleft, Q1)
        BD = mat_mat(Q1, BD)
        if (not (i ==(m - 2))):
            Q2 = recopie_droite(BD[i], i+1)
            Q2 = creerHH(Q2, complementaireHH(Q2, i+1))
            Qright = mat_mat(Q2, Qright)
            BD = mat_mat(BD, Q2)
    return (Qleft, BD, Qright)


A = np.matrix([[100, 10, 1], [2, 2, 155], [3, 3, 2]])
print(bidiagonalise(A))
