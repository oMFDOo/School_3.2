import cv2
from matplotlib import pylab as pylab

#아나콘다 shell에 입
#pip install opencv-python
#pip install opencv-contrib-python

#%% SIFT
img_src = cv2.imread('../images/book.png')
img_src = cv2.cvtColor(img_src, cv2.COLOR_BGR2RGB)
gray_src = cv2.cvtColor(img_src, cv2.COLOR_BGR2GRAY)

img_dst = cv2.imread('../images/books.png')
img_dst = cv2.cvtColor(img_dst, cv2.COLOR_BGR2RGB)
gray_dst = cv2.cvtColor(img_dst, cv2.COLOR_BGR2GRAY)


sift = cv2.SIFT_create()

# 서술자를 찾기위한 방법
# 1)찾으려는 특징점에 해당되는 키포인트 선정
# 키포인트 찾기
kp_src = cv2.detect(gray_src, None)
# 디스크립터 불러오기
kp_src, desc_src = sift.detectAndCompute(gray_src, None)
# 키포인트를 그려주는 함
img_srckey = cv2.drawKeypoints(img_src, kp_src, None, flags=cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)

kp_dst = cv2.detect(gray_dst, None)
kp_dst, desc_dst = sift.detectAndCompute(gray_src, None)
img_dstkey = cv2.drawKeypoints(img_dst, kp_dst, None, flags=cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)

# 매치
bf = cv2.BFMatcher()
# 해밍 거리를 이용하는 무언가
#bf = cv2.BFMatcher(cv2.NORM_HAMMING, crossCheck=True)
#matches= bf.match(desc_src, desc_dst)
# k 개 중에 가장 괜찮은 친구 찾기
matches = bf.knnmatch(desc_src, desc_dst, k = 2)

# 더 좋은 매치를 앞에 덜 좋은 애를 뒤에 소팅을 해주는 친구
good_matches = []
for m1, m2 in matches:
    # 이정도 차이가 나면 좋은 걸로 하겠다.
    if m1.distance < 0.75*m2.distance:
        good_matches.append([m1])

# good_matches[:20] : 20개만 보여달라
img_match = cv2.drawMatchesKnn(img_src, kp_src, img_dst, kp_dst, good_matches[:20], None, flags=2)

pylab.figure(figsize=(20, 20))

ax0 = pylab.subplot(212)
ax0.imshow(img_match)

ax1 = pylab.subplot(221)
ax1.imshow(img_srckey)

pylab.show()


#%% 오츄 알고리즘
import numpy as np
from skimage.transform import (hough_line, hough_line_peaks, hough_circle, hough_circle_peaks)
from skimage.draw import circle_perimeter
from skimage.io import imread, imsave
from skimage.color import rgb2gray, gray2rgb, label2rgb

image = rgb2gray(imread('../images/triangle_circle.png'))

# 기본적인 하프변환 방식
# 리턴값
# theta : 각도
# d : 거리
h, theta, d = hough_line(image)

# 원을 찾자!
# 50부터 100까지 1씩 반지름을 증가하면서 찾자!
hough_radii = np.arange(50, 100, 2)
hough_res = hough_circle(image, hough_radii)
# 교차 점 중 쓸만한 친구 가져오기 -> 중심점과 반지름 세트를 가져온다
accums, cx, cy, radii = hough_circle_peaks(hough_res, hough_radii, total_num_peaks=6)

# 원을 그리자
image_cir = gray2rgb(image)
for center_y, center_x, radius in zip(cy, cx, radii):
    # 중심값을 넣으면 좌표값을 리턴
    circy, circx = circle_perimeter(center_y, center_x, radius)
    image_cir[circy, circx] = (0.9, 0.2, 0.2)


pylab.figure(figsize=(20, 20))

pylab.subplot(221)
pylab.imshow(image, cmap='gray')

pylab.subplot(222)
pylab.imshow(np.log(1 + h),
             extent=[10*np.rad2deg(theta[-1]), np.rad2deg(theta[0]), d[-1], d[0]],
             cmap='hot', aspect=1/1.5)


# 그림 위에 빨간선 그리기
ax0 = pylab.subplot(223)
ax0.imshow(image, cmap='gray')
# hough_line_peaks의 역할 : 최 상위점을 찍는 점을 가져와라.
for _, angle, dist in zip(*hough_line_peaks(h, theta, d)):
    y0 = (dist - 0 * np.cos(angle)) / np.sin(angle)               # 직방 계산중
    y1 = (dist - image.shape[1] * np.cos(angle)) / np.sin(angle)  # 직방 계산중
    ax0.plot((0, image.shape[1]), (y0, y1), '-r')
ax0.set_xlim((0, image.shape[1]))
ax0.set_ylim((image.shape[0], 0))


pylab.subplot(2, 2, 4)
pylab.imshow(image_cir)

pylab.show()

























