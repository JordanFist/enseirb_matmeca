from math import *
from random import choice

def pgcd(a, b):
    if (b == 0):
        return a
    return pgcd(b, a % b)

def isPrime(n):
    for i in range(2 , int(sqrt(n)) + 1):
        if (n % i == 0):
            return False
    return True

def generate_prime(a, i):
    tab = []
    for i in range(a, a + i + 1):
        if (isPrime(i) == True):
            tab.append(i)
    if (len(tab) == 0):
        return -1
    return choice(tab)

def prime_with(n):
    tab = []
    for i in range(2, n):
        if (pgcd(n ,i) == 1):
            tab.append(i)
    if (len(tab) == 0):
        return -1
    return choice(tab)

# http://jf.burnol.free.fr/agreg171124euclide_info.pdf
def euclide_etendu(a, b):
    if (b == 0):
        if (a == 0):
            return 0, 0, 0
        return abs(a), -1 if a < 0 else 1, 0
    a, sa = abs(a), -1 if a < 0 else 1
    b, sb = abs(b), -1 if b < 0 else 1
    vv, uu, v, u = 1, 0, 0, 1
    e = 1
    q, rr = divmod(a, b)
    while (rr):
        a, b = b, rr
        vv, v = q * vv + v, vv
        uu, u = q * uu + u, uu
        e = -e
        q, rr = divmod(a, b)
    return -sa * e * uu, sb * e * vv

def inverse_modulaire(a, n):
    d, e = euclide_etendu(a, n)
    return d

def expo_modulaire(e, b, n):
    res = b
    while (e > 1):
        res = (res * b) % n
        e -= 1
    #print(e - 1, " fois et modulo")
    return res

def dec_to_bin(n):
    return bin(n)

def expo_rapide(e, b, n):
    ebin = dec_to_bin(e)
    nbre = len(ebin) - 1
    bcarre = b ** 2
    res = 1
    for i in ebin:
        if (i == '1'):
            res *= bcarre ** nbre
        nbre -= 1
    return res % n



    
