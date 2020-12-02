import Tictactoe 
from starterTictactoe import getresult
from random import randint,choice
import numpy as np

#1.
def compteParties(b):
    if b.is_game_over():
        return (0, 1)
    (nbnoeuds, nbfeuilles) = (0, 0)
    for m in b.legal_moves():
        nbnoeuds += 1
        b.push(m)
        (n, f) = compteParties(b)
        b.pop()
        nbnoeuds += n
        nbfeuilles += f
    return (nbnoeuds, nbfeuilles)

#2.
""" Si je suis sur un niveau ami et que j'ai un 1 qui remonte, on va pas voir les autres, on remonte 1
Si je suis sur un niveau ennemi et que j'ai un -1 qui remonte, on va pas voir les autres, on remonte -1
sur un niveau ennemi avec des 0 et des 1 on remonte le 0
"""

def strategieGagnante(b, player = 'X'):
    if (b.is_game_over()):
        return getresult(b)
    nextplayer = '0' if player == 'X' else 'X'
    best = -1 if player == 'X' else 1
    for m in b.legal_moves():
        b.push(m)
        res = strategieGagnante(b, nextplayer)
        b.pop()
        if player == 'X':
            best = max(best, res)
            if (best == 1):
                return 1
        else:
            best = min(best, res)
            if (best == -1):
                return -1
    return best

#3
"""
def MiniMax(etat):
    si EstFeuille(etat):
        return Eval(etat, Ami)
    Meilleur = -infini
    pour tous successeur s de etat faire:
        Meilleur = max(Meilleur, MinMax(s))
    return Meilleur

def MinMax(etat):
    si EstFeuille(etat):
        return Eval(etat, Ennemi)
    Pire = +infini
    pour tous successeur s de etat faire:
        Pire = min(Pire, MaxMin(s))
    return Pire
"""     
count = 0

def MaxMin(b): #b = board
    global count
    count += 1
    if b.is_game_over():
        return getresult(b)
    best = -np.inf #best = -1 valide aussi
    for i in b.legal_moves():
        b.push(i)
        best = max(best, MinMax(b))
        b.pop()
        if best == 1: #ameliorer l'algo si on a la valeur max ca sert a rien de continuer
            return 1
    return best

def MinMax(b):
    global count
    count += 1
    if b.is_game_over():
        return getresult(b)
    pire = np.inf
    for i in b.legal_moves():
        b.push(i)
        pire = min(pire, MaxMin(b))
        b.pop()
        if pire == -1:
            return -1
    return pire

board = Tictactoe.Board()
#print(compteParties(board))
print(strategieGagnante(board)) #on obtient 0 soit il n'est pas possible de trouver une strategie gagnante au morpion
print(MaxMin(board))
print("noeuds explorés = ", count)
