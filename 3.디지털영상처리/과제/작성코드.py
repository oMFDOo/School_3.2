from skimage import filters, feature, img_as_float, exposure, img_as_ubyte
from skimage.io import imread
from skimage.color import rgb2gray
# 이미지 그리기
import matplotlib.pylab as pylab
# 컨볼루션
from scipy import signal, ndimage
import numpy as np
import cv2 

# 히스토그램 평활화
def equalize_func(im):
    return exposure.equalize_hist(im)
# 콘트라스트 스트레칭
def contrast_str_func(im):
    from_, to_ = np.percentile(im, (2, 98))
    return exposure.rescale_intensity(im, in_range=(from_, to_))


#%% 소벨이미지와 라플라시안 이미지

im = rgb2gray(imread("../images/3.jpg"))
im = contrast_str_func(im)

# 소벨 커널 생성
ker_x = [ [-1, 0, 1], [-2, 0, 2], [-1, 0, 1]]
ker_y = [ [-1, -2, -1], [0, 0, 0], [1, 2, 1]]

im_x = signal.convolve2d(im, ker_x, mode="same")
im_y = signal.convolve2d(im, ker_y, mode="same")

# magnitude
im_mag = np.sqrt( (im_x)**2 + (im_y)**2 )
# direction
im_dir = np.clip(np.arctan( im_y / im_x ), 0, 1)


# 라플라시안 커널 : 등방성
ker_lp = [[0, -2, 0], [-1, -8, -1], [0, -2, 0]]

im_lp = signal.convolve2d(im, ker_lp, mode="same")


pylab.figure(figsize=(30, 30))
pylab.subplot(2,2,1), pylab.imshow(im, cmap='gray')
pylab.subplot(2,2,2), pylab.imshow(im_mag, cmap='gray')
pylab.subplot(2,2,3), pylab.imshow(im_dir, cmap='gray')
# pylab.subplot(2,2,4), pylab.imshow(im_fft, cmap='gray')
pylab.subplot(2,2,4), pylab.imshow(im_lp, cmap='gray')


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
im = equalize_func(im)

# LoG
# 숫자조정해서 가우시안 값을 바꿀 수 있다.
im_g = filters.gaussian(im, 2)
im_l = filters.laplace(im_g)

# T값도 내 맘대로 조정 가능하다
edge = zero_cross(im_l, T=np.max(im_l)*0.001)

# DoG
im_dog = filters.difference_of_gaussians(im, 2.0)
edge2 = zero_cross(im_dog, T=np.max(im_dog)*0.001)

# fft
height, width = im.shape 
dft = cv2.dft(np.float32(edge2), flags=cv2.DFT_COMPLEX_OUTPUT) 
dft_shift = np.fft.fftshift(dft)
im_fft = 20*np.log(cv2.magnitude(dft_shift[:, :, 0], dft_shift[:, :, 1]))

from skimage.morphology import disk

blur = filters.median(edge, disk(1))

pylab.figure(figsize=(30, 30))
pylab.subplot(2,2,1), pylab.imshow(im, cmap='gray')
pylab.subplot(2,2,2), pylab.imshow(im_l, cmap='gray')
pylab.subplot(2,2,3), pylab.imshow(edge, cmap='gray')
pylab.subplot(2,2,4), pylab.imshow(edge2, cmap='gray')
# pylab.subplot(2,2,4), pylab.imshow(im_fft, cmap='gray')
# pylab.subplot(2,2,4), pylab.imshow(blur, cmap='gray')


#%% Edge Detector

im = rgb2gray(imread('../images/3.jpg'))
im = equalize_func(im)


im = filters.median(im)
edges = filters.sobel(im)
# 
pylab.figure(figsize=(30,20))
pylab.subplot(121), pylab.imshow(im, cmap='gray'), pylab.title('original')
pylab.subplot(122), pylab.imshow(edges, cmap='gray'), pylab.title('original')

#%% Canny
im = rgb2gray(imread('../images/3.jpg'))
im = contrast_str_func(im)

im = ndimage.gaussian_filter(im, 2)
edges = feature.canny(im, sigma=2)

pylab.figure(figsize=(30,20))
pylab.subplot(121), pylab.imshow(im, cmap='gray'), pylab.title('original')
pylab.subplot(122), pylab.imshow(edges, cmap='gray'), pylab.title('original')
