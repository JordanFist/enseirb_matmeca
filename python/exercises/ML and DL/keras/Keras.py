###########################################################################
# #@title
# import numpy as np
# from keras.models import Sequential
# from keras.layers import Dense, Activation, Conv2D, MaxPooling2D
# from keras.optimizers import SGD
# import matplotlib.pyplot as plt
# import matplotlib.cm as cm
# from keras.utils import np_utils
# from keras.layers import Dropout, Flatten

# #fonction a approximer
# def F(x1, x2):
#   return np.sin(np.pi * x1 / 2.0) * np.cos(np.pi * x2 / 4.0)

# A = 2
# nb_samples = 1000
# X_train = np.random.uniform(-A, A, (nb_samples, 2))
# Y_train = np.vectorize(F)(X_train[:,0], X_train[:,1]) #application de la fonction sur tous les points

# model = Sequential() #creation du model

# nb_neurons = 20
# model.add(Dense(nb_neurons, input_shape=(2,))) #nombre de couches du reseau
# model.add(Activation('relu'))
# model.add(Dense(1))

# sgd = SGD(lr=0.01, decay=1e-6, momentum=0.9, nesterov=True)
# model.compile(loss='mean_squared_error', optimizer=sgd)

# model.fit(X_train, Y_train, epochs=10, batch_size=32)

# #Prediction

# x = [1.5, 0.5]
# print(F(x[0], x[1]))
# x = np.array(x).reshape(1, 2)
# print(x)
# print(model.predict(x))
# print(model.predict(x)[0][0])

# #Visualization

# Width = 200
# Height = 200
# U = np.linspace(-A, A, Width)
# V = np.linspace(-A, A, Height)
# UV = np.transpose([np.tile(U, len(V)), np.repeat(V, len(U))])
# print(UV)
# ys = model.predict(UV)
# print(ys)
# I = ys.reshape(Width, Height)

# %matplotlib inline
# plt.imshow(I, cmap = cm.Greys)

###########################################################################

# from keras.datasets import mnist

# (X_train, y_train), (X_test, y_test) = mnist.load_data()
# print(X_train.shape)

# plt.imshow(X_train [0], cmap = cm.Greys)
# X_train = X_train.reshape(X_train.shape[0], 28, 28, 1)
# X_train = X_train.astype('float32')
# X_train /= 255
# print(X_train.shape)

# X_test = X_test.reshape(X_test.shape[0], 28, 28, 1)
# X_test = X_test.astype('float32')
# X_test /= 255

# print(y_train.shape)
# print(y_train[0:3])

# y_train = np_utils.to_categorical(y_train, 10)
# print(y_train[0])

# model = Sequential()
# model.add(Conv2D(32, (3, 3), activation='relu', input_shape=(28,28,1)))
# print(model.output_shape)

# model.add(MaxPooling2D(pool_size=(2, 2)))
# print(model.output_shape)

# model.add(Dropout(0.25))
# print(model.output_shape)
# model.add(Flatten())
# print(model.output_shape)

# model.add(Dense(128, activation='relu'))
# print(model.output_shape)

# model.add(Dropout(0.5))
# model.add(Dense(10, activation='softmax'))
# print(model.output_shape)

# model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['accuracy'])

# model.fit(X_train, y_train, batch_size=32, epochs=10, verbose=1)

# plt.imshow(X_test[0].reshape(28, 28), cmap=cm.Greys)

# print(model.predict(X_test[0].reshape(1, 28, 28, 1)))

###########################################################################

from keras.applications.vgg16 import VGG16, decode_predictions
from keras.preprocessing.image import load_img, img_to_array

model = VGG16()
print(model.summary())
!wget https://cdn.cnn.com/cnnnext/dam/assets/190325211231-02-trump-white-house-0325-exlarge-169.jpg
image = load_img('190325211231-02-trump-white-house-0325-exlarge-169.jpg', target_size=(224, 224))
image = img_to_array(image)
print(image.shape)
image = image.reshape((1, image.shape[0], image.shape[1], image.shape[2]))

print(image.shape)

y_pred = model.predict(image)
print(y_pred.shape)
labels_pred = decode_predictions(y_pred)
print(labels_pred)

                                                      

