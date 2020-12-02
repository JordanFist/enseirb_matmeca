import numpy as np
import matplotlib as plt
import copy

import Euler as eu



def Identite() :
    def truc(t, Y) :
        return Y
    return truc

def test_equa_diff_ordre_1_dim_1():

    Y0 = np.array([[1.]])
    t0 = -3
    tf = 5
    eps = 10e-2
    F = Identite()
    meth = eu.step_point_milieu
    tab = eu.meth_epsilon(Y0, t0, tf, eps, F, meth)

    return tab


def test_equa_diff_ordre_1_dim_2():

    Y0 = np.array([[1.,1.]])
    t0 = 0
    tf = 2
    eps = 10e-2
    F = Identite()
    meth = eu.step_point_milieu
    tab = eu.meth_epsilon(Y0, t0, tf, eps, F, meth)

    return tab

#tab = test_equa_diff_ordre_1_dim_1()
#print([tab[k][0][0] for k in range(len(tab))])

#eu.tracage(test_equa_diff_ordre_1_dim_1(), -3, 5, "test1")

eu.trace_quiver(test_equa_diff_ordre_1_dim_2(), 0, 2)

