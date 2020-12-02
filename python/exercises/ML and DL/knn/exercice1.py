#============================================================================
# 1. Getting Started
#============================================================================

from sklearn import datasets
iris = datasets.load_iris()

#print(iris)

iris_X = iris.data #Les données iris dans un tableau sans les virgules
iris_y = iris.target # 0=setosa, 1=versicolor, 2=virginica

#print(iris_X)

import numpy as np
indices = np.random.permutation(len(iris_X))
iris_X_train = iris_X[indices[:-40]]
iris_y_train = iris_y[indices[:-40]]
iris_X_valid = iris_X[indices[-40:-20]]
iris_y_valid = iris_y[indices[-40:-20]]
iris_X_test = iris_X[indices[:-20]]
iris_y_test = iris_y[indices[:-20]]

#============================================================================
# 2. Nearest Neighbor Classifier
#============================================================================

from sklearn.neighbors import KNeighborsClassifier

knn = KNeighborsClassifier(n_neighbors = 1) #modifier k et tester
knn.fit(iris_X_train, iris_y_train)
res = knn.predict(iris_X_valid)
numberOfMistakes = 0

for i in range(0, len(iris_y_valid)):
  if (res[i] != iris_y_valid[i]):
     numberOfMistakes += 1
#print(numberOfMistakes)

#============================================================================
# 3. Linear Support Vector Machine Classifier
#============================================================================

from sklearn import svm

svc = svm.SVC(kernel='linear', C = 2) #modifier C et tester
svc.fit(iris_X_train, iris_y_train)
res = svc.predict(iris_X_valid)

for i in range(0, len(iris_y_valid)):
  if (res[i] != iris_y_valid[i]):
    numberOfMistakes += 1
#print(numberOfMistakes)

#============================================================================
# 4. Non Linear Support Vector Machine Classifier
#============================================================================

svc = svm.SVC(kernel='rbf', gamma = 0.1, C = 2)
svc.fit(iris_X_train, iris_y_train)
res = svc.predict(iris_X_valid)

for i in range(0, len(iris_y_valid)):
  if (res[i] != iris_y_valid[i]):
    numberOfMistakes += 1
#print(numberOfMistakes)

#============================================================================
# 5. Visualisation
#============================================================================

iris_X = iris.data[:, :2]
indices = np.random.permutation(len(iris_X))
iris_X_train = iris_X[indices[:-40]]
iris_y_train = iris_y[indices[:-40]]
iris_X_valid = iris_X[indices[-40:-20]]
iris_y_valid = iris_y[indices[-40:-20]]
iris_X_test = iris_X[indices[:-20]]
iris_y_test = iris_y[indices[:-20]]

import matplotlib.pyplot as plt

def plot_contours(ax, clf, xx, yy, **params):
  Z = clf.predict(np.c_[xx.ravel(), yy.ravel()])
  Z = Z.reshape(xx.shape)
  out = ax.contourf(xx, yy,Z, **params)
  return out

def make_meshgrid(x, y, h=.02):
  x_min, x_max = x.min() - 1, x.max() + 1
  y_min, y_max = y.min() - 1, y.max() + 1
  xx, yy = np.meshgrid(np.arange(x_min, x_max, h), np.arange(y_min, y_max, h))
  return xx, yy

svc = svm.SVC(kernel='rbf', gamma=0.1, C=2)
pred = svc.fit(iris_X_train, iris_y_train)

U, V = iris_X_train[:, 0], iris_X_train[:,1]
xx, yy = make_meshgrid(U, V)

figsize = 10
fig = plt.figure(figsize=(figsize, figsize))
ax = plt.subplot(111)
plot_contours(ax, svc, xx, yy, cmap=plt.cm.coolwarm, alpha=0.8)
ax.scatter(U, V, c=iris_y_train, cmap=plt.cm.coolwarm, s=20, edgecolors='k')
ax.set_xlim(xx.min(), xx.max())
ax.set_ylim(yy.min(), yy.max())
plt.show()
                                    