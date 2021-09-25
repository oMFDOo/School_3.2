# -*- coding: utf-8 -*-
"""
Created on Sat Sep 25 23:03:09 2021

@author: user
"""

import numpy as np
from scipy import signal, misc, ndimage
from skimage import filters, feature, img_as_float, exposure
from skimage.io import imread
from skimage.color import rgb2gray
from PIL import Image, ImageFilter
import matplotlib.pylab as pylab
import matplotlib.pylab as plt
import cv2

import time

from skimage.morphology import binary_erosion

# sobelEdge 사용 시 필요
import scipy.fftpack as fp

# 히스토그램 평활화
def equalize_func(im):
    return exposure.equalize_hist(im)

# 콘트라스트 스트레칭
def contrast_str_func(im):
    from_, to_ = np.percentile(im, (2, 98))
    return exposure.rescale_intensity(im, in_range=(from_, to_))

# 1. HPF
def highPassFiliter(im, t):
  t = time.time()
  freq = fp.fft2(im) # 고속 fft변환
  (w, h) = freq.shape # 너비값 저장
  half_w, half_h = int(w/2), int(h/2) # 중앙값 계산
  freq1 = np.copy(freq) # fft 변환값 저장
  freq2 = fp.fftshift(freq1) # fft 변환값 쉬프팅
  # 하이패스 필터 적용  
  freq2[half_w-20:half_w+21,half_h-20:half_h+21] = 0 # 저주파(스펙트럼 중앙 부분)대역 삭제
  im1 = np.clip(fp.ifft2(fp.ifftshift(freq2)).real,0,255) # 고속푸리에변환 후 허수값을 제외한 0에서 255값의 변환이미지 값 생성
  return im1, time.time() - t

# 2. unshape masking
def unshape_masking(im, t):
    t = time.time()
    im = rgb2gray(img_as_float(im))  # skimage라이브러리의 함수 rgb2gray()를 통한 이진화
    im_blurred = ndimage.gaussian_filter(im, 5)    # 가우시안필터를 이용하여 블러링처리
    im_detail = np.clip(im - im_blurred, 0, 1)     # 원본이미지에서 블러링한 이미지를 빼서 마스크 생성
    #im_sharp = np.clip(im + 5*im_detail, 0, 1)   # 마스크를 영상에 더한다(가중치 =5, 가장 원본과 차이가 큼)
    return im_detail, time.time() - t

# 4. 라플라시안
def laplacian_func(img, t):
    t = time.time()
    laplac_kern = [[1,1,1],[1,-8,1],[1,1,1]] # 라플라시안 필터 생성
    result = np.clip(signal.convolve2d(img, laplac_kern, mode='same'), 0, 1) #라플라시안 필터로 컨볼루션 적용
    return result, time.time() - t

# 5. 경계 추출
def boundary_func(im, t):   #경계 추출
    t = time.time()
    threshold = 0.5 # 임계값 설정
    im[im<threshold], im[im >= threshold] = 0, 1 # 임계값보다 작은 값은 0, 크거나 같은 값은 1
    boundary = im - binary_erosion(im) # 경계를 추출하기 위해 이진 영상에서 침식된 영상을 뺀다
    result = np.array(boundary)
    return result, time.time() - t

# 6. Sobel 엣지
def sobelEdge_func(im, t):
    t = time.time()
    edges = filters.sobel(im) # 소벨에지 적용
    return edges, time.time() - t

# 7. 캐니
def canny_func(im, t):
    t = time.time()
    canny = feature.canny(im, 1)
    result = np.array(canny)
    return result, time.time() - t



im = []
for i in range(3):
    path_ = '../images/' + str(i+1) +'.jpg'
    im.append(rgb2gray(imread(path_)))
    
    
hist_equ = []
cont_img = []
for i in range(3):
    hist_equ.append(equalize_func(im[i]))
    cont_img.append(contrast_str_func(im[i]))

result_img = []
tmp = 0

time_ = [];
time_temp = 0; 
for j in range(2):
    if j == 0: 
        img_temp = hist_equ 
        title = 'histogram equalize'
    if j == 1: 
        img_temp = cont_img
        title = 'contrast stretching'
    for k in range(3):
        fig, axes=plt.subplots(2, 4, figsize=(16,8))
        axes[0][0].imshow(img_temp[k])
        tmp, time_temp = highPassFiliter(img_temp[k], time_temp)
        axes[0][1].imshow(tmp)
        time_.append(round(time_temp*1000, 2))
        tmp, time_temp = unshape_masking(img_temp[k], time_temp)
        axes[0][2].imshow(tmp)
        time_.append(round(time_temp*1000, 2))
        tmp, time_temp = canny_func(img_temp[k], time_temp)
        axes[0][3].imshow(tmp)
        time_.append(round(time_temp*1000, 2))
        tmp, time_temp = laplacian_func(img_temp[k], time_temp)
        axes[1][0].imshow(tmp)
        time_.append(round(time_temp*1000, 2))
        tmp, time_temp = boundary_func(img_temp[k], time_temp)
        axes[1][1].imshow(tmp)
        time_.append(round(time_temp*1000, 2))
        tmp, time_temp = sobelEdge_func(img_temp[k], time_temp)
        axes[1][2].imshow(tmp)
        time_.append(round(time_temp*1000, 2))
        tmp, time_temp = canny_func(img_temp[k], time_temp)
        axes[1][3].imshow(tmp)
        time_.append(round(time_temp*1000, 2))
        axes[0][0].axis('off')
        axes[0][1].axis('off')
        axes[0][2].axis('off')
        axes[0][3].axis('off')
        axes[1][0].axis('off')
        axes[1][1].axis('off')
        axes[1][2].axis('off')
        axes[1][3].axis('off')
        
        axes[0][0].set_title(title)
        axes[0][1].set_title('HPF')
        axes[0][2].set_title('Unshape masking')
        axes[0][3].set_title('Gradient')
        axes[1][0].set_title('Laplacian')
        axes[1][1].set_title('Boundary')
        axes[1][2].set_title('Sobel')
        axes[1][3].set_title('HPF')
        plt.show()
     
sum_temp = [[0 for col in range(7)] for row in range(2)]
for i in range(2):
  for j in range(7):
    sum_temp[i][j] = float(0.0)
    
for i in range(0, 42):
    sum_temp[int(i//3)] += time_[int(i%14)]
    
for i in range(3):
  for j in range(2):
    for k in range(7):
      sum_temp[j][k] += time_[(i*j)+k]

sum_total = []
cnt = int(0)
for j in range(2):
    for k in range(7):
      sum_total[cnt] = sum_temp[j][k] / 3.0   
      cnt = cnt + 1
      
sum_total.sort()

print(sum_total)


    
      
      
    # for i in hist_equ:
    #     tmp, time_temp = laplacian_func(i, time_temp)
    #     result_img.append(tmp)
    #     time_.append(str(time_temp*1000)+'ms')
    #     #time_temp = 0
    #     tmp, time_temp = canny_func(i, time_temp)
    #     result_img.append(tmp)
    #     time_.append(str(time_temp*1000)+'ms')
    #     #time_temp = 0
    
    # for i in cont_img:
    #     tmp, time_temp = laplacian_func(i, time_temp)
    #     result_img.append(tmp)
    #     time_.append(str(time_temp*1000)+'ms')
    #     #time_temp = 0
    #     tmp, time_temp = canny_func(i, time_temp)
    #     result_img.append(tmp)
    #     time_.append(str(time_temp*1000)+'ms')
    #     #time_temp = 0
    