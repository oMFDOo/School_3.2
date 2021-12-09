import numpy as np
import cv2 as cv2
import cvzone
#cap = cv2.VideoCapture('vtest.avi')
cap = cv2.VideoCapture(0)
# 이미지 사이즈 설정
cap.set(3, 640)
cap.set(4, 480)

fgbg = cv2.createBackgroundSubtractorKNN(detectShadows=True)
while True:
    ret, frame = cap.read()
    if frame is None:
        break
    fgmask = fgbg.apply(frame)
    
    kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (3,3))
    fgmask = cv2.morphologyEx(fgmask, cv2.MORPH_OPEN, kernel)
    
    dst = cv2.imread('../images/bg1.png', cv2.IMREAD_COLOR)
    
    # cv2.copyTo(frame, fgmask, dst)

    # 이미지 스택(stackImages) :이미지 리스트, 열, 사이즈
    imgList = [frame, fgmask]
    imgStacked = cvzone.stackImages(imgList, 2, 1)
    
    cv2.imshow("Image", imgStacked)
    

    keyboard = cv2.waitKey(30)
    if keyboard == ord('q') :
        break
cap.release()
cv2.destroyAllWindows()