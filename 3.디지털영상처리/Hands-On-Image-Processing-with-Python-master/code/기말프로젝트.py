# import numpy as np
# import cv2

# def backSubtraction():
# 	cap = cv2.VideoCapture(0)
# 	cap.set(3, 480)
# 	cap.set(4, 320)
# 	mog = cv2.bgsegm.createBackgroundSubtractorMOG()
# 	mog = cv2.createBackgroundSubtractorMOG2()	

# 	while True:
# 		ret, frame = cap.read()
# 		fgmask = mog.apply(frame)
# 		cv2.imshow('mask', fgmask)
# 		k = cv2.waitKey(1) & 0xFF
# 		if k == 27:
# 			break
# 	cap.relase()
# 	cv2.destroyAllWindows()

# backSubtraction()

import cv2
import cvzone
from cvzone.SelfiSegmentationModule import SelfiSegmentation
import os

cap = cv2.VideoCapture(0)
# 이미지 사이즈 설정
cap.set(3, 640)
cap.set(4, 480)
# 영상 프레임 60으로 설정
cap.set(cv2.CAP_PROP_FPS,60)
# 배경영상 불러오기
# imgBg = cv2.imread("../images/bg/bg1.png")

# 모든 이미지 불러오기
listImg = os.listdir("../images/bg/")
bgList = []
for imgPath in listImg:
	img = cv2.imread(f'../images/bg/{imgPath}')
	bgList.append(img)
    
# 불러올 이미지 번호
imgIndex = 0



# 배경과 전경 분할
# SelfiSegmentation(0) : 일반화모델
# SelfiSegmentation(1) : 약간느려짐, 디폴트
segmentor = SelfiSegmentation(0)
# 프레임 정보를 저장할 것임
fpsReader = cvzone.FPS()

while True:
	success, img = cap.read()
	# 배경이미지 제거 removeBG(입력영상, 배경이미지-색상/이미지)
	imgOut = segmentor.removeBG(img, bgList[imgIndex], threshold=0.8)

    # 이미지 스택(stackImages) :이미지 리스트, 열, 사이즈
	imgList = [img, imgOut]
	imgStacked = cvzone.stackImages(imgList, 2, 1)
    # fps와 stackImage를 반환하는데 fps는 무시 (_, : 무시)
	_, imgStacked = fpsReader.update(imgStacked, color=(255, 30, 40), scale=2, thickness=2)
    
    
	cv2.imshow("Image", imgStacked)
	# 지연시간
	key = cv2.waitKey(1)
	if key == ord('w') :
		if imgIndex > 0 :
			imgIndex += 1
	elif key == ord('s') :
		if imgIndex < len(imgList)-1 :
			imgIndex -= 1
	elif key == ord('q') :
		break