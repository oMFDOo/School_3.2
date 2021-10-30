# 가우시안 필터 가져오기
from skimage import filters
from skimage.io import imread
from skimage.color import rgb2gray
from PIL import Image
import scipy.fftpack as fp
import matplotlib.pylab as pylab  # 이미지 그리기
import numpy as np

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

im = rgb2gray(imread("../images/goldengate.jpg"))

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
