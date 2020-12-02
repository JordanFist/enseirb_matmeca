from numpy import *
import matplotlib.pyplot as plt


precision = 18

L = [log(1 + 2 ** (-k)) for k in range(precision + 2)]
A = [arctan(2 ** (-k)) for k in range(precision + 2)]

#for k in range(10):
#   print(L[k], " ")
#   print(A[k], "\n")

def expo(x):
    i = 0
    while (x < 0):
        x += L[0]
        i += 1
    while (x >= L[0]):
        x -= L[0]
        i -= 1
    k = 0
    y = 1
    while (k <= precision):
        while (x >= L[k]):
            x = x - L[k]
            y = y + y * 2**(-k)
        k = k + 1
    return (y + y * x) * 2 ** (-i)

def ln(x):
    i = 0
    while (x < 1):
        x = x * 2
        i += 1
    while (x > 2):
        x = x / 2
        i -= 1
    k = 0
    y = 0
    p = 1
    while (k <= precision):
        while (x >= p + p * 2 ** (-k)):
            y = y + L[k]
            p = p + p * 2 ** (-k)
        k = k + 1
    return y + (x / p - 1) - i * L[0]

def arctang(x):
    if (x < 0):
        return - arctan(-x)
    if (x > 1):
        return (pi / 2) - arctan(1 / x)
    k = 0
    y = 1
    r = 0
    while (k <= precision):
        while ((x < y * 2 ** (-k)) and (k <= precision)):
            k = k + 1
        xp = x - y * 2 ** (-k)
        y = y + x * 2 ** (-k)
        x = xp
        r = r + A[k]
    return (r + x / y)
               
def tang(x):
    if (x < 0):
        return -tang(-x)
    if (x > pi):
        return tang(x % pi)
    if (x > pi / 2):
        return -tang(pi - x)
    if (x > pi / 4):
        return 1 / (tang((pi/2) - x))
    k = 0
    n = 0
    d = 1
    while (k <= precision):
        while (x >= A[k]):
            x = x - A[k]
            np = n + d * 2 ** (-k)
            d = d - n * 2 ** (-k)
            n = np
        k = k + 1
    return (n + x * d) / (d - x * n)


X1 = [k / 10000 for k in range(-10000, 50000)]
X2 = [k / 10000 for k in range(1, 50000)]
X3 = [k / 10000 for k in range(-50000, 50000)]
X4 = [k / 10000 for k in range(0, 100000)]

Y_c1 = [expo(x) for x in X1]
Y_c2 = [ln(x) for x in X2]
Y_c3 = [arctang(x) for x in X3]
Y_c4 = [tang(x) for x in X4]

Y_m1 = [exp(x) for x in X1]
Y_m2 = [log(x) for x in X2]
Y_m3 = [arctan(x) for x in X3]
Y_m4 = [tan(x) for x in X4]


def test_exp():
    #erreur exp
    max_error_rel = 0
    max_error_abs = 0

    for i in range(len(X1)):
        error = abs(Y_c1[i] - Y_m1[i])
        if (error > max_error_abs):
            max_error_abs = error
        if(Y_m1[i] != 0):
            error = abs(error / Y_m1[i])
            if (error > max_error_rel):
                max_error_rel = error

    print("Exponentielle :")
    print("Erreur relative max : ", max_error_rel)
    print("Erreur absolue max : ", max_error_abs)

    plt.plot(X1, Y_c1, label="exp CORDIC")
    plt.plot(X1, Y_m1, label="exp numpy")
    
    plt.axhline(0, color="black")
    plt.axvline(0, color="black")
    plt.legend()
    plt.show()
    
    
def test_ln():
    #erreur ln
    max_error_rel = 0
    max_error_abs = 0

    for i in range(len(X2)):
        error = abs(Y_c2[i] - Y_m2[i])
        if (error > max_error_abs):
            max_error_abs = error
        if(Y_m2[i] != 0):
            error = abs(error / Y_m2[i])
            if (error > max_error_rel):
                max_error_rel = error

    print("Logarithme :")
    print("Erreur relative max : ", max_error_rel)
    print("Erreur absolue max : ", max_error_abs)

    plt.plot(X2, Y_c2, label="ln CORDIC")
    plt.plot(X2, Y_m2, label="ln numpy")

    plt.axhline(0, color="black")
    plt.axvline(0, color="black")
    plt.legend()
    plt.show()
    

def test_arctan():
    #erreur arctan
    max_error_rel = 0
    max_error_abs = 0

    for i in range(len(X3)):
        error = abs(Y_c3[i] - Y_m3[i])
        if (error > max_error_abs):
            max_error_abs = error
        if(Y_m3[i] != 0):
            error = abs(error / Y_m3[i])
            if (error > max_error_rel):
                max_error_rel = error

    print("Arctangente :")
    print("Erreur relative max : ", max_error_rel)
    print("Erreur absolue max : ", max_error_abs)

    plt.plot(X3, Y_c3, label="arctan CORDIC")
    plt.plot(X3, Y_m3, label="arctan numpy")

    plt.axhline(0, color="black")
    plt.axvline(0, color="black")
    plt.legend()
    plt.show()

    
def test_tan():
    #erreur tan
    max_error_rel = 0
    max_error_abs = 0
    
    for i in range(len(X4)):
        error = abs(Y_c4[i] - Y_m4[i])
        if (error > max_error_abs):
            max_error_abs = error
        if(Y_m4[i] != 0):
            error = abs(error / Y_m4[i])
            if (error > max_error_rel):
                max_error_rel = error

    print("Tangente :")
    print("Erreur relative max : ", max_error_rel)
    print("Erreur absolue max : ", max_error_abs)

    plt.plot(X4, Y_c4, label="tan CORDIC")
    plt.plot(X4, Y_m4, label="tan numpy")
    
    plt.axhline(0, color="black")
    plt.axvline(0, color="black")
    plt.legend()
    plt.show()


test_ln()
test_exp()
test_arctan()
test_tan()
