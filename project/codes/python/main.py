import os
from pdi.selfLabeler import * 
from detectors.kingDetect import *


def pdi():
    path_root = '/home/morphyna/Documentos/GITHUB/ChessTarget/Proyecto/autoData/'
    path_images = os.path.join(path_root, 'images/train')
    path_images_val = os.path.join(path_root, 'images/val')
    path_labels = os.path.join(path_root, 'labels/train')
    path_labels_val = os.path.join(path_root, 'labels/val')

    images, name_images = getImages(path_images)
    images_val, name_images_val = getImages(path_images_val)

    for i in range(len(images)):
        numLabel = labelName(name_images[i])
        nameText = name_images[i] + '.txt'
        pathText = os.path.join(path_labels, nameText)
        connectedBorderDetectorYUV(images[i], numLabel, pathText)
        
    
    for i in range(len(images_val)):
        numLabel_val = labelName(name_images_val[i])
        nameText_val = name_images_val[i] + '.txt'
        pathText_val = os.path.join(path_labels_val, nameText_val)
        connectedBorderDetectorYUV(images_val[i], numLabel_val, pathText_val)

def startKingDectector(res):
    modelPath = '/home/morphyna/Documentos/GITHUB/ChessTarget/Proyecto/models/best.pt'

    if res == 'lo':
        url ='http://192.168.1.5/cam-lo.jpg'
    elif res == 'hi':
        url ='http://192.168.1.5/cam-hi.jpg'
    
    kingDetector(url, modelPath)


def main():
    pdi()

if __name__ == "__main__":
    main()
