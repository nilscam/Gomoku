#!/usr/bin/env python3

import os

from keras.models import *
from keras.layers import *
from keras.optimizers import *
import numpy
import GameBoard as game

numpy.random.seed(7)

class neuralNet:

    def __init__(self):
        self.model = self.createModel()

    def createModel(self):
        inputs = Input(shape=(722,)) # changer la shape pour les convolutions

        shape = Reshape((19, 19, 2))(inputs) # on explique qu'on a 2 board de 19 par 19
        conv1 = Activation('relu')(BatchNormalization(axis=3)(Conv2D(16, 3, padding='same', use_bias=False)(shape)))
        conv2 = Activation('relu')(BatchNormalization(axis=3)(Conv2D(16, 3, padding='same', use_bias=False)(conv1)))
        conv3 = Activation('relu')(BatchNormalization(axis=3)(Conv2D(16, 3, padding='same', use_bias=False)(conv2)))

        flat = Flatten()(conv3)
        hidden1 = Dropout(0.2)(Activation('relu')(BatchNormalization(axis=1)(Dense(1024, use_bias=False)(flat))))
        hidden2 = Dropout(0.2)(Activation('relu')(BatchNormalization(axis=1)(Dense(512, use_bias=False)(hidden1))))

        v = Dense(1, activation='tanh')(hidden2)
        pm = Dense(361, activation='softmax')(hidden2)

        # l1 = Dense(256, activation='sigmoid')(inputs)
        # l2 = Dense(256, activation='sigmoid')(l1)
        # v = Dense(1, activation='tanh', name='v')(l2)
        # pm = Dense(361, activation='softmax', name='pm')(l2)

        model = Model(inputs=inputs, outputs=[v, pm])
        model.compile(loss=['mse', 'categorical_crossentropy'], optimizer='adam')
        return model

    def save(self, folder='model', filename='my_model.h5'):
        filepath = os.path.join(folder, filename)

        if not os.path.exists(folder):
            os.mkdir(folder)
        self.model.save(filepath)

    def load(self, folder='model', filename='my_model.h5'):
        filepath = os.path.join(folder, filename)

        if not os.path.exists(filepath):
            raise("model not found")
        self.model.load_weights(filepath)

    def train(self, examples):
        inputBoards, pms, vs = list(zip(*examples)) # regroupe les inputs, pm et v ensemble

        # on convertie en numpy array pour les passer à keras
        inputBoards = np.asarray(inputBoards)
        pms = np.asarray(pms)
        vs = np.asarray(vs)
        self.model.fit(x= inputBoards, y= [vs, pms], epochs=10, batch_size=32)

    def predict(self, board):
        inp = np.asarray(board.to_dataset())
        inp2 = inp[np.newaxis, :]
        v, pm = self.model.predict(inp2)
        return v[0], pm[0]

    def copy(self, toCopy):
        toCopy.save()
        self.load()
