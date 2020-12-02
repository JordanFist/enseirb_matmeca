import numpy as np
from math import *
from newton_raphson import *

def E(X):
    N=len(X)
    res =  0
    for i in range(N):
        res += log(abs(X[i] + 1), 10) + log(abs(X[i] - 1), 10)
        for j in range(N):
            if i != j:
                res += 0.5 * log(abs(X[i] - X[j]), 10)
    return res

def nabla(X):
    N=len(X)
    res=np.zeros(N)
    for i in range(N):
        somme=0
        for j in range(N):
            if j!=i:
                somme+=1/(X[i]-X[j])
        res[i]=1/(X[i]+1)+1/(X[i]-1)+0.5*somme
    return res
    
def jac_nabla(X):
    N=len(X)
    res=np.zeros((N, N))
    for i in range(N):
        for j in range(N):
            if i==j:
                somme=0
                for k in range(N):
                    if i!=k:
                        somme+=1/(X[k]-X[i])**2
                res[i, i]=-1/(X[i]+1)**2-1/(X[i]-1)**2-0.5*somme
            else:
                res[i, j]=1/(2*(X[j]-X[i])**2)
    return res

def newtonRaphson(f, x, J, N, epsilon):
    for i in range(N):
        f0=f(x)
        if math.sqrt(np.dot(f0,f0)/len(x)) < epsilon: 
            return x
        dx = fun.gaussPivot(J(x), -f0)
        x=x+dx
        if math.sqrt(np.dot(dx,dx)) < epsilon*max(max(abs(x)),1.0):
            return x
    return x

"""X=np.array([-0.70, -0.45, -0.2, 0.3, 0.95])
print(E(X))
#print(jac_nabla(X))
Y=newtonRaphson(nabla, X, jac_nabla, 30, 1.0e-9)
print(Y)
print(E(Y))"""

def create_legendre(l):
    n=len(l)
    def P(x):
        return ((2*(n-1)+1)*x*l[n-1](x)-(n-1)*l[n-2](x))/n
    l.append(P)

def generate_legendre(n):
    res=[]
    def P_0(x):
        return 1
    def P_1(x):
        return x
    res.append(P_0)
    res.append(P_1)
    for i in range(2, n):
        create_legendre(res)
    return res

print(np.polynomial.legendre.Legendre((1, 1, 1, 1, 1)).deriv(1).roots())
