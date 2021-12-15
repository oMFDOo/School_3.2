import cv2

cap = cv2.VideoCapture('./images/envplay.mp4')

if not (cap.isOpened()):
    print("Could not open video file")
    
cv2.namedWindow('preview')

while(True): 
    ret, frame = cap.read()
    if not ret :
        break
    
    cv2.imshow('preview',frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()