# 히스토그램 처리(10주차)

import cv2
import numpy as np
from skimage import data, img_as_float, img_as_ubyte, exposure, io, color
from skimage.io import imread
from skimage.exposure import cumulative_distribution
from skimage.restoration import denoise_bilateral, denoise_nl_means, estimate_sigma
from skimage.util import random_noise
from skimage.color import rgb2gray
from PIL import Image, ImageEnhance, ImageFilter
from scipy import ndimage, misc
import matplotlib.pylab as pylab
from skimage import filters, feature, img_as_float, exposure
from skimage.segmentation import felzenszwalb, slic, quickshift, watershed
from skimage.segmentation import mark_boundaries, find_boundaries
import matplotlib.pyplot as plt
import copy

# 한글출력을 위함
from PIL import ImageFont, ImageDraw, Image

#%%
# 히스토그램 평활화
def equalize_func(im):
    hist = exposure.equalize_hist(im)
    return hist

# 콘트라스트 스트레칭
def contrast_str_func(im):
    from_, to_ = np.percentile(im, (2, 98))
    cont_ = exposure.rescale_intensity(im, in_range=(from_, to_))
    return cont_
  
#%%
import cv2
import cvzone
from cvzone.SelfiSegmentationModule import SelfiSegmentation
import os
import numpy as np


cap = cv2.VideoCapture(0)
# 이미지 사이즈 설정
cap.set(3, 640)
cap.set(4, 480)
# 영상 프레임 60으로 설정
cap.set(cv2.CAP_PROP_FPS,60)
# 배경영상 불러오기
# imgBg = cv2.imread("../images/bg/bg1.png")

# 경로 상의 모든 이미지 불러오기
listImg = os.listdir("../images/bg/")
bgList = []
for imgPath in listImg:
	img = cv2.imread(f'../images/bg/{imgPath}')
    # 깔끔한 처리를 위한 이미지 평활화
	bgList.append(img)
    
# 불러올 모드 번호
imgIndex = 0
textIndex = 0
testMode = 0
isImageMode = False
isBlurMode = False
isTextMode = False
isObjectMode = False

# 글자출력 정보
b = [255, 255, 40]
g = [255, 50, 40]
r = [255, 255, 255]
a = 0
fontpath = ["../fonts/210+Byulbitcha R.ttf", "../fonts/210+마녀의숲B.ttf", "../fonts/a로케트.ttf", "../fonts/210+블라블라R.ttf"]
fontsize = [40, 60, 50]
fontX = [160, 100, 30]
fontY = [50, 70, 60]
textTitle = ["▼ 오늘 제일 잘 노는 애 ▼", "날 막을 자는\n없다!", "Build failed\n   with an\n exception"]
testModeTitle = ["기본배경 + 인물검출", "기본배경 + 동적 물체 검출", "블러배경 + 인물 검출", "블러배경 + 동적 물체 검출", "이미지 배경 + 인물 검출", "이미지 배경 + 동적 물체 검출"]
textModeTitle = ["텍스트 ON", "텍스트 OFF"]
info = "O : 인물검출 모드 / 동적물체검출 모드\nB : 배경 블러처리 \nI : 배경 임의의 이미지 사용\n   - W : 다음이미지\n   - S : 이전이미지\nT : 텍스트 출력\n   - A : 이전텍스트\n   - D : 다음텍스트\nQ : 종료"

fgbg = cv2.createBackgroundSubtractorKNN(detectShadows=True)


# 배경과 전경 분할
# SelfiSegmentation(0) : 일반화모델
# SelfiSegmentation(1) : 약간느려짐, 디폴트
segmentor = SelfiSegmentation(0)
# 프레임 정보를 저장할 것임
fpsReader = cvzone.FPS()

while True:
	success, img = cap.read()
    
	if img is None:
		break
      
    # 인물검출 모드 마스크/커널 설정
	fgmask = fgbg.apply(img)
    # 커널 마스크 생성
	kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (3,3))
    # 모폴로지 열림 연산으로 조금 더 입자가 크도록 연출
	fgmask = cv2.morphologyEx(fgmask, cv2.MORPH_OPEN, kernel)
    
    # 블러모드
	if isBlurMode == True :
		temp = cv2.GaussianBlur(img, (0, 0), 3)
        # 오브젝트 검출 모드
		if isObjectMode == True :  
				cv2.copyTo(img, fgmask, temp)
				imgOut = temp
				testMode = 3
		# 인물 검출 모드
		else :
		        # 배경이미지 제거 removeBG(입력영상, 배경이미지-색상/이미지)
				imgOut = segmentor.removeBG(img, temp, threshold=0.5)
				testMode = 2
                
                
    # 이미지모드
	elif isImageMode == True :
		# 오브젝트 검출 모드
		if isObjectMode == True :  
                # 얕은 복사로 일어난 오류 제거
				temp = copy.deepcopy(bgList[imgIndex])
				cv2.copyTo(img, fgmask, temp)
				imgOut = temp
				testMode = 5
		# 인물 검출 모드
		else :
				# 배경이미지 제거 removeBG(입력영상, 배경이미지-색상/이미지)
				imgOut = segmentor.removeBG(img, bgList[imgIndex], threshold=0.5)
				testMode = 4
                
                
    # 기본모드
	else:
		# 오브젝트 검출 모드
		if isObjectMode == True :
				temp = cv2.copyTo(img, fgmask)
				imgOut = temp
				testMode = 1
		else :
				# 기본화면
				imgOut = segmentor.removeBG(img, (0, 0, 0), threshold=0.5)
				testMode = 0




    # 텍스트모드
	if isTextMode == True :
		img_pil = Image.fromarray(imgOut)
		draw = ImageDraw.Draw(img_pil)
		font = ImageFont.truetype(fontpath[textIndex], fontsize[textIndex])
		draw.text((fontX[textIndex], fontY[textIndex]), textTitle[textIndex], font=font, fill=(b[textIndex],g[textIndex],r[textIndex],a))
		imgOut = np.array(img_pil)
    
    
    # 각 모드 정보 출력
	img_pil2 = Image.fromarray(imgOut)
	draw = ImageDraw.Draw(img_pil2)
	font = ImageFont.truetype(fontpath[3], 35)
	draw.text((10,10), testModeTitle[testMode], font=font, fill=(255, 255, 255, a))
	imgOut = np.array(img_pil2)
    
    # 사용 출력
	img_pil2 = Image.fromarray(img)
	draw = ImageDraw.Draw(img_pil2)
	font = ImageFont.truetype(fontpath[3], 30)
	draw.text((10,60), info, font=font, fill=(0, 0, 0, a))
	img = np.array(img_pil2)
    
    
    # 이미지 스택(stackImages) :이미지 리스트, 열, 사이즈
	imgList = [img, imgOut]
	imgStacked = cvzone.stackImages(imgList, 2, 1)
    # fps와 stackImage를 반환하는데 fps는 무시 (_, : 무시)
	_, imgStacked = fpsReader.update(imgStacked, color=(255, 30, 40), scale=2, thickness=2)
    
    
	imgMax = len(imgList)+1;
    
	cv2.imshow("Image", imgStacked)
	# 지연시간
	key = cv2.waitKey(1)
    # 이미지 모드 배경 전환
	if key == ord('w') :
		if len(imgList) >= imgIndex and isImageMode == True :          
			imgIndex += 1
	elif key == ord('s') :
		if imgIndex >= 0 and isImageMode == True :
			imgIndex -= 1
    # 이미지 모드 on/off
	elif key == ord('i') :
		if isImageMode == True :
			isImageMode = False
		else :
			isImageMode = True;   
			isBlurMode = False  # 이미지모드 시 블러모드 끄기 
            
            
    # 텍스트 모드 변경
	elif key == ord('d') :
		if textIndex < 2 and isTextMode == True :          
			textIndex += 1
	elif key == ord('a') :
		if textIndex > 0 and isTextMode == True :
			textIndex -= 1
    # 텍스트 모드 on/off
	elif key == ord('t') :
		if isTextMode == True :
			isTextMode = False
		else :
			isTextMode = True;
            
    # 오브젝트 검출 모드 on/off
	elif key == ord('o') :
		if isObjectMode == True :
			isObjectMode = False
		else :
			isObjectMode = True;
            
    # 블러 모드 on/off
	elif key == ord('b') :
		if isBlurMode == True :
			isBlurMode = False
		else :
			isBlurMode = True;     
			isImageMode = False  # 블러모드 시 이미지모드 끄기
	elif key == ord('q') :
		break
cap.release()
cv2.destroyAllWindows()