from matplotlib import pylab as pylab

from skimage.io import imread

from skimage.color import rgb2gray

from skimage.feature import corner_harris, corner_subpix, corner_peaks, match_descriptors, plot_matches

from skimage.transform import warp, SimilarityTransform, AffineTransform, resize

import cv2

import numpy as np

from skimage import data

from skimage.util import img_as_float

from skimage.exposure import rescale_intensity

from skimage.measure import ransac

 
#%% 매칭
temple = rgb2gray(img_as_float(imread('../images/5.jpg')))

image_original = temple.copy()

image_original_gray = rgb2gray(image_original)

affine_trans = AffineTransform(scale=(0.8, 0.9), rotation=0.1, translation=(120, -20))

image_warped = warp(image_original, affine_trans.inverse, output_shape=image_original.shape) # 원래 이미지를 어파인 변환을 통해 결과 얻음

image_warped_gray = rgb2gray(image_warped)

 

coordinates = corner_harris(image_original_gray)

coordinates[coordinates > 0.01*coordinates.max()] = 1

coordinates_original = corner_peaks(coordinates, threshold_rel=0.0001, min_distance=5)

 

coordinates = corner_harris(image_warped_gray)

coordinates[coordinates > 0.01*coordinates.max()] = 1

coordinates_warped = corner_peaks(coordinates, threshold_rel=0.0001, min_distance=5)

 

coordinates_original_subpix = corner_subpix(image_original_gray, coordinates_original, window_size=9)

coordinates_warped_subpix = corner_subpix(image_warped_gray, coordinates_warped, window_size=9)

 

#코너가 서로 비슷한지 check

matches = match_descriptors(coordinates_original, coordinates_warped, metric="euclidean", cross_check=True) 

#최적의 라인을 찾아감(랜덤이기에 완전 최적은 아님)

#어파인 변화 = model_robust, 대응 관계 점 = inliers에 저장

model_robust, inliers = ransac((coordinates_original[matches[:, 0]], coordinates_warped[matches[:, 1]]), AffineTransform, min_samples=3, residual_threshold=2, max_trials=100)

 

pylab.figure(figsize=(20,15))

ax = pylab.subplot(111)

plot_matches(ax, image_original_gray, image_warped_gray,

             coordinates_original, coordinates_warped,

             matches[inliers], matches_color ='b')

ax.axis('off')

pylab.show()