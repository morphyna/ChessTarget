# Chess Target

## Introducción

El procesamiento de fichas de ajedrez con Python involucra el uso de herramientas y técnicas de visión por computadora y aprendizaje profundo para analizar y comprender imágenes de fichas de ajedrez. Además, el uso de Arduino se vuelve indispensable a la hora de unir la cámara con los movimientos del brazo robótico, para este caso, se han utilizado varias tecnologías y componentes:

- ESP32-CAM en un Brazo Robótico: La ESP32-CAM es una cámara con capacidad de conexión Wi-Fi basada en el chip ESP32. Se utiliza para capturar imágenes de las fichas de ajedrez.
El brazo robótico impreso en 3D proporciona el movimiento necesario para posicionar la cámara en diferentes ubicaciones y ángulos para tomar fotos de las fichas desde diferentes perspectivas.

- YoloV5 para Detección de Objetos: YoloV5 es un modelo de detección de objetos basado en la arquitectura YOLO (You Only Look Once). Se utiliza para entrenar una red neuronal que puede identificar y ubicar las fichas de ajedrez en las imágenes capturadas.
El entrenamiento del modelo implica proporcionar un conjunto de datos anotados que contienen imágenes de fichas de ajedrez junto con sus etiquetas (ubicación y clase).

- Control del Brazo con Arduino: Arduino se utiliza para controlar el brazo robótico y coordinar la toma de fotos en diferentes posiciones. La integración entre Arduino y la ESP32-CAM permite la sincronización de la captura de imágenes con el movimiento del brazo.

- Procesamiento de Imágenes con Python: Python se utiliza para procesar las imágenes capturadas. En tu código, se aplican técnicas de visión por computadora utilizando bibliotecas como OpenCV y scikit-image.
Se realizan operaciones como conversión de espacio de color, umbralización, dilatación, y detección de contornos para identificar y segmentar las fichas en las imágenes.

## Procedimiento
Primero se contruyó un brazo robótico, para lograr esto se partió de un diseño en 3D y se modificó para adaptarle una extensión que soportara la esp32cam, este brazo robótico cuenta con 4 grados de libertad, en hombro y codo se ubicaron servomotores MG90, lo que permite la elevación de la cámara. Para los movimientos de rotación de la cámara, se usaron 2 servomotores SG90 que permiten mover la cámara de derecha a izquierda y de arriba a abajo, cubriendo así un amplio rango de alcance. Para controlar los servomotores, se optó por un arduino nano utilizando los pines 5 y 6 para el hombro y el codo, y 2 y 3 para el cuello y la vértebra. Luego, para alimentar el sistema se contruyó una tarjeta con 4 convertidores buck, ésta tarjeta recibe 12V provenientes de un par de baterías 18650 y las salidas del convertidor proporcionan 4 conexiones a 5V para alimentar la esp32cam, el arduino nano y los 4 servomotores, para controlar la carga y descarga de la batería, se usaron módulos de carga y descarga tipo BMS permitiendo así proteger las baterías.

El primer código en desarrollarse fue el controlador de la esp32cam ya que es el eje principal del proyecto, su función es conectar adecuadamente los pines de la cámara, habilitar el pin del flash, conectarse vía Wi-Fi a la red y funcionar como servidor para el intercambio de datos entre un computador, el arduino nano y las funcionalidades de la esp32cam. El intercambio de información entre el esp32cam y el computador se hace por medio de la dirección IP a la que se conecta el microcontrolador, el tráfico de la información es en formato json, ahora, entre esp32cam y arduino nano, se hace por medio de comunicación serial, el tipo de datos que se comparten son enteros

## Archivos
En la carpeta llamada 'codes', se encuentran los códigos correspondientes a todo lo que tiene que ver con los movimientos del brazo, reconocimiento de imágenes y entrenamiento de la red neuronal. Dentro de dicha carpeta, se encuentran distribuidas dos carpetas adicionales llamadas 'arduino' y 'python' que contienen todo lo relacionado con el control del brazo y recocimiento de las piezas respectivamente.

Dentro de la carpeta de 'arduino' está el código de la esp32cam, el cual se encarga básicamente de la conexión de la cámara y la captura de imágenes con la misma, este archivo está relacionado con la carpeta llamada 'cameraIP' ya que permite la conexión de la cámara con python; de igual forma, se encuentra la carpeta llamada 'motorController' que contiene los códigos respectivos para los movimentos del brazo robótico que sujeta la esp32cam, ésto con el fin de que el brazo robótico pueda desplazar la cámara y permitir la captura de fotos con ciertos ángulos específicos.

Ahora, en la carpeta llamada 'python', se tiene la otra parte del proyecto, la cual es el entrenamiento de la red neuronal y autoetiquetado, estos dos componentes son los que permiten el reconocimiento de la pieza en cuestión que se quiere detectar.
En esencia, con estos archivos mencionados anteriormente, se tiene lo necesario para controlar una cámara que permita capturar ciertas imágenes que posteriormente tendrán su validez respectiva por parte del sistema dependiendo de si el objeto detectado es parte de los que se quieren reconocer.
