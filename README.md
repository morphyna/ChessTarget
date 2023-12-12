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
- 
# Chess Target - Procedimiento Detallado

## ESP32-CAM

### Configuración Inicial

1. **Conexión de ESP32-CAM:**
   - Conecta la ESP32-CAM al Arduino Nano siguiendo el esquema de conexiones.

   ![Esquema de Conexiones ESP32-CAM a Arduino Nano](URL_IMAGEN_ESP32CAM_1)

2. **Configuración del Entorno de Desarrollo de Arduino para ESP32-CAM:**
   - Abre el Arduino IDE y sigue los pasos mencionados anteriormente para configurar las preferencias y la tarjeta ESP32-CAM.
   - Ajusta las configuraciones en el código, como el nombre y la contraseña de la red Wi-Fi, la dirección IP y el puerto del servidor.

   ```cpp
   const char *ssid = "nombre_de_la_red";
   const char *password = "contraseña";
   IPAddress local_IP(192, 168, 1, 100);
   IPAddress gateway(192, 168, 1, 1);
   IPAddress subnet(255, 255, 255, 0);
   unsigned int localPort = 80;
   ```

   ![Configuración del Entorno de Desarrollo para ESP32-CAM](URL_IMAGEN_ESP32CAM_2)

3. **Subir el Código a ESP32-CAM:**
   - Conecta la ESP32-CAM a la computadora y selecciona el puerto COM correcto en "Herramientas" -> "Puerto".
   - Sube el código a la ESP32-CAM.

   ![Subir el Código a ESP32-CAM](URL_IMAGEN_ESP32CAM_3)

### Drivers y Configuración

1. **Instalación de Controladores USB para ESP32-CAM:**
   - Descarga e instala los controladores USB CP210x para la ESP32-CAM desde el sitio web del fabricante del chip.

   ![Instalación de Controladores USB para ESP32-CAM](URL_IMAGEN_ESP32CAM_4)

2. **Verificación del Puerto COM:**
   - Después de instalar los controladores, conecta la ESP32-CAM a la computadora y verifica que aparezca en el Administrador de Dispositivos como un puerto COM.

   ![Verificación del Puerto COM para ESP32-CAM](URL_IMAGEN_ESP32CAM_5)

## Arduino Nano

### Configuración y Control del Brazo Robótico

1. **Conexión de Servomotores al Arduino Nano:**
   - Conecta los servomotores MG90 y SG90 al Arduino Nano según el esquema de conexiones.

   ![Esquema de Conexiones de Servomotores a Arduino Nano](URL_IMAGEN_ARDUINO_NANO_1)

2. **Configuración del Entorno de Desarrollo de Arduino para el Brazo Robótico:**
   - Abre el código de control del brazo robótico en el Arduino IDE.
   - Sube el código al Arduino Nano.

   ![Configuración del Entorno de Desarrollo para el Brazo Robótico](URL_IMAGEN_ARDUINO_NANO_2)

## YoloV5

### Entrenamiento de la Red Neuronal

1. **Preparación del Dataset:**
   - Asegúrate de tener un conjunto de datos anotados con imágenes de fichas de ajedrez y sus etiquetas (ubicación y clase).
   - Estructura el dataset según los requisitos de YoloV5.

2. **Configuración del Entorno de Desarrollo para YoloV5:**
   - Clona el repositorio oficial de YoloV5 desde [GitHub](https://github.com/ultralytics/yolov5).

   ```bash
   git clone https://github.com/ultralytics/yolov5.git
   ```

   - Instala las dependencias necesarias.

   ```bash
   pip install -U -r yolov5/requirements.txt
   ```

3. **Entrenamiento de la Red:**
   - Ejecuta el script de entrenamiento, especificando la ubicación de tu conjunto de datos.

   ```bash
   python yolov5/train.py --img-size 640 --batch-size 16 --epochs 50 --data path/to/dataset.yaml --cfg yolov5/models/yolov5s.yaml --weights yolov5/models/yolov5s.pt
   ```

   - Ajusta los parámetros según tus necesidades y características del conjunto de datos.

## Servidor Flask

### Despliegue y Comunicación

1. **Configuración del Entorno de Desarrollo para Flask:**
   - Asegúrate de tener Flask instalado.

   ```bash
   pip install Flask
   ```

   - Crea una aplicación Flask y define las rutas y funciones necesarias.

   ```python
   from flask import Flask, render_template

   app = Flask(__name__)

   @app.route('/')
   def index():
       # Función para manejar la página principal
       return render_template('index.html')

   if __name__ == '__main__':
       app.run(debug=True)
   ```

2. **Comunicación entre Componentes:**
   - Implementa las funciones en Flask para recibir datos de la ESP32-CAM, controlar el brazo robótico y mostrar los resultados del procesamiento de imágenes.

   ```python
   # Implementa las funciones de comunicación aquí
   ```

   - Actualiza las rutas y funciones según las necesidades del proyecto.

Con estos pasos, has completado la configuración y conexión de los componentes principales en el proyecto Chess Target. Asegúrate de seguir cada sección detalladamente y personaliza las configuraciones según tus necesidades específicas. ¡Buena suerte con tu proyecto!
  - **'image_processing':** Programa para procesar imágenes capturadas, generando máscaras y rectángulos alrededor de las piezas detectadas.
  - **'yolov5_training':** Programa para el entrenamiento de la red neuronal YoloV5.

Con estos archivos, se logra el control de una cámara para capturar imágenes que son procesadas para reconocer piezas de ajedrez específicas.
