# Chess Target

## Introducción

El procesamiento de fichas de ajedrez con Python implica el uso de herramientas y técnicas de visión por computadora y aprendizaje profundo para analizar y comprender imágenes de fichas de ajedrez. En este proyecto, se emplean varias tecnologías y componentes, incluyendo:

- **ESP32-CAM en un Brazo Robótico:** La ESP32-CAM, una cámara con capacidad de conexión Wi-Fi basada en el chip ESP32, se utiliza para capturar imágenes de las fichas de ajedrez. El brazo robótico, impreso en 3D, proporciona el movimiento necesario para posicionar la cámara en diferentes ubicaciones y ángulos.

- **YoloV5 para Detección de Objetos:** Se utiliza YoloV5, un modelo de detección de objetos basado en la arquitectura YOLO (You Only Look Once), para entrenar una red neuronal que puede identificar y ubicar las fichas de ajedrez en las imágenes capturadas.

- **Control del Brazo con Arduino:** Arduino se utiliza para controlar el brazo robótico y coordinar la toma de fotos en diferentes posiciones. La integración entre Arduino y la ESP32-CAM permite la sincronización de la captura de imágenes con el movimiento del brazo.

- **Procesamiento de Imágenes con Python:** Se utiliza Python para procesar las imágenes capturadas. En el código, se aplican técnicas de visión por computadora utilizando bibliotecas como OpenCV y scikit-image. Operaciones como conversión de espacio de color, umbralización, dilatación y detección de contornos se realizan para identificar y segmentar las fichas en las imágenes.

## Resumen

El proyecto comienza con la construcción de un brazo robótico, que cuenta con 4 grados de libertad utilizando servomotores MG90 y SG90 para controlar el movimiento de la cámara en diferentes direcciones. Arduino Nano se encarga de controlar los servomotores, y se ha desarrollado una tarjeta con convertidores buck para alimentar todo el sistema.

El código se divide en varias partes. Se inicia con el controlador de la ESP32-CAM, que funciona como servidor, permitiendo la comunicación con un ordenador y Arduino a través de Wi-Fi y comunicación serial, respectivamente. Arduino controla el movimiento del brazo robótico en diferentes modos: espera, captura de imagen y reconocimiento de piezas.

En el lado del ordenador, se han desarrollado programas en Python. Uno para recuperar los fotogramas de la ESP32-CAM, otro para actualizar las variables en el servidor, y un tercero para procesar las imágenes capturadas, generando máscaras y rectángulos alrededor de las piezas detectadas. Además, se incluye un programa en Python que utiliza YoloV5 para el entrenamiento de la red neuronal.

## Librerias


- **OpenCV (Open Source Computer Vision):** OpenCV es una biblioteca de visión por computadora que proporciona herramientas para el procesamiento de imágenes y visión artificial. En este proyecto, se utiliza para realizar operaciones como conversión de espacio de color, umbralización, dilatación y detección de contornos en las imágenes capturadas.

- **WiFi.h y WebServer (Arduino):** Estas bibliotecas son esenciales para la implementación de la conexión Wi-Fi y la creación de un servidor en la ESP32-CAM. Permiten la comunicación inalámbrica entre la cámara y otros dispositivos, como el ordenador y el Arduino, facilitando la transferencia de datos.

- **ArduinoJson (Arduino):** ArduinoJson es una biblioteca para el manejo de datos en formato JSON en plataformas Arduino. En este proyecto, se utiliza para estructurar y facilitar el intercambio de datos entre la ESP32-CAM y el ordenador a través de la conexión Wi-Fi.

- **scikit-image, Matplotlib, y NumPy:** Estas bibliotecas de Python se utilizan en el procesamiento de imágenes. Scikit-image proporciona algoritmos avanzados para el procesamiento de imágenes, Matplotlib se utiliza para visualizar los resultados, y NumPy facilita la manipulación de matrices para operaciones eficientes.

- **Flask:** Flask es un marco web de Python utilizado para crear aplicaciones web. En este proyecto, Flask se utilizó para desarrollar interfaces web o servicios adicionales que complementan la funcionalidad principal.

- **YoloV5:** YoloV5 es un modelo de detección de objetos basado en la arquitectura YOLO. En este proyecto, se utiliza para entrenar una red neuronal capaz de identificar y ubicar las fichas de ajedrez en las imágenes capturadas por la ESP32-CAM.

- **Servo.h (Arduino):** La biblioteca Servo.h de Arduino se utiliza para controlar los servomotores que manejan los movimientos del brazo robótico. Permite definir la posición de los servomotores y realizar movimientos precisos.

- **FreeRTOS (Real-Time Operating System):** FreeRTOS se utiliza para gestionar tareas en tiempo real en sistemas embebidos. Puede haberse implementado en el proyecto para mejorar la sincronización y la ejecución de tareas concurrentes.

Estas librerías desempeñan roles específicos y son fundamentales para lograr la integración exitosa de la ESP32-CAM, el brazo robótico y el procesamiento de imágenes en el proyecto Chess Target.

## Archivos

En la carpeta "codes," se encuentran los códigos relacionados con los movimientos del brazo, reconocimiento de imágenes y entrenamiento de la red neuronal. Las subcarpetas "arduino" y "python" contienen códigos para el control del brazo y reconocimiento de piezas, respectivamente.

- **En la carpeta 'arduino':**
  - **'esp32cam_controller':** Código para la ESP32-CAM, gestionando la conexión de la cámara y la captura de imágenes.
  - **'motor_controller':** Códigos para controlar los movimientos del brazo robótico.

- **En la carpeta 'python':**
  - **'image_processing':** Programa para procesar imágenes capturadas, generando máscaras y rectángulos alrededor de las piezas detectadas.
  - **'yolov5_training':** Programa para el entrenamiento de la red neuronal YoloV5.

Con estos archivos, se logra el control de una cámara para capturar imágenes que son procesadas para reconocer piezas de ajedrez específicas.
