from math import *
import numpy as np
from scipy.linalg import cholesky
import math
import func as fun
"""
On a f(U+V) = 0 <=> f(U) + H(U).V = 0
                <=> H(U).v = - f(U)

Il suffit donc de resoudre le system d'equations : H(U)V = - f(U) avec V l'inconnu
"""


def f(x):
    
    """
    une fonction vectorielle pour les tests de la methode de Raphson Newton
    """
    
    f = np.zeros(len(x))
    f[0] = (math.sin(x[0]) + x[1]**2 + math.log(x[2]) - 7.0)
    f[1] = (3.0*x[0] + 2.0**x[1] - x[2]**3 + 1.0)
    f[2] = (x[0] + x[1] + x[2] - 5.0)
    return f

def g(x):

    """
    une fonction reelle pour les tests de la methode de Raphson Newton
    """
    return x*x-4

    
def newtonRaphson2(f, x,  backtracking = 0 , N = 100, tol=1.0e-9):
    """
    Cette fonction est une implementation de la methode de Raphson Newton pour la recherche des zeros des fonctions, cette fonction est adapte pour fonctionner avec n'importe quel type de fonction (reelle, vectorielle...),
    f : la fonction
    x : le point de depart pour la recherche
    tol : l'erreur
    N : Nombre d'iterations
    backtracking : égale à 1 si on veut bien utiliser le backtracking, 0 sinon
    """
    def jacobian(f, x):
        """
        cette fonction calcul la matrice jacobienne de la fonction f en x
        """
        h = 1.0e-4
        n = len(x)
        jac = np.zeros((n,n))
        f0 = f(x)
        for i in range(n):
            temp = x[i]
            x[i] = temp + h
            f1 = f(x)
            x[i] = temp
            jac[:,i] = (f1 - f0)/h
        return jac,f0
    if backtracking == 0 : 
        for i in range(N):
            jac,f0 = jacobian(f, x)
            if math.sqrt(np.dot(f0,f0)/len(x)) < tol: 
                return x
            dx = fun.gaussPivot(jac,-f0)
            x=x+dx
            #if math.sqrt(np.dot(dx,dx)) < tol*max(max(abs(x)),1.0):
        return x
            #print("Too many iterations")
    else:
        for i in range(N):
            jac,f0 = jacobian(f, x)
            if math.sqrt(np.dot(f(x),f(x))/len(x)) < tol: 
                return x
            dx = fun.gaussPivot(jac,-f0)
            delta = 1
            while ( np.linalg.norm(f(x + dx*delta)) > (1-delta/2)*np.linalg.norm(f(x)) and delta > 1/100):
                delta = delta/2
            x= x + dx*delta
            #if math.sqrt(np.dot(dx,dx)) < tol*max(max(abs(x)),1.0):    
        return x
            #print("Too many iterations")
    

    




"""
Test de la fonction newton_raphson sur la fonction reelle : f x -> x*x - 4, de zero x = 2.
"""
x = np.array([1.0, 1.0, 1.0])
y = np.array([ 0.59905376, 2.3959314, 2.00501484])
N = 10
print("le zero de la fonction f (x) = x*x-4 est")
print(newtonRaphson2(g,x,1, N)[0])

"""
test pour une fonction vectorielle f
"""
print("le zero de la fonction f(x, y, z) =  (sin(x) + y*y + log(z) - 7, 3x + 2**y + z**3 + 1, x + y + z -5)")
print(newtonRaphson2(f, x,1,N))
