
import mnist
import matplotlib.pyplot as plt 
import gzip, os, sys
import numpy as np
from scipy.stats import multivariate_normal
#%% Classifying MNIST with k-nearest neighbors (KNN) classifier

## Load the training set
#path = 'C:\Courses\Edx\Current\USCD ML\Week3\\'
# 훈련 데이터
train_data = mnist.load_mnist_images('train-images-idx3-ubyte.gz')
# 데이터의 정답(lable) => 지도학습
train_labels = mnist.load_mnist_labels('train-labels-idx1-ubyte.gz')

# 훈련 데이터 개수 제한
train_data = train_data[:10000, ...]
train_labels = train_labels[:10000, ...]

## Load the testing set
test_data = mnist.load_mnist_images('t10k-images-idx3-ubyte.gz')
test_labels = mnist.load_mnist_labels('t10k-labels-idx1-ubyte.gz')

# 테스터 데이터 개수 제한
test_data = test_data[:100, ...]
test_labels = test_labels[:100,...]

## Define a function that takes an index into a particular data set ("train" or "test") and displays that image.
def vis_image(index, dataset="train"):
    if(dataset=="train"): 
        label = train_labels[index]
        mnist.show_digit(train_data[index,], label)
    else:
        label = test_labels[index]
        mnist.show_digit(test_data[index,], label)
    #print("Label " + str(label))
    plt.show()
    return
  
plt.figure(figsize=(10,10))
for i in range(25):
    plt.subplot(5, 5, i+1)
    #show_digit(train_data[i,], train_labels[i])
    mnist.show_digit(test_data[i,], test_labels[i])
plt.tight_layout()
plt.show()

#%% Ball Tree 만드는 과정
import time
# BallTree 3개의 이웃 특징점을 이용
from sklearn.neighbors import BallTree

## 학습 시간 출력
## Build nearest neighbor structure on training data
t_before = time.time()
ball_tree = BallTree(train_data)
t_after = time.time()
## Compute training time
t_training = t_after - t_before
print("Time to build data structure (seconds): ", t_training)

## Get nearest neighbor predictions on testing data
t_before = time.time()
test_neighbors = np.squeeze(ball_tree.query(test_data, k=1, return_distance=False))
test_predictions = train_labels[test_neighbors]
t_after = time.time()
## Compute testing time
t_testing = t_after - t_before
print("Time to classify test set (seconds): ", t_testing)

# 0.96909999999999996
import pandas as pd
import seaborn as sn
from sklearn import metrics
cm = metrics.confusion_matrix(test_labels,test_predictions)
# 인식 범위
df_cm = pd.DataFrame(cm, range(10), range(10))
sn.set(font_scale=1.2)# for label size
sn.heatmap(df_cm, annot=True,annot_kws={"size": 16}, fmt="g")