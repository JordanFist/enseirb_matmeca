from partie1 import *

X = np.matrix([[3], [4], [0]])
Y = np.matrix([[0], [0], [5]])
H = np.matrix([[0.64, -0.48, 0.6], [-0.48, 0.36, 0.8], [0.6, 0.8, 0]])

def test_creerHH():
    test = 0
    RES = creerHH(X, Y)
    (n, m) = np.shape(RES)
    for i in range (n):
        for j in range (m):
            if float(int(RES[i, j] * 10**14)/10**14) == H[i, j] :
                test += 1
    if test == n * m :
        print("Test de creerHH... ok")
    else :
        
        print("Test de creerHH... failed")

test_creerHH()

def test_mat_vect():
    test = 0
    RES = mat_vect(creerHH(X, Y), X)
    (n, m) = np.shape(RES)
    for k in range (m):
        if RES[k] == Y[k] :
            test += 1
    if test == m :
        print("Test de mat_vect... ok")
    else :
        
        print("Test de mat_vect... failed")

test_mat_vect()
