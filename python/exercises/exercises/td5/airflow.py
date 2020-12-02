# -*- coding: utf-8 -*-
"""
Modelling the airflow
"""
from load_foil import load_foil
from interpolation import interpolation
import numpy as np
import matplotlib.pyplot as plt
#import matplotlib as mpl
from integer import derivate
from scipy.integrate import simps as simps


def flow(X, Y, h , a):
    """
    Computes the array representing a curve describing the airflow above or below the wing.
    X: array of tabulated points (abscissas)
    Y: array of tabulated values (ordinates)
    a: constant in [0;1]
    h: maximal or minimum height of the airfoil
    """
    assert (0 <= a <= 1)
    
    res = []
    n = len(X)
    for i in range(n):
        y = (1 - a) * Y[i] + a * 3 * h
        res.append(y)
        
    return res
    

def flows_all(X, Y, n, h):
    """
    Computes the arrays representing the curves describing the airflow above or below the wing.
    X: array of tabulated points (abscissas)
    Y: array of tabulated values (ordinates)
    n: number of curves wanted above or below the wing
    h: minimum or maximal height of the airfoil
    """
    RES = []
    s = (1 - 0) / n
    a = 0
    for i in range(n):
        res = flow(X, Y, h , a)
        a += s
        RES.append(res)
    return RES



def plot_airflows():
    """
    Plots the wing and the airflow above and below that wing.
    """
    
    (dim,ex,ey,ix,iy) = load_foil("boe106.dat")
    n = 100
    n_up = 20
    n_down = 10
    
    EX, EY = interpolation(ex, ey, n)
    IX, IY = interpolation(ix, iy, n)
    
    hmax = max(EY)
    hmin = min(IY)
    UP = flows_all(EX, EY, n_up, hmax)
    DOWN = flows_all(IX, IY, n_down, hmin)
    
    plt.grid(True)
    plt.plot(EX, UP[0], color="blue")
    for i in range(1, n_up):
        plt.plot(EX, UP[i], color="blue", linestyle="--")
    
    plt.plot(IX, DOWN[0], color="red")
    for i in range(1, n_down):
        plt.plot(IX, DOWN[i], color="red", linestyle="--")
   
    #plt.axes().set_aspect('equal')
    plt.xlabel("Abscissa")
    plt.ylabel("Ordinate")
    plt.show()
    
    
#plot_airflows() 



def arc_length_old(x, y):
    n = 40
    h = 1/n
    DY = []
    for i in range(len(y) - 1):
        dx = derivate(y, i, h)
        DY.append(np.sqrt(1 + dx**2))
    
    npts = len(x) - 1
    arc = np.sqrt((x[1] - x[0])**2 + (DY[1] - DY[0])**2)
    for k in range(1, npts):
        arc = arc + np.sqrt((x[k] - x[k-1])**2 + (DY[k] - DY[k-1])**2)
    return arc




def arc_length(X, Y):
    """
    Computes the length of a curve on the entire interval.
    X: array of tabulated points of the curve (abscissas)
    Y: array of tabulated values of the curve (ordinates)
    """
    n = 40
    h = 1/n
    DY = []
    for i in range(len(Y) - 1):
        dx = derivate(Y, i, h)
        DY.append(np.sqrt(1 + dx**2))
    
    #use of scipy simpsons inegration method
    arc = simps(DY, X[:-1])
    return arc




    
def dynamic_pressure(X, Y):
    """
    Computes an array contening the dynamic pressure above or below the wing.
    X: array of tabulated points of the wing (abscissas)
    Y: array of tabulated values of the wing (ordinates)
    """
    rho = 1.225 #kg/m^3 at sea level, at 15°C
    # 1,316 at -5°C
    
    RES = 0
    V =  arc_length(X,Y)
    RES=(0.5 * rho * (V ** 2))
    return RES




def min_list(L):
    """
    Finds the minimum in a list of list L.
    L: list of list
    """
    res = L[0][0]
    for i in range(len(L)):
        x = min(L[i])
        if (res > x):
            res = x
    return res







def pressure_map():
    """
    Draw the pressure map around an airfoil.
    """
    #Loading of data
    (dim,ex,ey,ix,iy) = load_foil("boe106.dat")
    n = 1000
    n_up = 150
    n_down = 150
    m = n/2

    # Computation of the airfoil
    EX, EY = interpolation(ex, ey, n)
    IX, IY = interpolation(ix, iy, n)

    # Creating the array of curves
    hmax = max(EY)
    hmin = min(IY)
    UP = flows_all(EX, EY, n_up, hmax)
    UP.reverse()
    DOWN = flows_all(IX, IY, n_down, hmin)
    Y =  DOWN + UP

    # create the map
    mini = min_list(DOWN) * m
    # (max(EY) - min(EY)) * m and (max(EX) - min(EX)) * m
    p_map = np.zeros([int((0.3+0.1)*m),int(1*m)])
    
    
    #computing the pressure for each curve
    for i in range(0, n_up + n_down):
        Y2 = Y[i]
        RES = dynamic_pressure(EX, Y2)
        #print(RES)
        for j in range(n):
            p_map[int(m * Y2[j])+int(abs(mini))] [int(m * EX[j])] = RES
            
            
    # ajusting the value of the inside of the wing to the min of pressure for graphical purpose
    mini_p = np.min(p_map[np.nonzero(p_map)])
    p_map[p_map == 0] = mini_p
    
    
#    cmap2 = mpl.colors.LinearSegmentedColormap.from_list('my_colormap', ['black','red','yellow','white'], 256)
#    cmap2.set_over('1')
#    cmap2.set_under('0.7')

    plt.title("Dynamic pressure map")
    plt.imshow(p_map, cmap='hot', aspect='auto', interpolation='nearest', origin='lower')
    plt.colorbar(fraction=0.046, pad=0.04)
    
    plt.show()


#pressure_map()
    
