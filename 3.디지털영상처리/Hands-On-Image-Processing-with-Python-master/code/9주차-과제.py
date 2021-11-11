import numpy as np
import matplotlib.pyplot as plt
from skimage.io import imread
from skimage.color import rgb2gray
from skimage.segmentation import felzenszwalb, slic, quickshift, watershed
from skimage.segmentation import mark_boundaries, find_boundaries
from skimage.util import img_as_float


def plot_image(img, title, cmap='gray'):
    plt.imshow(img, cmap)
    plt.title(title, size=20)
    plt.axis('off')    

#%% 군집    
# 숫자가 커질수록 해상도가 줄어든다[::4, ::4, :3]
img = imread('../images/10.jpg')[::2, ::2, :3]
# 커널 사이즈 max_dist:최대 거리 100 정보의 ratio:색상과 거리의 조절
# ratio값이 커지면 조금 더 색상 기준으로 나눈다.
segments_quick = quickshift(img, kernel_size=3, max_dist=300, ratio=0.5)
segments_mark = mark_boundaries(img, segments_quick)

plt.figure(figsize=(20,20))
plot_image(segments_mark, "Result")
plt.show()

#%% Region growing

# pip install SimpleITK
import SimpleITK as sitk

img = 255*rgb2gray(imread('../images/10.jpg'))
img_T1 = sitk.GetImageFromArray(img) 
img_T1_255 = sitk.Cast(sitk.RescaleIntensity(img_T1), sitk.sitkUInt8)

# 기반 위치 설정
seed = (100,120)
# 확률적으로 임계값 설정
# lower/upper : 영역확장의 최소/최대 크
seg = sitk.ConnectedThreshold(img_T1, seedList=[seed], lower=40, upper=80)
# 원본과 겹친 이미지
overlay = sitk.LabelOverlay(img_T1_255, seg)

plt.figure(figsize=(20,20))
plot_image(sitk.GetArrayViewFromImage(overlay), "Result")
plt.show()

#%% watershed
from skimage.filters import sobel

img = imread('../images/10.jpg')[::2, ::2, :3]
# 에지 탐색
gradient = sobel(rgb2gray(img))
# markers : 댐의 높이/크기
# compactness : 높은 값일 수록 일반적인 다각형
segments_watershed = watershed(gradient, markers=100, compactness=0.001)
segments_mark = mark_boundaries(img, segments_watershed)

plt.figure(figsize=(20,20))
plot_image(segments_mark, "Result")
plt.show()

#%% graph-based : Felzenszwalb
from matplotlib.colors import LinearSegmentedColormap

org = imread('../images/10.jpg')[::2, ::2, :3]
img = img_as_float(org)
segments_fz = felzenszwalb(img, scale=100, sigma=0.5, min_size=100)
segments_mark = mark_boundaries(img, segments_fz)

# 색상 면 만드는 법
borders = find_boundaries(segments_fz)
unique_colors = np.unique(segments_fz.ravel())
segments_fz[borders] = -1 
colors = [np.zeros(3)]
for color in unique_colors:
  # 영역을 받아와서 거기에 색상 평균값 적용
  colors.append(np.mean(img[segments_fz == color], axis=0))    
cm = LinearSegmentedColormap.from_list('pallete', colors, N=len(colors))

plt.figure(figsize=(20,20))
# 영역만 나눈 영상
#plot_image(segments_mark, "Result")
# cmap 속성을 방금 만든 색상 면 적용한 거
plot_image(segments_fz, "Result", cmap=cm)
plt.show()

#%% SLIC

img = imread('../images/10.jpg')[::2, ::2, :3]

plt.figure(figsize=(12,12))
i = 1
for compactness in [0.1, 1, 10, 100]:
    plt.subplot(2,2,i)
    segments_slic = slic(img, n_segments=250, compactness=compactness, sigma=1)
    plot_image(mark_boundaries(img, segments_slic), 'compactness=' + str(compactness))
    i += 1
plt.suptitle('SLIC', size=30)
plt.tight_layout(rect=[0, 0.03, 1, 0.95])
plt.show()

#%% Active contours
from skimage import data
from skimage.filters import gaussian
from skimage.segmentation import active_contour
img = imread('../images/10.jpg')[::2, ::2, :3]
img_gray = rgb2gray(img)
s = np.linspace(0, 2*np.pi, 2000)
x = 620 + 100*np.cos(s)
y = 600 + 100*np.sin(s)
init = np.array([y, x]).T
i = 1
plt.figure(figsize=(20,20))
for max_it in [20, 30, 50, 100]:
    snake = active_contour(gaussian(img_gray, 3), init, alpha=0.015, beta=10, gamma=0.001, max_iterations=max_it)
    plt.subplot(2,2,i), plt.imshow(img), plt.plot(init[:, 1], init[:, 0], '--b', lw=3)
    plt.plot(snake[:, 1], snake[:, 0], '-r', lw=3)
    plt.axis('off'), plt.title('max_iteration=' + str(max_it), size=20)
    i += 1
plt.tight_layout(), plt.show()









