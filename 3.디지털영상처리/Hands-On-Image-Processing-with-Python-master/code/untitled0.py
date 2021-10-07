from matplotlib import pylab as pylab
from skimage.io import imread
from skimage.color import rgb2gray
import numpy as np
from scipy import signal
import cv2
from skimage.feature import corner_harris, corner_subpix, corner_peaks

#%%
kernel1d = cv2.getGaussianKernel(3, 1) 
kernel2d = np.outer(kernel1d, kernel1d.transpose())

def gaussian_kernel(whsize, sigma=1):
    x, y = np.mgrid[-whsize:whsize+1, -whsize:whsize+1]
    g_w = np.zeros(x.shape, dtype = np.double)
    g_w[:] = np.exp(-0.5 * (x**2 / sigma**2 + y**2 / sigma**2))
    g_w /= 2* np.pi * sigma**2
    g_w /= np.sum(g_w)    
    return g_w

im = np.zeros((12,12))

for i in range(3,8):
     im[i, 3:i+1] = 1
    
ker_x = [[-1, 0, 1]]
ker_y = [[-1], [0], [1]]
ker_g = gaussian_kernel(1)

im_x = signal.convolve2d(im, ker_x, mode='same')
im_y = signal.convolve2d(im, ker_y, mode='same')
im_x2 = im_x ** 2
im_y2 = im_y ** 2
im_xy = im_x * im_y

im_gx = signal.convolve2d(im_x2, ker_g, mode='same') 
im_gy = signal.convolve2d(im_y2, ker_g, mode='same') 
im_gxy = signal.convolve2d(im_xy, ker_g, mode='same') 
  
im_a = ( im_gx * im_gy - im_gxy*im_gxy) - 0.15*( im_gx + im_gy) ** 2
im_t = np.where(im_a > im_a.max()*0.01, 255, 0)

im_c = np.zeros([12, 12, 3])
im_o = np.zeros([12, 12, 3])
im_o[:,:,0] = im_o[:,:,1] = im_o[:,:,2] = np.clip(im, 0, 255)
coordinates = corner_harris(im, k =0.15)
im_c[coordinates>0.0001*coordinates.max()]=[255,0,0]
corner_coordinates = corner_peaks(coordinates)
coordinates_subpix = corner_subpix(im, corner_coordinates, window_size=13)

pylab.figure(figsize=(30,20))
pylab.subplot(221), pylab.imshow(im, cmap='gray'), pylab.title('original'), pylab.axis('off')
pylab.subplot(222), pylab.imshow(im_gx, cmap='gray'), pylab.title('gradient x'), pylab.axis('off')
pylab.subplot(223), pylab.imshow(im_a, cmap='gray'), pylab.title('gradient y'), pylab.axis('off')
#pylab.subplot(224), pylab.imshow(im_t, cmap='gray'), pylab.title('result'), pylab.axis('off')
#pylab.subplot(224), pylab.imshow(im_c), pylab.title('result'), pylab.axis('off')
    
pylab.subplot(224), pylab.imshow(im_o, interpolation='nearest')
pylab.plot(corner_coordinates[:, 1], corner_coordinates[:, 0], 'bo', markersize=5)
#pylab.plot(coordinates_subpix[:, 1], coordinates_subpix[:, 0], 'r+', markersize=10), pylab.axis('off')
pylab.tight_layout(), pylab.show()

#%%
#image = imread('../images/chess_football.png') # RGB image
image = imread('../images/pyramids2.jpg') # RGB image

image_harris = image.copy()
image_gray = rgb2gray(image)

coordinates = corner_harris(image_gray, k =0.01)
#image_harris[coordinates>0.01*coordinates.max()]=[255,0,0,255]
image_harris[coordinates>0.01*coordinates.max()]=[255,0,0]

corner_coordinates = corner_peaks(coordinates, min_distance=5, threshold_rel=0.01)
coordinates_subpix = corner_subpix(image_gray, corner_coordinates, window_size=11)

pylab.figure(figsize=(20,10))
pylab.subplot(211), pylab.imshow(image_harris), pylab.axis('off')
pylab.subplot(212), pylab.imshow(image, interpolation='nearest')
pylab.plot(corner_coordinates[:, 1], corner_coordinates[:, 0], 'bo', markersize=5)
pylab.plot(coordinates_subpix[:, 1], coordinates_subpix[:, 0], 'r+', markersize=10), pylab.axis('off')
pylab.tight_layout(), pylab.show()























