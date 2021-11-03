import numpy as np
from skimage.transform import (hough_line, hough_line_peaks, hough_circle, hough_circle_peaks)
from skimage.draw import circle_perimeter
from skimage.feature import canny
from skimage.data import astronaut
from skimage.io import imread, imsave
from skimage.color import rgb2gray, gray2rgb, label2rgb
from skimage import img_as_float
from skimage.morphology import skeletonize
from skimage import data, img_as_float
import matplotlib.pyplot as plt
from matplotlib import cm
from skimage.filters import sobel, threshold_otsu
from skimage.feature import canny
from skimage.segmentation import felzenszwalb, slic, quickshift, watershed
from skimage.segmentation import mark_boundaries, find_boundaries

#%% 동전의 경계검출
# 사이언스 킷 내장 이미지
coins = data.coins()
hist = np.histogram(coins, bins=np.arange(0, 256), normed=True)
#print(hist)

# 캐니로 엣지 검출
# 시그마가 2일땐 필링이 잘 안 되더니
# 3이니까 되네! 노이즈가 많았구나!
edges = canny(coins, sigma=3)

# 경계만큼 채워 넣기
from scipy import ndimage as ndi
fill_coins = ndi.binary_fill_holes(edges)

# 그림그리기
from skimage.color import label2rgb
# 분할된 이미지에 대해 레이블링
labeled_coins, _ = ndi.label(fill_coins)
print(np.unique(labeled_coins))
image_label_overlay = label2rgb(labeled_coins, image=coins)

fig, axes = plt.subplots(3, 2, figsize=(10, 10))
# 원본이미지와 히스토그램 확인
axes[0][0].imshow(coins, cmap=plt.cm.gray, interpolation='nearest')
axes[0][0].axis('off')
axes[0][1].plot(hist[1][:-1], hist[0], lw=2)
axes[0][1].set_title('histogram of gray values')
# 캐니로 검출한 선 내용 확인
axes[1][0].imshow(edges, cmap=plt.cm.gray, interpolation='nearest')
axes[1][0].set_title('Canny detector')
axes[1][0].axis('off')
# 채워낸 이미지 확인
axes[1][1].imshow(fill_coins, cmap=plt.cm.gray, interpolation='nearest')
axes[1][1].set_title('filling the holes')
axes[1][1].axis('off')
# 분할한 이미지 확인
axes[2][0].imshow(coins, cmap=plt.cm.gray, interpolation='nearest')
axes[2][0].contour(fill_coins, [0.5], linewidths=1.2, colors='y')
axes[2][1].imshow(image_label_overlay, interpolation='nearest')
plt.show()
