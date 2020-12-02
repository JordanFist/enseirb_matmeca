import numpy as np
import matplotlib.pyplot as plt
import copy


# y(n+1) = y(n) + h F(t(n), y(n))



def compare_table(tab_init, tab_suivant, eps):
    
    N = len(tab_init)
    for i in range(N):
        if not((np.linalg.norm(tab_init[i] - tab_suivant[2*i]) < eps)) :
            return False
    return True


def meth_n_step(Y0, t0, N, h, F, meth) :
    
    Yk = Y0
    tk = t0
    tab = [Yk]
    for k in range(N):
        Yk = meth(Yk, tk, h, F)
        tk = t0 + h
        tab.append(Yk)

    return tab


    
    

def step_euler(Y, t, h, F): #y vector, t variable, h step, F function
    X = Y + h * F(t, Y)
    return X



def step_point_milieu(Y, t, h, F): #y vector, t variable, h step, F function
    Y_milieu = Y + h/2 * F(t, Y)
    X = Y + h * F(t  + h/2, Y_milieu)
    return X

def step_heun(Y, t, h, F): #y vector, t variable, h step, F function
    t_suivant = t + h
    pn1 = F(t, Y)
    Y_suivant = Y + h * pn1
    pn2 = F(t_suivant, Y_suivant)
    X = Y + h * (pn1 + pn2) / 2
    return X

def step_runge_kutta(Y, t, h, F):  #y vector, t variable, h step, F function
    
    t_intermediaire = t + 1/2 * h
    t_suivant = t + h

    pn1 = F(t, Y)
    yn2 = Y + 1/2 * h * pn1
    pn2 = F(t_intermediaire, yn2)
    yn3 = Y + 1/2 * h * pn2
    pn3 = F(t_intermediaire, yn3)
    yn4 = Y + h * pn3
    pn4 = F(t_suivant, yn4)

    X = Y + 1/6 * h * (pn1 + 2*pn2 + 2*pn3 + pn4)
    return X

def meth_epsilon(Y0, t0, tf, eps, F, meth) : #method is "step euler" or ...
    
    compteur_securite = 1
    limite_securite = 100
    N = 2
    h = (tf - t0) / N 
    tab_init = []
    tab_suivant = meth_n_step(Y0, t0, N, h, F, meth)

    cond = False
    while ((not(cond) and (compteur_securite < limite_securite))) :

        N = N*2
        h = (tf - t0) / N
        tab_init = copy.deepcopy(tab_suivant)
        tab_suivant = meth_n_step(Y0, t0, N, h, F, meth)
        cond = compare_table(tab_init, tab_suivant, eps)
        compteur_securite += 1
    return tab_suivant


def tracage(Y_init, t0, tf, nom_chaine_de_car):
    Y = []
    n = len(Y_init)
    for i in range(len(Y_init)):
        Y.append(Y_init[i][0][0])
    X = np.linspace(t0, tf, n)
    plt.plot(X, Y, label=nom_chaine_de_car)
    plt.legend()
    plt.show()



def trace_quiver(Y_init, t0, tf):
    n = len(Y_init)
    Y = []
    Z = []
    
    K = n*1j

    for i in range(len(Y_init)):
        Y.append(Y_init[i][0][0])
        Z.append(Y_init[i][0][1])
        X, X_2 = np.meshgrid(np.arange(t0, tf, 2/33),np.arange(t0, tf, 2/33))
#mettre un pas de type n*1j apparemment...

        #X,X_2 = np.linspace(t0, tf, n), np.linspace(t0, tf, n) 
    U = Y
    V = Z

    print(n)
    print(len(X_2[0]))

    print(X_2[0])
    print(X)
    #print(len(V))

    #plt.figure()
    #plt.title('Arrows scale with plot width, not view')
    #Q = plt.quiver(X, Y, U, V, units='width')
    #qk = plt.quiverkey(Q, 0.9, 0.9, 2, r'$2 \frac{m}{s}$', labelpos='E',
    #                   coordinates='figure')
    #plt.scatter(X, Y, color='k', s=5)
    
    #plt.show()
