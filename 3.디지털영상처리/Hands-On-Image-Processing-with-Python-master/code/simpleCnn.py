# -*- coding: utf-8 -*-
"""
Created on Fri Dec  3 11:04:12 2021

@author: user
"""
import tensorflow as tf

from tensorflow import keras 

import numpy as np

import matplotlib.pyplot as plt

 

#%%

print(tf.__version__)

 

fashion_mnist = keras.datasets.fashion_mnist 

(train_images, train_labels), (test_images, test_labels) = fashion_mnist.load_data()

 

plt.figure(figsize=(15, 5))

for i in range(3):

    plt.subplot(1, 3, i+1), plt.imshow(train_images[i])

plt.show()

 
# 인풋 레이어
model = keras.Sequential([
  # 히든 레이어
    keras.layers.Flatten(input_shape=(28, 28)),
  # 활성화 함수
    keras.layers.Dense(128, activation='relu'),
  # 
    keras.layers.Dense(10, activation='softmax') ])

 

model.compile(optimizer='adam',

              loss='sparse_categorical_crossentropy',

              metrics=['accuracy'])

 

model.fit(train_images, train_labels, epochs=5)

 

test_loss, test_acc = model.evaluate(test_images,  test_labels, verbose=2)

print('\n테스트 정확도:', test_acc)

# 학습한 모델 저장하기
model.save('./mymodel.h5')

#%%
import cv2

# 저장된 모델 불러오기
model = keras.models.load_model('./mymodel.h5')
model.summary()

img = cv2.imread('../images/boots.png', cv2.IMREAD_GRAYSCALE)
# 않이 가로로 뒤집으니까 잘 하네
img = cv2.flip(img, 1)
plt.imshow(img)

img = cv2.resize(img, (28, 28))


# 채널 확장
inp_img = img[np.newaxis, :, :]
result = model.predict(inp_img)

class_names = ['T-Shirt', 'Trouser', 'Pull', 'Dress', 'Coat', 'sandal', 'Shirt', 'Sneaker', 'Bag', 'Boot']

yhat = np.argmax(result)

print(class_names[yhat])




