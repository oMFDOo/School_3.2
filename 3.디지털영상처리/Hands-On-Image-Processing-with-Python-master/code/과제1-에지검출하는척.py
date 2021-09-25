# -*- coding: utf-8 -*-
"""
Created on Sat Sep 25 23:12:06 2021

@author: user
"""

from skimage.io import imread
from skimage.color import rgb2gray
# 이미지 그리기
import matplotlib.pylab as pylab
# 컨볼루션
from scipy import signal
import numpy as np


#%% 소벨이미지와 라플라시안 이미지

im = rgb2gray(imread("../images/3.jpg"))

# 소벨 커널 생성
ker_x = [ [-1, 0, 1], [-2, 0, 2], [-1, 0, 1]]
ker_y = [ [-1, -2, -1], [0, 0, 0], [1, 2, 1]]

im_x = signal.convolve2d(im, ker_x, mode="same")
im_y = signal.convolve2d(im, ker_y, mode="same")

# magnitude
im_mag = np.sqrt( (im_x)**2 + (im_y)**2 )
# direction
im_dir = np.clip(np.arctan( im_y / im_x ), 0, 1)

# 컬러 이미지 생성
ima = np.zeros( (im.shape[0], im.shape[1], 3) )
# 1번 채널
ima[..., 0] = np.sin(im_dir)    # R
# 2번 채널
ima[..., 1] = np.cos(im_dir)    # G



# 라플라시안 커널 : 등방성
ker_lp = [ [0, -1, 0], [-1, 4, -1], [0, -1, 0]]

im_lp = signal.convolve2d(im, ker_lp, mode="same")


pylab.figure(figsize=(30, 20))
pylab.subplot(2,4,1), pylab.imshow(im, cmap='gray')
pylab.subplot(2,4,2), pylab.imshow(im_x, cmap='gray')
pylab.subplot(2,4,3), pylab.imshow(im_y, cmap='gray')
pylab.subplot(2,4,4), pylab.imshow(im_mag, cmap='gray')
pylab.subplot(2,4,5), pylab.imshow(im_dir, cmap='gray')
pylab.subplot(2,4,6), pylab.imshow(ima, cmap='gray')
pylab.subplot(2,4,7), pylab.imshow(im_lp, cmap='gray')

#%% LoG와 DoG로 에지 검출하기
# 가우시안 필터 가져오기
from skimage import filters


def zero_cross(image, T=0):
    zimg = np.zeros(image.shape)
    # 커널이 넘치지 않게 하려고 -1만큼 까지만 돌게됨
    for i in range(0, image.shape[0]-1):
        for j in range(0, image.shape[1]-1):
            # if문 끝에 \는 라인 엔터치려고 넣은거임
            
            # 오른쪽
            if image[i][j]*image[i+1][j] < 0 \
            and np.abs( image[i+1][j] - image[i][j]) > T :
                   zimg[i,j] = 1
            # 우상단
            elif image[i][j]*image[i+1][j+1] < 0 \
            and np.abs( image[i+1][j+1] - image[i][j]) > T :
                   zimg[i,j] = 1
            # 위           
            elif image[i][j]*image[i][j+1] < 0 \
            and np.abs( image[i][j+1] - image[i][j]) > T :
                   zimg[i,j] = 1
    return zimg

im = rgb2gray(imread("../images/3.jpg"))

# LoG
# 숫자조정해서 가우시안 값을 바꿀 수 있다.
im_g = filters.gaussian(im, 8)
im_l = filters.laplace(im_g)
# T값도 내 맘대로 조정 가능하다
edge = zero_cross(im_l, T=np.max(im_l)*0.001)

# DoG
im_dog = filters.difference_of_gaussians(im, 5.0)
edge2 = zero_cross(im_dog, T=np.max(im_dog)*0.001)

pylab.figure(figsize=(30, 20))
pylab.subplot(2,2,1), pylab.imshow(im, cmap='gray')
pylab.subplot(2,2,2), pylab.imshow(im_l, cmap='gray')
pylab.subplot(2,2,3), pylab.imshow(edge, cmap='gray')
pylab.subplot(2,2,4), pylab.imshow(edge2, cmap='gray')



