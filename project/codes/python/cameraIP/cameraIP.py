import cv2
import urllib.request
import numpy as np

#url = 'http://192.168.1.5/cam-hi.jpg'
#url = 'http://192.168.1.5/cam-lo.jpg'

def cameraIP(url):
    winName = 'CAM'
    cv2.namedWindow(winName, cv2.WINDOW_AUTOSIZE)
    scale_percent = 80
    while(1):
        imgResponse = urllib.request.urlopen(url)
        imgNp = np.array(bytearray(imgResponse.read()), dtype = np.uint8)
        img = cv2.imdecode(imgNp, -1)


        img = cv2.rotate(img, cv2.ROTATE_90_COUNTERCLOCKWISE)
        #gris = cv2.imdecode(img, cv2.COLOR_BGR2GRAY)

        cv2.imshow(winName, img)

        tecla = cv2.waitKey(5) & 0xFF
        if tecla == 27:
            break

    cv2.destroyAllWindows()