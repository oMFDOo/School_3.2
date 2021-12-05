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

#%%

# 컨볼루션 신경
# it will download weights for the first time
vgg_conv = VGG16(weights='imagenet',
                  include_top=False,
                  input_shape=(224, 224, 3)) 


