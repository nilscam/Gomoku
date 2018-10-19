#!/usr/bin/env python3

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
        l1 = Dense(256, activation='sigmoid')(inputs)
        l2 = Dense(256, activation='sigmoid')(l1)
        v = Dense(1, activation='tanh', name='v')(l2)
        pm = Dense(361, activation='softmax', name='pm')(l2)

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
        self.nnet.model.load_weights(filepath)

    def train(self, examples):
        inputBoards, pms, vs = list(zip(*examples)) # regroupe les inputs, pm et v ensemble

        # on convertie en numpy array pour les passer à keras
        inputBoards = np.asarray(inputBoards)
        pms = np.asarray(pms)
        vs = np.asarray(vs)
        model.fit(x= inputBoards, y= [vs, pms], epoch=10, batch_size=16)

    def predict(self, board):
        inp = np.asarray(board.to_dataset())
        inp2 = inp[np.newaxis, :]
        print (inp2.shape)
        print (inp.shape)
        v, pm = self.model.predict(inp2)
        return v[0], pm[0]

    def copy(self, toCopy):
        toCopy.save()
        self.model.load()
