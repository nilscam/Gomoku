#!/usr/bin/env python3

from keras.models import Sequential
from keras.layers import Dense
import numpy
import GameBoard as game

numpy.random.seed(7)

class neuralNet:

    def __init__(self):
        self.model = createModel()

    def createModel(self):
        sizeInput = 722 + 1

        inputs = Input(shape=(sizeInput,))
        l1 = Dense(256, activation='sigmoid')(inputs)
        l2 = Dense(256, activation='sigmoid')(l1)
        v = Dense(1, activation='tanh', name='v')(l2)
        pm = Dense(361, activation='softmax', name='pm')(l2)

        model = Model(inputs=inputs, outputs=[v, pm])
        model.compile(loss=['mse', 'categorical_crossentropy'], optimizer='adam'
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
        input = board.toDataSet()
        return self.model.predict(input)

    def copy(self, toCopy):
        toCopy.save()
        self.model.load()
