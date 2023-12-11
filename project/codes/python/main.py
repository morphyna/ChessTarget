from pdi.selfLabeler import * 
from cameraIP.cameraIP import *
from cameraIP.handlerJson import *
from detectors.kingDetect import *

import os

autoDataPath = '/home/morphyna/Documentos/GITHUB/ChessTarget/project/autoData/'
dataPath = '/home/morphyna/Documentos/GITHUB/ChessTarget/project/data/'
modelPath = '/home/morphyna/Documentos/GITHUB/ChessTarget/project/models/best.pt'
paths = {
    'autoData': os.path.join(autoDataPath, 'images'),
    'images' : os.path.join(dataPath, 'images/train'),
    'images_val' : os.path.join(dataPath, 'images/val'),
    'labels' : os.path.join(dataPath, 'labels/train'),
    'labels_val' : os.path.join(dataPath, 'labels/val')
}
urls = {
    'resHi'  :'http://192.168.1.5/cam-hi.jpg',
    'resLo'  :'http://192.168.1.5/cam-lo.jpg', 
    'status' :'http://192.168.1.5/status',
}


def pdi():
    images, name_images = getImages(paths['autoData'])
    for i in range(len(images)):
        if i%3!=0:
            copyImage(os.path.join(paths['autoData'], name_images[i]+'.jpg'),os.path.join(paths['images'], name_images[i]+'.jpg'))
        else:
            copyImage(os.path.join(paths['autoData'], name_images[i]+'.jpg'),os.path.join(paths['images'], name_images[i]+'.jpg'))
            copyImage(os.path.join(paths['autoData'], name_images[i]+'.jpg'),os.path.join(paths['images_val'], name_images[i]+'.jpg'))

        numLabel = labelName(name_images[i])
        nameText = name_images[i] + '.txt'
        pathText = os.path.join(paths['labels'], nameText)
        connectedBorderDetectorYUV(images[i], numLabel, pathText)
        
    images_val, name_images_val = getImages(paths['images_val'])
    for i in range(len(images_val)):
        numLabel_val = labelName(name_images_val[i])
        nameText_val = name_images_val[i] + '.txt'
        pathText_val = os.path.join(paths['labels_val'], nameText_val)
        connectedBorderDetectorYUV(images_val[i], numLabel_val, pathText_val)


def main():
    sms = "MODOS ROBOT \n\
        0. Esperando. \n\
        1. Capturar objeto \n\
        2. Aprender objeto \n\
        3. Reconocer objetos."
    while True:
        print(sms)
        selectMode = input("Ingrese el modo del robot: ")
        mode, state, servos = handlerJson(urls['status'], selectMode)


        if selectMode == '0':
            pass
        elif selectMode == '1':
            name_image = input("Ingrese el nombre de la pieza: ")
            if state:
                cameraIP(urls['resLo'], paths['autoData'], name_image, 10, 900)
        elif selectMode == '2':
            if not comparateLenFolder(paths['images'], paths['autoData']):
                pdi()
        elif selectMode == '3':
            kingDetector(urls['resHi'], modelPath)
        else:
            print("El programa terminó")
            break

if __name__ == "__main__":
    main()
