import numpy as np

def U(X, Y):
    norme = np.linalg.norm(X-Y)
    if norme != 0 :
        return (X-Y)/norme
    else :
        return np.zeros((np.shape(X)))

X = np.matrix([[3], [4], [0]])
Y = np.matrix([[0], [0], [5]])
H = np.matrix([[0.64, -0.48, 0.6], [-0.48, 0.36, 0.8], [0.6, 0.8, 0]])

#print(U(X, Y))

def creerHH(X, Y):
    Id = np.eye(len(X))
    u = U(X, Y)
    return Id - 2 * u * u.T

#print(creerHH(X, Y))

def mat_vect_bad(M, X): #non optimise
    (n, n) = np.shape(M)
    V_res = np.zeros((n, 1))
    for i in range (n):
        for j in range (n):
            V_res[i] += M[i][j] * X[j]
    return V_res

def mat_vect(M, Z): #optimise
    (n, n) = np.shape(M)
    V_res = np.zeros((n, 1))
    u = U(X, Y) #complexite n
    utu = u.T * Z #produit scalaire (complexite n)
    utu = u * utu #multiplication vecteur * scalaire (complexite n)
    V_res = Z - 2 * utu #complexite n
    return V_res
#lineaire

#print(mat_vect(creerHH(X, Y), Z))

def mat_mat(M1, M2):
    (n, n) = np.shape(M1)
    M_res = np.zeros((n, n))
    for i in range (n):
        M_res[i] = mat_vect(M1, M2[i].T).T
    return M_res

#print(mat_mat(creerHH(X, Y),creerHH(X, Y)))
    
    

