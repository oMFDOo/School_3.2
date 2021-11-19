import tkinter
import mnist
import time
import matplotlib.pyplot as plt 
import gzip, os, sys
import numpy as np
from scipy.stats import multivariate_normal
from sklearn.neighbors import BallTree
import cv2

W = 320
H = 320


#%% 학습데이터 가져오기
## Load the training set
#path = 'C:\Courses\Edx\Current\USCD ML\Week3\\'
# 훈련 데이터
train_data = mnist.load_mnist_images('train-images-idx3-ubyte.gz')
# 데이터의 정답(lable) => 지도학습
train_labels = mnist.load_mnist_labels('train-labels-idx1-ubyte.gz')

# 훈련 데이터 개수 제한
train_data = train_data[:10000, ...]
train_labels = train_labels[:10000, ...]

# 캔버스의 버퍼를 만들거래
# 캔버스에도 그래고 버퍼에도 그린대
buffer = np.zeros((W,H))


#%% 윈도우 그리기
window=tkinter.Tk()
# 윈도우 사이즈 설정
window.geometry('500x500')


# 캔버스 생성
canvas = tkinter.Canvas(window, width=W, height=H, bg="black")
canvas.place(x=90, y=10)

# 텍스트박스 생성
tbox = tkinter.Text(window, height = 8, width= 40)
tbox.place(x=150, y= 350)

def cclear():
  canvas.delete('all')
  # 버퍼내용 지우기
  buffer[:] = 0

# 버튼 생성 : 지우기
btn1 = tkinter.Button(window, text='Clear', width=15, command=cclear)
btn1.place(x=10, y=350)

def learn():
    # 1. KNN
    t_before = time.time()
    # ball_tree는 탐색에 최적화를 위해 사용
    global ball_tree
    # meteric : 거리 계산법
    # 해밍(hamming) : 거리계산을 위해 0과 1의 차이의 개수를 보는것
    # 유클리디안(euclidean) 
    ball_tree = BallTree(train_data,metric="hamming")
    
    # 저기 들어갈 수 있는 옵션 뭐 있는지 출력해달
    print(BallTree.valid_metrics)
    
    t_after = time.time()
    
    t_training = t_after - t_before
    # 텍스트 박스에 시간 출력
    tbox.insert('end', 'Learn: ' + str(t_training) + '\n')
    
    # 2. bAYES CLASSIFIER
    global mu, sigma, pi
    # mu, sigma, pi = fit_generative_model(train_data, train_labels)
    # tbox.insert('end', "compute Done\n")

# 버튼 생성 : 학습하기
btn2 = tkinter.Button(window, text='Learn', width=15, command=learn)
btn2.place(x=10, y=400)

def cfind():
    # 1. KNN
  # 버퍼 내용을 그려줘
  # 코드 디렉토리에 버퍼내용 이미지가 생
  # cv2.imwrite("outbuf.jpg", buffer)
  
  # 값 크기가 안 맞아서 크기 재설정 중
  from skimage.transform import resize
  input_data = resize(buffer, (28, 28))
  input_data = np.reshape(input_data.flatten(), (1, 28*28))
  result = ball_tree.query(input_data, k=1, return_distance=False)
  tbox.insert('end', str(train_labels[result]) + '\n')
  
  # # 2. bAYES CLASSIFIER
  # score = np.zeros((10)
  # for label in range(0,10):
  #     # mu : 평균
  #     # sigma : 분산
  #     rv = multivariate_normal(mean=mu[label], cov=sigma[label])
  #     score[i,label] = np.log(pi[label]) + rv.logpdf(input_data)
  #     result = np.argmax(score, axis=1)

# 버튼 생성 : 탐색하기
btn3 = tkinter.Button(window, text='Find', width=15, command=cfind)
btn3.place(x=10, y=450)

def mmove(event):
  x = event.x
  y = event.y
  # 버퍼 기록하기
  Y, X = np.ogrid[0:W, 0:H]
  # 원의 방정식 x^2 + y^2 = r^2
  mask = (X -x)**2 + (Y-y)**2 < 100
  buffer[mask] = 255;
  # 캔버스에 원 그리기
  canvas.create_oval(x-10, y-10, x+10, y+10, outline='white', fill='white')
  
# 캔버스에 이벤트 바인딩 : 왼쪽 클릭
canvas.bind('<B1-Motion>', mmove)
 
window.mainloop()