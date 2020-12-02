import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches
%matplotlib inline

def generate_training_data(nb_samples):
  X = np.zeros((nb_samples, 2))
  y = np.zeros(nb_samples)
  for i in range(nb_samples):
    c = np.random.randint(2)
    if c == 0:
      y[i] = +1
      X[i][0] = np.random.normal()
      X[i][1] = np.random.normal()
    else:
      y[i] = -1
      r = np.random.normal(5)
      if r < 0:
        r = 0
      theta = np.random.random() * 2 * np.pi
      X[i][0] = r * np.cos(theta)
      X[i][1] = r * np.sin(theta)
  return [X, y]
    
class AdaBoostClassifier:
  def __init__(self, X_train, y_train):
    self.X_train = X_train
    self.N = self.X_train.shape[0]
    self.weights = np.ones(self.N) / self.N
    self.y_train = y_train
    self.total_nb_weak_learners = 0
    
  def bounded_random_weak_learner(self, u_min, u_max, v_min, v_max):
    tab = [-1, 1]
    c = np.random.randint(2)
    s = tab[np.random.randint(2)]
    if c == 0:
      return [c, s, np.random.randint(u_min, u_max)]
    else:
      return [c, s, np.random.randint(v_min, v_max)]
    
  def random_weak_learner(self):
    U, V = self.X_train[:, 0], self.X_train[:, 1]
    u_min, u_max = U.min(), U.max()
    v_min, v_max = V.min(), V.max()
    return self.bounded_random_weak_learner(u_min, u_max, v_min, v_max)

  def weak_learner(self, coord, threshold, sign, u, v):
    if ((coord == 0 and u > threshold) or (c == 1 and v > threshold)):
      return sign
    else:
      return -sign
    
    
  def weighted_weak_learner_error(self, wl):
    r = 0
    for i in range(N):
      if (y_train[i] != weak_learner(wl[0], wl[1], wl[2], X_train[i, 0], X_train[i, 1])):
        r += weights[i]
    return r
    
    
  def weight_sum(self, wl):
    r = 0
    for i in range(N):
      r += weights[i] * weak_learner(wl[0], wl[1], wl[2], X_train[i, 0], X_train[i, 1]) * y_train[i]
    return r
    
  def partial_prediction(self, nb_weak_learners, u, v):
    r = 0
    for i in range(nb_weak_learners):
      r += alphas[i] * weak_learner(weak_learners[j, 0], weak_learners[j, 1], weak_learners[j, 2], u, v)
    if (r > 0):
      return 1
    else: 
      return -1
    
    
  def partial_classification_error(self, nb_weak_learners):
    err = 0
    for i in range (0,nb_weak_learners):
      p = partial_prediction(nb_weak_learners, X_train[i, 0], X_train[i, 1])
      if p != y_train[i]:
        err += 1
    return err
    

  def init_learn(self, total_nb_weak_learners, nb_trials):
    self.total_nb_weak_learners = total_nb_weak_learners
    self.alphas = np.zeros(total_nb_weak_learners)
    self.weak_learners = np.zeros((self.total_nb_weak_learners, 3))
    self.total_nb_weak_learners = total_nb_weak_learners
    self.nb_trials = nb_trials
    self.index_current_weak_learner = 0
  
#    def learn_one_step(self):
#        i = self.index_current_weak_learner
#        print(’Optimizing weak learner #’, i)
#          ...
#        for j in range(nb_trials):
#          ...
#        print(’ > Found error ’, best_error, ’wl = ’, best_wl)
#        r = self.weight_sum(best_wl)
#        self.weak_learners[i,:] = best_wl
#        self.alphas[i] = 0.5 * np.log((1+r)/(1-r))
#          ...
#        print(’> Current prediction error ’, self.partial_classification_error(i+1))
#    def learn(self, total_nb_weak_learners, nb_trials):
#        init_learn()
#        for i in range(self.total_nb_weak_learners):
#            learn_one_step()
  def predict(self, u, v):
    return 0
  
  def plot_contours(self, ax, xx, yy, **params):
    C = np.vectorize(self.predict)(xx.ravel(), yy.ravel())
    C = C.reshape(xx.shape)
    out = ax.contourf(xx, yy, C, **params)
    return out
  
  def plot_training_data(self, ax):
    min_r = self.weights.min()
    max_r = self.weights.max()
    for i in range(X_train.shape[0]):
      if max_r - min_r > 0.00001:
        r = 0.1 + 0.1 * (self.weights[i] - min_r) / (max_r - min_r)
      else:
        r = 0.1
      p = patches.Circle((X_train[i][0], X_train[i][1]), r, color=plt.cm.coolwarm((y_train[i]+1)/2))
      ax.add_patch(p)
      
  def visualize(self):
    figsize = 5
    fig = plt.figure(figsize=(figsize,figsize))
    ax = plt.subplot(111)
    x_min, x_max = X_train[:, 0].min() - 1, X_train[:, 0].max() + 1
    y_min, y_max = X_train[:, 1].min() - 1, X_train[:, 1].max() + 1
    step = 0.25
    xx, yy = np.meshgrid(np.arange(x_min, x_max, step),
    np.arange(y_min, y_max, step))
    self.plot_contours(ax, xx, yy, cmap=plt.cm.coolwarm, alpha=0.3)
    self.plot_training_data(ax)
    ax.set_xlim(x_min, x_max)
    ax.set_ylim(y_min, y_max)
    plt.show()
    return
  
[X_train, y_train] = generate_training_data(200)
cls = AdaBoostClassifier(X_train, y_train)
cls.visualize()