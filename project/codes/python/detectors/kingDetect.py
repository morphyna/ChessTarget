# Importamos librerias
import torch
import cv2
import urllib.request
import numpy as np

#url ='http://192.168.1.5/cam-lo.jpg'
#url ='http://192.168.1.5/cam-hi.jpg'
#modelPath = '/home/morphyna/Documentos/GITHUB/ChessTarget/Proyecto/models/best.pt'


def kingDetector(url, modelPath):
    winName = 'CAM'
    cv2.namedWindow(winName, cv2.WINDOW_AUTOSIZE)
    scale_percent = 80

    # Leemos el modelo
    model = torch.hub.load('ultralytics/yolov5', 
                        'custom',
                        path = modelPath)

    # Empezamos
    while True:
        #videocaptura
        imgResponse = urllib.request.urlopen(url)
        imgNp = np.array(bytearray(imgResponse.read()), dtype = np.uint8)
        img = cv2.imdecode(imgNp, -1)

        img = cv2.rotate(img, cv2.ROTATE_90_COUNTERCLOCKWISE)

        detect = model(img)

        cv2.imshow("King detecter", np.squeeze(detect.render()))

        key = cv2.waitKey(5)

        if key == 27:
            break


    cv2.destroyAllWindows()