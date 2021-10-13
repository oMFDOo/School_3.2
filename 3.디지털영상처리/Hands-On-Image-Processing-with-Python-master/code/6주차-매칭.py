from matplotlib import pylab as pylab
from skimage.io import imread
from skimage.color import rgb2gray
from skimage.feature import corner_harris, corner_subpix, corner_peaks, plot_matches, match_descriptors, BRIEF
from skimage.transform import AffineTransform, warp
from skimage.util import img_as_float
from skimage.measure import ransac
from skimage.transform import AffineTransform
import numpy as np

#%% match
temple = rgb2gray(img_as_float(imread('../images/temple.jpg')))
image_original = temple.copy()
image_original_gray = rgb2gray(image_original)

affine_trans =  AffineTransform(scale=(0.8, 0.9), rotation=0.1, translation=(120, -20))
image_warped = warp(image_original, affine_trans.inverse, output_shape=image_original.shape)
image_warped_gray = rgb2gray(image_warped)

# 0.05 된 곳 값을 줄이면  좌표 범위가 줄어서...? 더 빨라진다.
coordinates = corner_harris(image_original_gray, k=0.02)
coordinates[coordinates > 0.05*coordinates.max()] = 1
coordinates_original = corner_peaks(coordinates, threshold_rel=0.05, min_distance=5)
coordinates_original_subpix = corner_subpix(image_original_gray, coordinates_original, window_size=9)


coordinates = corner_harris(image_warped_gray, k=0.02)
coordinates[coordinates > 0.05*coordinates.max()] = 1
coordinates_warped = corner_peaks(coordinates, threshold_rel=0.05, min_distance=5)
coordinates_warped_subpix = corner_subpix(image_warped_gray, coordinates_warped, window_size=9)

##BRIFE##

extractor = BRIEF()
extractor.extract(image_original_gray, coordinates_original)
keypoints1, descriptors1 = coordinates_original[extractor.mask], extractor.descriptors


extractor.extract(image_original_gray, coordinates_original)
keypoints2, descriptors2 = coordinates_original[extractor.mask], extractor.descriptors

# BRIFE 쓸 떄만 키기
matches = match_descriptors(descriptors1, descriptors2, metric='hamming', cross_check=True)
# 뭐 어떻게 하던데 모르겠다 model, inliers = ransac( (source, destination), AffineTransform, min_samples=3, residual_threshold=1, max_trials=100 )


#########

# 코너 매치해보기
def match_corner(coordinates, window_ext=3):
    row, col = coordinates
    window_original = image_original[row-window_ext:row+window_ext+1, col-window_ext:col+window_ext+1]
    SSDs = []
    for coord_row, coord_col in coordinates_warped:
        window_warped = image_warped[coord_row-window_ext:coord_row+window_ext+1,
        coord_col-window_ext:coord_col+window_ext+1]
        if window_original.shape == window_warped.shape:
            SSD = np.sum((window_original - window_warped)**2)
            SSDs.append(SSD)
    min_idx = np.argmin(SSDs)
    return coordinates_warped[min_idx]

source, destination = [], []
for src_coord in coordinates_original :
  dest_coord = match_corner(src_coord)
  if len(dest_coord) > 0:
    # 소스 코디네이션 각도 추가
    source.append(src_coord)
    # 찾은 좌표값 넣기
    destination.append(dest_coord)

# 소스와 데스티네이션이 매치됨    
source = np.array(source)
destination = np.array(destination)


# 저거 두개가 매치 되었기 때문에 필요 없어짐
# 아래 매치 보면 유클리디언 거리 쓰는데 마할라노비스 거리쓰면 더 좋지 않을까?
# matches = match_descriptors(coordinates_original, coordinates_warped, metric='euclidean', cross_check=True)
# model = AffineTransform이 나옴
# inliers = 해당되는 점들이 나옴 true, false로
model, inliers = ransac( (source, destination), AffineTransform, min_samples=3, residual_threshold=1, max_trials=100 )

# 보여줄 인덱스 좌표 생성
indx = np.arange(source.shape[0])
# inlier만 보여주고 싶다
indx = np.nonzero(inliers)[0]


pylab.figure(figsize=(20,15))
ax1 = pylab.subplot(212)
plot_matches(ax1, image_original_gray, image_warped_gray, coordinates_original, coordinates_warped,  np.column_stack((indx, indx)))
ax1.axis('off'), ax1.set_title('Correct correspondences', size=20)

ax2 = pylab.subplot(221)
ax2.imshow(image_original_gray, interpolation='nearest', cmap='gray')
ax2.plot(coordinates_original[:, 1], coordinates_original[:, 0], 'bo', markersize=5)
ax2.axis('off'), ax2.set_title('Original', size=20)

ax3 = pylab.subplot(222)
ax3.imshow(image_warped_gray, interpolation='nearest', cmap='gray')
ax3.plot(coordinates_warped[:, 1], coordinates_warped[:, 0], 'ro', markersize=5)
ax3.axis('off'), ax3.set_title('Warped', size=20)

pylab.show()

#%% HOG

from skimage.feature import hog
from skimage import exposure
image = rgb2gray(imread('../images/cameraman.jpg'))
fd, hog_image = hog(image, orientations=8, pixels_per_cell=(16, 16),
cells_per_block=(1, 1), visualize=True)
print(image.shape, len(fd))
# ((256L, 256L), 2048)
fig, (axes1, axes2) = pylab.subplots(1, 2, figsize=(15, 10), sharex=True, sharey=True)
axes1.axis('off'), axes1.imshow(image, cmap=pylab.cm.gray), axes1.set_title('Input image')
hog_image_rescaled = exposure.rescale_intensity(hog_image, in_range=(0, 10))
axes2.axis('off'), axes2.imshow(hog_image_rescaled, cmap=pylab.cm.gray),
axes2.set_title('Histogram of Oriented Gradients')
pylab.show()

#%% BRIEF