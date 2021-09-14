8# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

from PIL import Image
import scipy.fftpack as fp
import matplotlib.pylab as pylab  # 이미지 그리기
import numpy as np
import numpy.fft



imarr = np.zeros((512, 512)) # 512*512 크기 0배열 선언 튜플이라 괄호 하나 더 넣었음.
imarr[:,:] = 128 # 모든 값을 회색조로 지정하자

# img = Image.fromarray(imarr)
# img.show()

# 인덱싱 공부 잘 해놓기
# for x in range(-50, 50) :
#     imarr[:,x+256] = np.abs(x*3)


# 원형 마스크 생성하기
lx = ly = 512
X, Y = np.ogrid[0:lx, 0:ly]
# < 이 값의 내부에 들어올 때만 값 적용
# 16의 값을 1024처럼 크게 하면 파장이 보이게 됨 : 주파수 대역대가 커졌기 때문
# 원의 방정식
mask = (X - lx/2)**2 + (Y-ly/2)**2 < lx * ly / 2048
imarr[mask] = 255


freq = fp.fft2(imarr) # 형태를 보기 위해 푸리에 스펙트럼이 유용하다.
ftarr = 20*np.log10(0.01 + np.abs(fp.fftshift(freq))) # 사상을 적용

pylab.figure(figsize=(10,10)) # figsize가 높아질수록 해상도가 높아짐
pylab.subplot(1, 2, 1), pylab.imshow(imarr, cmap='gray', vmin=0, vmax=255) #imshow에는 numpy array가 들어가야한다.
# vmin/vamx : value의 최솟값 최댓값

pylab.subplot(1, 2, 2), pylab.imshow(ftarr, cmap="gray")