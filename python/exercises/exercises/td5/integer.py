from __future__ import division
from load_foil import load_foil
from interpolation import interpolation
import numpy.polynomial.polynomial as nppoly
import math as m

def derivate(Y, a, h):
    """
    Compute the derivate of the function, by dividing the difference of two point by an infinitesimal element.
    Y : array of tabulated points of the curve (ordinates)
    a : position of the integration point.
    h : infinitesimal element
    """
    return ((Y[int(a) + 1] - Y[int(a)]) / h)

def sum_1(Y, a, h, n):
    """
    Sub function of the simpson methode, compute the start of segment points.
    Y : array of tabulated points of the curve (ordinates)
    h : infinitesimal element
    n : number of point to be integrated.
    """
    s = 0
    for i in range (1, int(n)):
        s += m.sqrt(1 + derivate(Y, a + i, h)**2)
    return s

def sum_2(Y, a, h, n) :
    """
    Sub function of the simpson methode, compute the middle-segment points.
    Y : array of tabulated points of the curve (ordinates)
    h : infinitesimal element
    n : number of point to be integrated.
    """
    s = 0
    for i in range (int(n)):
        s += m.sqrt(1 + derivate([(Y[int(a + i)]+Y[int(a+(i+1))])/2,
                                  (Y[int(a + (i+1))]+Y[int(a+(i+2))])/2],
                                 0, h))
    return s

def simpson(Y, i, n, h):
    """
    Simpson method. 
    Y : array of tabulated points of the curve (ordinates)
    i : start of the integration
    n : number of points to be integrated
    h : infinitesimal element
    """
    s1 = sum_1(Y, i, h, n)
    s2 = sum_2(Y, i, h, n)
    return h * ((m.sqrt(1 + derivate(Y, i, h)**2) + m.sqrt(1 + derivate(Y, n-2, h)**2))/6 + s1/3 + (s2*2)/3)

def middle_point(Y, i, n, h):
    return h * sum_2(Y, i, h, n)

def extract(X, Y, end, ind, n):
    """
    Select the point belonging to the spline.
    X : array of tabulated points of the curve (abscissas)
    Y : array of tabulated points of the curve (ordinates)
    ind : the index of the first point of the spline
    end : the value of the last point of the spline
    n : the total number of points in X and Y
    """
    res_x = []
    res_y = []
    while(ind != n-3 and X[ind] < end):
        res_x.append(X[ind])
        res_y.append(Y[ind])
        ind+=1
    res_x.append(X[ind])
    res_y.append(Y[ind])
    return (res_x, res_y, ind)

def integer(method):
    """
    Compute the length of all splines of the wing.
    method : the approximation method chosen, either simpson or middle_point.
    """
    n = 100
    (dim,ex,ey,ix,iy) = load_foil("boe106.dat")
    (EX, EY) = interpolation(ex, ey, n)
    (IX, IY) = interpolation(ix, iy, n)
    I_e = []
    I_i = []
    a = 0
    b = 0
    for i in range (1, len(ex)):
        (simp_x, simp_y, b) = extract(EX, EY, ex[i], b, n)
        I_e.append(method(EY, a, len(simp_x), 1/n))
        (simp_x, simp_y, b) = extract(IX, IY, ix[i], b, n)
        I_i.append(method(IY, a, len(simp_x), 1/n))
        a = b
    return I_e, I_i

print(integer(middle_point))
print(integer(simpson))
