from load_foil import load_foil
import numpy as np
import matplotlib.pyplot as plt



def spline(X, Y, yp1, ypn, arg):
    """
    Computes the array containing the second derivatives of the interpolating function f.
    X: array of tabulated points (abscissas)
    Y: array of tabulated values (ordinates)
    yp1: values of the first derivative at X[0] of f
    yp1: values of the first derivative at X[-1] of f
    arg: 0      if natural cubic spline wanted
         !=0     else 
    """
    assert(len(X)==len(Y))
    n = len(X)
    len_u = n -1 
    u = [0] * len_u
    Y2 = [0] * n
    if (arg == 0):
        #if  the lower boundary condition is set to be natural
        Y2[0],  u[0] = 0.0, 0.0
    else:
         #if the user wanted to specify first derivatives
        Y2[0] = -0.5
        u[0] = (3.0 / (X[1] - X[0])) * ((Y[1] - Y[0]) / (X[1] - X[0]) - yp1)
        
    for i in range(1, len_u):
        sig = (X[i] - X[i - 1]) / (X[i + 1] - X[i - 1])
        p = sig * Y2[i - 1] + 2.0
        Y2[i] = (sig - 1.0) / p
        u[i] = (Y[i + 1] - Y[i]) / (X[i + 1] - X[i]) - (Y[i] - Y[i - 1]) / (X[i] - X[i - 1])
        u[i] = 6.0 * u[i] / (X[i + 1] - X[i - 1]) - sig * u[i - 1]
        u[i] /= p
        
    if (arg == 0):
        qn, un = 0.0, 0.0
    else:
        qn = 0.5
        un = (3.0 / (X[n - 1] - X[n - 2])) * (ypn - (Y[n - 1] - Y[n - 2]) / (X[n - 1] - X[n - 2]))
    Y2[n-1] = (un - qn * u[n - 2]) / (qn * Y2[n - 2] + 1.0)
    for k in range(n - 2, -1, -1):
        Y2[k] = Y2[k] * Y2[k + 1] + u[k]
    return np.array(Y2)




def splint(XA, YA, Y2A, x, ixa, jxa):
    """
    Computes a interpolated value at point x knowing the index of XA where it should belong [ixa, jxa].
    XA: array of tabulated points (abscissas)
    YA: array of tabulated values (ordinates)
    Y2A: array of tabulated values of the second derivatives of the interpolating function
        see the function spline for more detail
    x: point where the interpolation is made
    ixa: lower index of XA such as XA[ixa] <= x
    jxa: upper index of XA such as x <= XA[jxa]
    Remark: XA should be ordered and the subdivision between two intervals should be constant
    """
    #checking if x is in the right intervall
    #i,e: ixa and jxa are the right index of XA
    if not(XA[ixa] <= x <= XA[jxa]):
        ixa +=1
        jxa += 1
    h = XA[jxa] - XA[ixa]
    a, b = 0.0 , 0.0
    a = (XA[jxa] - x) / h
    b = (x - XA[ixa]) / h
    tmp = (a**3 - a) * Y2A[ixa] + (b**3 - b) * Y2A[jxa]
    y = a * YA[ixa] + b *YA[jxa] + tmp*h*h / 6.0
    return y, ixa, jxa



def interpolation(x,y,n):
    """
    Computes the abscissas and ordinates of the resulting interpolation.
    x: array of tabulated points (abscissas)
    y: array of tabulated values (ordinates)
    n: number of subintervals 
    """
    NATURAL = 0
    #OTHER = 1
    #length of subintervals 
    h = (x[-1] - x[0])/n
    arg = NATURAL
    # second derivatives
    Y2 = spline(x, y, 0, 0, arg)
    
    # current point
    a = x[0]
    # list of all points visited
    X = []
    # resulting interpolated values
    Y = []
    # index of XA
    ixa = 0
    jxa = 1
    for i in range(n):
        X.append(a)
        Yi, ixa, jxa = splint(x, y, Y2, a, ixa, jxa)
        Y.append(Yi)
        #update to the next point
        a += h
    return X, Y
    


def plot():
    """
    PLot the cubic spline interpolation of the airfoil.
    """
    (dim,ex,ey,ix,iy) = load_foil("boe106.dat")
    n = 100
    
    EX, EY = interpolation(ex, ey, n)
    IX, IY = interpolation(ix, iy, n)
    
    plt.grid(True)
    plt.plot(EX, EY, color="blue")
    plt.plot(IX, IY, color="red")
    plt.plot(ex, ey, color="blue", linestyle="None", marker="o", markersize=3)
    plt.plot(ix, iy, color="red", linestyle="None", marker="o", markersize=3)
    
    plt.xlabel("Abscissa")
    plt.ylabel("Ordinate")
    
    plt.show()    
    


#plot()
















"""


def spline_original(X, Y, n, yp1, ypn):
    u = np.zeros((1, n - 1))
    Y2 = [0 for k in range(n - 1)]
    if (yp1 > 0.99e30):
        Y2[1] = u[1] = 0
    else:
        Y2[1] = -0.5
        u[1] = (3.0 / (X[2] - X[1])) * ((Y[2] - Y[1]) / (X[2] - X[1]) - yp1)
    for i in range(2, n - 1):
        sig = (X[i] - X[i - 1]) / (X[i + 1] - X[i - 1])
        p = sig * Y2[i - 1] + 2.0
        Y2[i] = (sig - 1.0) / p
        u[i] = (Y[i + 1] - Y[i]) / (X[i + 1] - X[i]) - (Y[i] - Y[i - 1]) / (X[i] - X[i - 1])
        u[i] = (6.0 * u[i] / (X[i + 1] - X[i - 1]) - sig * u[i - 1]) / p
    if (ypn > 0.99e30):
        qn = un = 0.0
    else:
        qn = 0.5
        un = (3.0 / (X[n] - X[n - 1])) * (ypn - (Y[n] - Y[n - 1]) / (X[n] - X[n - 1]))
    Y2[n] = (un - qn * u[n - 1]) / (qn * Y2[n - 1] + 1.0)
    for i in range(n - 1, 0, -1):
        Y2[k] = Y2[k] * Y2[k + 1] + u[k]
    return (np.array(Y2))



def splint_original(xa, ya, y2a, x):
    n = len(xa)
    klo = 1
    khi = n
    while (khi - klo > 1):
        k = (khi + klo) >> 1
        if (xa[k] > x):
            khi = k
        else:
            klo = k
    h = xa[khi] - xa[klo]
    if (h == 0.0):
        print("ERROR CHIEF !")
    a, b = 0.0 , 0.0
    a = (xa[khi] - x) / h
    b = (x - xa[klo]) / h
    tmp = (a**3 - a) * y2a[klo] + (b**3 - b) * y2a[khi]
    y = a * ya[klo] + b *ya[khi] + tmp*h*h / 6.0
    return y


def interpolation(x,y,n):
    NATURAL = 0
    #OTHER = 1
    h = (x[-1] - x[0])/n
    arg = NATURAL
    Y2 = spline(x, y, 0, 0, arg)
    
    a = x[0]
    X = []
    Y = []
    for i in range(n):
        X.append(a)
        Y.append(splint_original(x, y, Y2, a))
        a += h
    return X, Y
    
"""