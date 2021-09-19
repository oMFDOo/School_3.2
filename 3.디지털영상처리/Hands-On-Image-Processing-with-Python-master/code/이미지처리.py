#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Sep 17 10:12:24 2021

@author: hwangjinju
"""

#Python Image Library
from PIL import Image, ImageDraw, ImageFont
import numpy as np
# pylab을 통한 이미지 출력을 위해 사용
import matplotlib.pylab as pylab
# 이미지를 가져오는 다른 방법
from skimage.io import imread
# rgb2grayㅡ를 사용하기 위함
from skimage.color import rgb2gray


# shift + enter 를 이용해 단위별 실행 가능

#%% 그레이레벨로 변환하는 다양한 함수

# 이미지 불러올 때 변환
im = Image.open("../images/parrot.png").convert('L')
im.show()

# numpy 변환
im2 = rgb2gray(imread("../images/parrot.png"))

# 평균 이용하기
im3 = imread("../images/parrot.png")
# 2개의 축 기준으로 평균을 내어달라
imarr = np.mean(im3, axis=2)


pylab.figure(figsize=(15,5))
pylab.subplot(1,2,1), pylab.imshow(im2, cmap="gray")
pylab.subplot(1,2,2), pylab.imshow(imarr, cmap="gray")

#%% 이미지를 가져오는 다른 방법

# 이렇게 가져온 이미지는 NUMPY로 처리 가능하다.
im = imread("../images/parrot.png")

# 이미지 분할 [-1]의미는 나는 모르니까 니가 알아서 해줘
[arr_r, arr_g, arr_b] = np.dsplit(im, im.shape[-1])

# 출력
pylab.figure(figsize=(15,5))
pylab.subplot(1,2,1), pylab.imshow(arr_r, cmap="gray")


#%% numpy를 이용해서 해보기

# 이미지 불러오기
im = Image.open("../images/parrot.png") 

# 이미지 색상 분리
im_r, im_g, im_b = im.split()

arr_r = np.array(im_r)
arr_g = np.array(im_g)
arr_b = np.array(im_b)

arr_r[:] = 0

# 레이어 병합
arr_rgb = np.dstack((arr_r, arr_g, arr_b))

# 이미지로 변환
Im2 = Image.fromarray(arr_rgb)
Im2.show()

# 출력
pylab.figure(figsize=(15,5))
pylab.subplot(1,2,1), pylab.imshow(arr_r, cmap="gray")
pylab.subplot(1,2,2), pylab.imshow(arr_rgb)




#%%

# 이미지 불러오기
im = Image.open("../images/parrot.png") 
# 이미지 정보 출력
print(im.width, im.height, im.mode)
# 콘솔에 이미지 출력
# im.show()

# 이미지 색상 분리
im_r, im_g, im_b = im.split()
# RGBA 영상인 경우 EX_ 치타
# im_r, im_g, im_b, _ = im.split()
# red값 영으로 만들기
im_r = im_r.point(lambda i : 0)

# 색상 결합
imout = Image.merge("RGB", (im_r, im_g, im_b))

# 도형그리기
draw = ImageDraw.Draw(imout, "RGBA")
draw.ellipse( (125, 125, 200, 250), fill=(255, 255, 0, 128) )
# font = ImageFont.truetype("arial.ttf", 23)
# draw.text((10, 5), "Test", font=font)
del draw

pylab.figure(figsize=(15,5))
pylab.subplot(1,2,1), pylab.imshow(imout)

# 히스토그램 출력. ravel을 쓰면 데이터를 펼칠 수 있다.
pylab.subplot(1,2,2), pylab.hist(np.array(im_r).ravel(), bins=20,
                                 range=(0,256), color='r')