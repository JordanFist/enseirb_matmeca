import numpy as np
import matplotlib.pyplot as pl
from math import *
from partie1 import *
from exo2 import *

def transfoQR_0(A):    
    (n, m) = np.shape(A)
    U = np.eye(n, m)
    V = np.eye(n, m)
    S = bidiagonalise(A)[1]
    for i in range (max(n, m)):
        (Q1, R1) = np.linalg.qr(S.T)
        (Q2, R2) = np.linalg.qr(R1.T)
        S = R2
        U = U * Q2
        V = Q1.T * V
    return (U, S, V)

A = np.matrix([[1, 1, 1], [2, 2, 1], [3, 3, 2]])
(Qleft, BD, Qright) = bidiagonalise(A)
(U, S, V) = transfoQR_0(A)

print(BD)
print()
print(S)
print()
