import cv2
import urllib.request
import numpy as np
import time
import os
from datetime import datetime

def cameraIP(url, save_path, name_image, cap_interval=10, cap_duration=900):
    win_name = 'CAM'
    cv2.namedWindow(win_name, cv2.WINDOW_AUTOSIZE)

    start_time = time.time()
    end_time = start_time + (cap_duration / 1000.0)

    # Crear el directorio de guardado si no existe
    os.makedirs(save_path, exist_ok=True)

    while time.time() < end_time:
        current_time = time.time()

        if current_time - start_time >= cap_interval / 1000.0:
            img_response = urllib.request.urlopen(url)
            img_np = np.array(bytearray(img_response.read()), dtype=np.uint8)
            img = cv2.imdecode(img_np, -1)

            img = cv2.rotate(img, cv2.ROTATE_90_COUNTERCLOCKWISE)

            cv2.imshow(win_name, img)

            fecha_hora_actual = datetime.now()

            # Formatear la fecha y hora como una cadena
            formato_personalizado = "%Y-%m-%d_%H-%M-%S"
            fecha_hora_formateada = fecha_hora_actual.strftime(formato_personalizado)

            img_path = os.path.join(save_path, f"{name_image}_{fecha_hora_formateada}.jpg")

            cv2.imwrite(img_path, img)
            print(f"Foto tomada y guardada en {img_path}")

            start_time = current_time

        key = cv2.waitKey(1) & 0xFF
        if key == 27:
            break

    cv2.destroyAllWindows()





