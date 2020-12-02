from random import randint, randrange
from exo1 import expo_rapide

def crible_eratosthene(n):
    """retourne la liste des nombres premiers <= n (crible d'eratosthene)"""
    if n<2:
        return []
    n += 1
    tableau = [False,False] + [True]*(n-2)
    tableau[2::2] = [False]*((n-2)//2 + n%2) 
    premiers = [2] 
    racine = int(n**0.5)
    racine = racine + [1,0][racine%2] 
    for i in range(3, racine+1, 2):
        if tableau[i]:
            premiers.append(i)
            tableau[i::i] = [False]*((n-i)//i + int((n-i)%i>0)) 
    for i in range(racine, n, 2):
        if tableau[i]:
            premiers.append(i)
    return premiers

def fermat(n ,t):
    if (n == 1):
        return True
    res = 1
    for i in range(t):
        rdm = randint(1, n - 1)
        if (expo_rapide(n-1, rdm, n) != 1):
            return False
    return True

def miller_rabin(n, k):
    if n == 2 or n == 3:
        return True

    if n % 2 == 0:
        return False

    r, s = 0, n - 1
    while s % 2 == 0:
        r += 1
        s //= 2
    for _ in range(k):
        a = randrange(2, n - 1)
        x = pow(a, s, n)
        if x == 1 or x == n - 1:
            continue
        for _ in range(r - 1):
            x = pow(x, 2, n)
            if x == n - 1:
                break
        else:
            return False
    return True

print(miller_rabin(561, 100))



