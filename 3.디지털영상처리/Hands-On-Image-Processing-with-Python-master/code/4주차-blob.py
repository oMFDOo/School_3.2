# 그림 그리기
from matplotlib import pylab
from skimage.io import imread
from skimage.color import rgb2gray
import numpy as np

# blob 인식을 위함
from skimage.feature import blob_log, blob_dog, blob_doh

#%% LoG / DoG / DoH
im = imread("../images/butterfly.png")
im_gray = rgb2gray(im)

# defult : min_sigma = 1, max_sigma = 50
# 시그마 = r/루트(2)
# num_sigma : min~max까지 num_sigma로 단계를 나누겠다.
# threshold : 한계점

# LoG
log_blobs = blob_log(im_gray, max_sigma = 30, num_sigma = 10, threshold = 0.2)

# DoG
#log_blobs = blob_dog(im_gray, max_sigma = 30, threshold = 0.2)

# DoH
#log_blobs = blob_doh(im_gray, max_sigma = 30, threshold = 0.005)

# 각 채널에 값(y값, x값, 반지름)을 넣었다.
log_blobs[:, 2] = log_blobs[:, 2]*np.sqrt(2)


pylab.figure( figsize=(30, 20))
pylab.subplot(1, 3, 1), pylab.imshow(im)
pylab.subplot(1, 3, 2), pylab.imshow(im_gray)

ax = pylab.subplot(1, 3, 3)
pylab.imshow(im), pylab.axis("off")
for blob in log_blobs:
    y, x, r = blob
    # 패스 설정 x,y 위치에 r사이즈로 라임색 두께가 이고 칠이 없는 원을 그린다.
    p = pylab.Circle((x, y), r, color='Lime', linewidth=2, fill= False)
    # 패치 붙여넣기
    ax.add_patch(p)
pylab.show()

#%% 물체 지우기

from PIL import Image
from PIL.ImageChops import difference

import numpy as np

# 클로징을 해주는 친구 : 모폴로지 연산을 위함 + 컴벡스헐
from skimage.morphology import area_closing, convex_hull_image

backim = Image.open("../images/background.png")
foreim = Image.open("../images/foreground.png")

# 차이값 이용
diff = difference(foreim, backim)
diff = diff.convert('L')

diffarr = np.clip(np.array(diff), 0, 255)

# 조건에 해당되면 픽셀 값을 가져와라
thrarr = np.where( diffarr > 25, 255, 0)

# 모폴로지연산 : 닫기
closeim = area_closing(thrarr)

# 컴벡스헐
chull = convex_hull_image(closeim)

pylab.figure( figsize=(30, 20))
pylab.subplot(2, 2, 1), pylab.imshow(diff, cmap="gray")
pylab.subplot(2, 2, 2), pylab.imshow(thrarr, cmap="gray")
pylab.subplot(2, 2, 3), pylab.imshow(closeim, cmap="gray")
pylab.subplot(2, 2, 4), pylab.imshow(chull, cmap="gray")










