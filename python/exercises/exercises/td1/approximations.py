from math import *
import numpy as n
import matplotlib.pyplot as pl

########## Partie 1  ##########

#1

def rp (x,p):
    if (x == -x):
        return x
    else:
        i = 0
        j = 0
        y = abs(x)
        c = 10**(p-1)
#on place abs(x) entre 10^p et 10^(p+1) 
        while (y <= c):
            y *= 10
            i += 1
        while (y > 10 * c):
            y /= 10
            j+=1
#on tronc en recopérant au préalable le (p+1)ème chiffre significatif pour l'arrondi
        y = y*10
        y=int(y)
#on arrondie et on retronc
        if (y % 10 >= 5):
            y = (y // 10) + 1
        else:
            y = y // 10
#on replace x à sa puissance initiale
        y = y * (10**j)
        y = y / (10**i)
        if  (x < 0):
            y = -y
        return y

#2

def somme(x,y,p):
    return (rp(rp(x,p) + rp(y,p),p))

def multiplication(x,y,p):
    return (rp(rp(x,p) * rp(y,p),p))


#3

def erreur_relative_somme(x,y,p):
    reel =  x + y
    machine = somme (x , y , p)
    if (reel == -reel):
        return 0
    else:
        return abs( (reel - machine) / reel)



def erreur_relative_mult (x,y,p):
    reel =  x * y
    machine = multiplication (x , y , p)
    if (reel == -reel):
        return 0
    else:
        return abs( (reel - machine) / reel)

#4

def graph_erreur_relative_somme():
    y=100
    p=2
    X= n.arange(0,2000.1,0.1)
    Y=[0]*len(X)
    for i in range(len(X)):
        Y[i] = erreur_relative_somme(y,X[i],p)
    pl.plot(X,Y)
    pl.xlabel("x")
    pl.ylabel("erreur_relative_somme(100,x)")
    pl.title("Représentation de la variation de l'erreur relative de la somme de 100 et d'un x variant de 0 à 2000 par pas de 0.1 avec une précision p = 2")
    pl.show()

def graph_erreur_relative_produit():
    y=100
    p=1
    A= n.arange(0.1,105.1,0.1)
    O=[0]*len(A)
    for i in range(len(A)):
        O[i] = erreur_relative_mult(y,A[i],p)
    pl.plot(A,O)
    pl.xlabel("x")
    pl.ylabel("erreur_relative_mult(100,y)")
    pl.title("Représentation de la variation de l'erreur relative du produit de 100 et d'un x variant de 0 à 105 par pas de 0.1 avec une précision p = 2")
    pl.show()

#5

def log2(p):
    den=1
    s=0
    for i in range(10**(p),0,-1):
        den*=-1
        s = somme(s, den/i ,p)
    erreur = abs((s - log(2)) / log(2))
    return (s,erreur)


def graph_erreur_relative_log2():
    X= n.arange(1,6)
    Y=[0]*len(X)
    for i in range(len(X)):
        Y[i] = log2(X[i])[1]
    pl.plot(X,Y)
    pl.xlabel("p")
    pl.ylabel("erreur_relative_log(p)")
    pl.title("Représentation de la variation de l'erreur relative du calcul de log(2) en fonction de la précision p ")
    pl.show()


########## tests ##########

def test_rp():
    a = (rp(3.141592658, 4) == 3.142)
    b = (rp(10507.1823, 4) == 10510)
    c = (rp(-0.0001857563, 4) == -0.0001858)
    d = (rp(3.141592658, 6) == 3.14159)
    e = (rp(-10507.1823, 6) == -10507.2)
    f = (rp(0.0001857563, 6) == 0.000185756)
    g = (rp(0.000000000000000000000, 6) == 0.000000)
    print ("test de rp : ", a and b and c and d and e and f and g)

def test_add():
    a = (somme(0.145 , 0.0564, 2) == 0.21)
    b = (somme(3.1415, 10507.1823, 3) == 10500)
    c = (somme(0.0001857, 0.0000756, 3) == 0.000262)
    print("test de la somme : ", a and b and c)

def test_mult():
    a = (multiplication(2.0000 , 1469, 2) == 3000)
    b = (multiplication(0.00001575, 9486.75, 3) == 0.150)
    c = (multiplication(0.00001575, 9486.75, 1) == 0.2)
    print("test de la multiplication : ", a and b and c)

def test_erreur_relative_somme():
    a = ( erreur_relative_somme(0.145 , 0.0564, 2) <= 10**(-1)/2)
    b = ( erreur_relative_somme(3.1415, 10507.1823, 3) <= 10**(-2)/2)
    c = ( erreur_relative_somme(0.0001857, 0.0000756, 3) <= 10**(-2)/2)
    print("test de l'erreur relative de la somme : ",a and b and c)

def test_erreur_relative_mult():
    a = (erreur_relative_mult(2.0000 , 1469, 2) <= 10**(-1)/2)
    b = (erreur_relative_mult(0.00001575, 9486.75, 3)<= 10**(-2)/2 )
    c = (erreur_relative_mult(0.00001575, 9486.75, 1)<= 1/2 )
    print("test de l'erreur relative de la multiplication : ", a and b and c)



    


########## main ##########

test_rp()
test_add ()
test_mult ()
test_erreur_relative_somme()
test_erreur_relative_mult()
graph_erreur_relative_somme()
graph_erreur_relative_produit()
graph_erreur_relative_log2()
