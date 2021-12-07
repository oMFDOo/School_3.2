import numpy as np
import cv2 as cv
import cvzone
#cap = cv.VideoCapture('vtest.avi')
cap = cv.VideoCapture(0)
# 이미지 사이즈 설정
cap.set(3, 640)
cap.set(4, 480)
#kernel = cv.getStructuringElement(cv.MORPH_ELLIPSE, (3,3))
#fgbg = cv.bgsegm.createBackgroundSubtractorMOG()
#fgbg = cv.bgsegm.BackgroundSubtractorGMG()
#fgbg = cv.createBackgroundSubtractorMOG2(detectShadows=True)
fgbg = cv.createBackgroundSubtractorKNN(detectShadows=True)
while True:
    ret, frame = cap.read()
    if frame is None:
        break
    fgmask = fgbg.apply(frame)
    #fgmask = cv.morphologyEx(fgmask, cv.MORPH_OPEN, kernel)


    # 이미지 스택(stackImages) :이미지 리스트, 열, 사이즈
    imgList = [frame, fgmask]
    imgStacked = cvzone.stackImages(imgList, 2, 1)
    
    cv.imshow("Image", imgStacked)
    

    keyboard = cv.waitKey(30)
    if keyboard == 'q' or keyboard == 27:
        break
cap.release()
cv.destroyAllWindows()