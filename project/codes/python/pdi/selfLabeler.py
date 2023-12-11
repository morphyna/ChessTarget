import os
import cv2
import numpy as np
import matplotlib.pyplot as plt
import skimage.morphology as morph
import shutil

def getImages(path_images):
    try:
        #Obtener lista de nombre de imagenes en la ruta 
        image_files = [f for f in os.listdir(path_images) if f.endswith(('.jpg', '.jpeg', '.png'))]
        #color de la pieza 
        name_images = [ os.path.splitext(i)[0] for i in image_files]
        #carga la lista de imagenes
        images =  [cv2.imread(os.path.join(path_images,i), cv2.IMREAD_COLOR) for i in image_files ]

        return images, name_images
             
    except Exception as e:
        print(f"Error: {e}")

def labelName(name_images):
    names = name_images.split('_')
    piece_mapping = {
        "black": {"pawn": 0, "rook": 2, "knight": 4, "bishop": 6, "queen": 8, "king": 10},
        "white": {"pawn": 1, "rook": 3, "knight": 5, "bishop": 7, "queen": 9, "king": 11}
    }
    return piece_mapping.get(names[0], {}).get(names[1], 99)

        
def connectedBorderDetectorYUV(imagen, numLabel, pathText):
    img = cv2.cvtColor(imagen, cv2.COLOR_BGR2RGB)
    yuv = cv2.cvtColor(img, cv2.COLOR_RGB2YUV)
    y_channel, u_channel, v_channel = cv2.split(yuv)

    if (numLabel%2 == 1):
        # Umbralizar en el canal U
        _, th1 = cv2.threshold(u_channel, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
    elif(numLabel%2 == 0):
        # Umbralizar en el canal Y
        _, th1 = cv2.threshold(y_channel, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
    # Invertir la imagen binaria
    inv = 255 - th1

    # Dilatar la imagen para eliminar falsos positivos
    elem1 = morph.disk(3)
    inv = morph.binary_dilation(inv, elem1)

    # Convertir la máscara para operarla más adelante
    imagen_binaria = inv.astype(np.uint8) * 255
        
    kernel = np.ones((9, 9), np.uint8)
    imagen_binaria = cv2.erode(imagen_binaria, kernel, iterations=1)

    # Aplicar la función connectedComponentsWithStats
    num_labels, labels, stats, centroids = cv2.connectedComponentsWithStats(imagen_binaria, connectivity=8)

    # Crear una imagen en color para dibujar los rectángulos
    imagen_etiquetada = img.copy()

    # Iterar sobre las regiones etiquetadas (excluyendo el fondo, etiqueta 0)
    for i in range(1, num_labels):
        x, y, w, h, area = stats[i]
        cv2.rectangle(imagen_etiquetada, (x, y), (x + w, y + h), (0, 255, 0), 2)
        cv2.putText(imagen_etiquetada, str(i), (x, y - 5), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)
    
    textData = f"{numLabel} {x} {y} {x+w} {y+h}"
    with open(pathText, 'a') as txt_file:
        txt_file.write(textData)

    """
    plt.figure(figsize=(12, 4))

    plt.subplot(1, 3, 1)
    plt.imshow(img)
    plt.title('Original')
    plt.axis('off')

    plt.subplot(1, 3, 2)
    plt.imshow(imagen_binaria, cmap='gray')
    plt.title('Binaria en Canal U')
    plt.axis('off')

    plt.subplot(1, 3, 3)
    plt.imshow(imagen_etiquetada)
    plt.title('Etiquetada')
    plt.axis('off')

    plt.show()
    """
    



def copyImage(sourcePath, destinationPath):
    try:
        shutil.copy(sourcePath, destinationPath)
        print(f"Imagen copiada exitosamente de {sourcePath} a {destinationPath}")
    except Exception as e:
        print(f"Error al copiar la imagen: {str(e)}")


def comparateLenFolder(folder_path1, folder_path2):
    try: 
        files_folder1 = [f for f in os.listdir(folder_path1) if os.path.isfile(os.path.join(folder_path1, f))]
        files_folder2 = [f for f in os.listdir(folder_path2) if os.path.isfile(os.path.join(folder_path2, f))]
        return files_folder1 == files_folder2 
    
    except Exception as e:
        print(f"Error al copiar la imagen: {str(e)}")
        return False