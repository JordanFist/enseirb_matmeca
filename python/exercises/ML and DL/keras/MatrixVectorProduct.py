import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches
%matplotlib inline

def generate_data(nb_samples):
    X = np.zeros((nb_samples, 2))
    y = np.zeros(nb_samples)
    for i in range(nb_samples):
        X[i][0] = np.random.normal()
        X[i][1] = np.random.normal()
        if (X[i][0] - X[i][1] > 0.5) or (X[i][0] - X[i][1] < -0.5):
            y[i] = -1
        else:
            y[i] = +1
    return [X, y]

def visualize(X, y):
    figsize = 5
    fig = plt.figure(figsize=(figsize,figsize))
    ax = plt.subplot(111)
    x_min, x_max = X[:, 0].min() - 1, X[:, 0].max() + 1
    y_min, y_max = X[:, 1].min() - 1, X[:, 1].max() + 1
    for i in range(X.shape[0]):
        p = patches.Circle((X[i][0], X[i][1]), 0.05, color=plt.cm.coolwarm((y[i]+1)/2))
        ax.add_patch(p)
    ax.set_xlim(x_min, x_max)
    ax.set_ylim(y_min, y_max)
    plt.show()
    return

def g(M):
  for i in range(M.shape[0]):
    for j in range(M.shape[1]):
      M[i, j] = max(0, M[i, j])
  
def mult(M, v):
  (rows, cols) = M.shape
  N = np.zeros(M.shape)
  for i in range (rows):
    for j in range (cols):
      for k in range(v.shape[0]):
        N[i, j] += M[i, k] * v[k, j]
  return N

R = np.array([[-1/2,np.sqrt(3)/2], [-np.sqrt(3)/2, -1/2]])
P = np.array([[1,0], [0,0]])
W = np.array([[0.5, -0.5], [-0.5, 0.5]])

N = 100
[X, y] = generate_data(N)
visualize(X, y)

Q = mult(X, R)
visualize(Q, y)
Q = mult(X, P)
visualize(Q, y)
Q = mult(X, W)
g(Q)
visualize(Q, y)

################################################################################

import cv2 # OpenCV
import numpy as np
import matplotlib.pyplot as plt

#For COLAB
import os
os.environ["ENABLE_CV2_IMSHOW"] = 'true'

#Works on Colab (download an image):
!wget https://www.labri.fr/perso/vlepetit/teaching/ml_dl_enseirb/susan.png
!ls
susan = cv2.imread('susan.png',0)

# If you do not use Colab, download the image first using the link
# above, and download the image (using the correct path)
# using the command below:
#susan = cv2.imread('CHANGE_PATH/susan.png',0)

figsize = 15
plt.figure(figsize=(figsize,figsize))
plt.imshow(susan, cmap='gray')

def conv2D(f, I):
  R = np.zeros(I.shape, np.float) # np.uint8 affichage en int (marche moins bien)
  for i in range(I.shape[0]):
    for j in range(I.shape[1]):
      if (i == 0 or i == I.shape[0]-1 or j == 0 or j == I.shape[1]-1):
        R[i, j] = I[i, j]
      else:
        res = 0
        for k in range(-1, 2, 1):
          for l in range(-1, 2, 1):
              res += f[k+1, l+1] * I[i+k, j+l]
        R[i, j] = res
  return R

f = np.array([[0,0,0],[1,0,-1],[0,0,0]]) #contours horizontaux
d = np.array([[-1,0,0],[0,0,0],[0,0,1]]) #relief negatif
g = np.array([[1/16,1/8,1/16],[1/8,1/4,1/8],[1/16,1/8,1/16]]) #filtre gaussien (smooth) (faire plusieurs fois -> flou)
l = np.array([[1,1,1],[1,-8,1],[1,1,1]]) #filtre laplacien (contour)

C = conv2D(d, susan)

plt.figure(figsize=(figsize,figsize))
plt.imshow(C, cmap='gray')
