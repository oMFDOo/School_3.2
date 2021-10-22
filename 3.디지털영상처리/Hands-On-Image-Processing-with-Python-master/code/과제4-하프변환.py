import cv2
from matplotlib import pylab as pylab
import numpy as np
from skimage.transform import (hough_line, hough_line_peaks, hough_circle, hough_circle_peaks)
from skimage.draw import circle_perimeter
from skimage.io import imread, imsave
from skimage.filters import sobel, threshold_otsu
from skimage.color import rgb2gray, gray2rgb, label2rgb
from skimage import filters, feature, img_as_float, exposure, img_as_ubyte


import matplotlib.pyplot as plt
from matplotlib import cm

#%%
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
#%% 오츄 알고리즘


image = rgb2gray(imread('../images/8.jpg'))

# 오츄 알고리즘 적용
# thresh = threshold_otsu(image)
# binary = image > (thresh * 1.2)

# LoG
# im_g = filters.gaussian(image, 2)
# im_l = filters.laplace(im_g)
# binary = zero_cross(im_l, T=np.max(im_l)*0.015)

# DoG
im_dog = filters.difference_of_gaussians(image, 2.0)
binary = zero_cross(im_dog, T=np.max(im_dog)*0.04)

# 캐니
# binary = feature.canny(image, sigma=2)


binary = binary.astype('bool')


# Classic straight-line Hough transform
h, theta, d = hough_line(binary)
print(h)
print(theta)
print(d)
#print(*hough_line_peaks(h, theta, d))

# Generating figure 1
fig, axes = plt.subplots(2, 2, figsize=(20, 20))
ax = axes.ravel()



hough_radii = np.arange(30, 80, 1)
hough_res = hough_circle(binary, hough_radii)

ax[0].imshow(image, cmap=cm.gray)
ax[0].set_title('Input image', size=20)
ax[0].set_axis_off()

ax[1].imshow(np.log(1 + h),
             extent=[10*np.rad2deg(theta[-1]), np.rad2deg(theta[0]), d[-1], d[0]],
             cmap=cm.hot, aspect=1/1.5)
ax[1].set_title('Hough transform', size=20)
ax[1].set_xlabel('Angles (degrees)', size=20)
ax[1].set_ylabel('Distance (pixels)', size=20)
ax[1].axis('image')

ax[2].imshow(binary, cmap=cm.gray)
for _, angle, dist in zip(*hough_line_peaks(h, theta, d)):
    y0 = (dist - 0 * np.cos(angle)) / np.sin(angle)
    y1 = (dist - binary.shape[1] * np.cos(angle)) / np.sin(angle)
    ax[2].plot((0, image.shape[1]), (y0, y1), '-r')
ax[2].set_xlim((0, image.shape[1]))
ax[2].set_ylim((image.shape[0], 0))
ax[2].set_axis_off()
ax[2].set_title('Detected lines', size=20)




# Select the most prominent 5 circles
accums, cx, cy, radii = hough_circle_peaks(hough_res, hough_radii, total_num_peaks=5)

image = gray2rgb(image)
for center_y, center_x, radius in zip(cy, cx, radii):
    circy, circx = circle_perimeter(center_y, center_x, radius)
    image[circy, circx] = (0.9, 0.1, 0.1)

ax[3].imshow(image, cmap=plt.cm.gray)
ax[3].set_axis_off()
ax[3].set_title('Detected Circles', size=20)

print("end")
plt.tight_layout()
plt.show()