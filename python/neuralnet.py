#!/usr/bin/env python3

from keras.models import Sequential
from keras.layers import Dense
import numpy

numpy.random.seed(7)

#classification model
def createModel():
    sizeInput = 722 + 1

    inputs = Input(shape=(sizeInput,))
    l1 = Dense(256, activation='sigmoid')(inputs)
    l2 = Dense(256, activation='sigmoid')(l1)
    v = Dense(1, activation='tanh', name='v')(l2)
    pm = Dense(361, activation='softmax', name='pm')(l2)

    model = Model(inputs=inputs, outputs=[v, pm])
    model.compile(loss=['mse', 'categorical_crossentropy'], optimizer='adam'
    return model

def save(model):
    model.save('my_model.h5')

def train(examples):
    inputBoards = 1
    pms = 2
    vs = 3

    model.fit(x= inputBoards, y= [vs, pms], epoch=10, batch_size=16)
