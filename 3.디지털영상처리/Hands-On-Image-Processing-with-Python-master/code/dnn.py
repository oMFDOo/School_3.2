# -*- coding: utf-8 -*-
"""
Created on Fri Dec  3 10:15:20 2021

@author: user
"""
# 모델을 만들고 얼마나 정확한지
# 그 중 오류가 있는 녀석들은 어떤 녀석인지
from tensorflow.keras.applications import VGG16 
from keras.preprocessing.image import ImageDataGenerator
from keras import models, layers, optimizers
from keras.layers import BatchNormalization
import matplotlib.pylab as plt
from keras.preprocessing.image import load_img
import numpy as np

#%%

# 컨볼루션 신경망
# 컨볼루션 레이어를 만들어준다.
vgg_conv = VGG16(weights='imagenet',
                  include_top=False,
                  input_shape=(224, 224, 3)) 


train_dir = '../images/train'
validation_dir = '../images/vaild'
 
# 트레이닝 데이터 500개 씩 3그룹
# 결과 데이터 50개 씩 3그룹
nTrain = 500*3
nVal = 50*3

# 그레이레벨로 이용
datagen = ImageDataGenerator(rescale=1./255)
batch_size = 25
 
train_features = np.zeros(shape=(nTrain, 7, 7, 512))
train_labels = np.zeros(shape=(nTrain,3))

train_generator = datagen.flow_from_directory(
    train_dir,
    target_size=(224, 224),
    batch_size=batch_size,
    class_mode='categorical',
    shuffle=True)

# 컨볼루션 정의 : 트레이닝 데이터 생성
i = 0
for inputs_batch, labels_batch in train_generator:
    features_batch = vgg_conv.predict(inputs_batch)
    train_features[i * batch_size : (i + 1) * batch_size] = features_batch
    train_labels[i * batch_size : (i + 1) * batch_size] = labels_batch
    i += 1
    print(i * batch_size)
    if i * batch_size >= nTrain:
        break
         
train_features = np.reshape(train_features, (nTrain, 7 * 7 * 512))


# 테스트 데이터 생성
validation_features = np.zeros(shape=(nVal, 7, 7, 512))
validation_labels = np.zeros(shape=(nVal,3))

validation_generator = datagen.flow_from_directory(
    validation_dir,
    target_size=(224, 224),
    batch_size=batch_size,
    class_mode='categorical',
    shuffle=False)
i = 0
for inputs_batch, labels_batch in validation_generator:
    features_batch = vgg_conv.predict(inputs_batch)
    validation_features[i * batch_size : (i + 1) * batch_size] = features_batch
    validation_labels[i * batch_size : (i + 1) * batch_size] = labels_batch
    i += 1
    if i * batch_size >= nVal:
        break
         
validation_features = np.reshape(validation_features, (nVal, 7 * 7 * 512))


# 인풋레이어를 이용
model = models.Sequential()
# 활성화 함수 : activation
model.add(layers.Dense(512, activation='relu', input_dim=7 * 7 * 512))
model.add(BatchNormalization())
model.add(layers.Dropout(0.5)) # 엣지를 줄이는 %
#model.add(layers.Dense(256, activation='relu')) # make the neural network deep
#model.add(BatchNormalization())
#model.add(layers.Dropout(0.5))
model.add(layers.Dense(3, activation='softmax'))

# 에이담
model.compile(optimizer = "adam", #optimizers.RMSprop(lr=1e-3),
              loss='categorical_crossentropy',
              metrics=['acc'])

history = model.fit(train_features,
                    train_labels,
                    epochs=10,
                    batch_size=batch_size,
                    validation_data=(validation_features,validation_labels))



# 검증단
fnames = validation_generator.filenames 
ground_truth = validation_generator.classes 
label2index = validation_generator.class_indices 
# Getting the mapping from class index to class label
idx2label = dict((v,k) for k,v in label2index.items()) 

prob = model.predict(validation_features) 
# predictions = model.predict_classes(validation_features)
predictions = list(np.argmax(prob, axis=1))



errors = np.where(predictions != ground_truth)[0]
print("No of errors = {}/{}".format(len(errors),nVal))



plt.figure(figsize=(20,12))
for i in range(10):
    pred_class = np.argmax(prob[errors[i]])
    pred_label = idx2label[pred_class]
    original = load_img('{}/{}'.format(validation_dir,fnames[errors[i]]))
    plt.subplot(3,6,i+1), plt.imshow(original), plt.axis('off')
    plt.title('Original label:{}\nPrediction:{}\nconfidence:{:.3f}'.format(
        fnames[errors[i]].split('\\')[0],
        pred_label,
        prob[errors[i]][pred_class]), size=15)
plt.show()




