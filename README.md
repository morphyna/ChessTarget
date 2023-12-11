# Chess Target

## Introducción

El procesamiento de fichas de ajedrez con Python involucra el uso de herramientas y técnicas de visión por computadora y aprendizaje profundo para analizar y comprender imágenes de fichas de ajedrez. En tu caso específico, se han utilizado varias tecnologías y componentes:

- ESP32-CAM en un Brazo Robótico: La ESP32-CAM es una cámara con capacidad de conexión Wi-Fi basada en el chip ESP32. Se utiliza para capturar imágenes de las fichas de ajedrez.
El brazo robótico impreso en 3D proporciona el movimiento necesario para posicionar la cámara en diferentes ubicaciones y ángulos para tomar fotos de las fichas desde diferentes perspectivas.

- YoloV5 para Detección de Objetos: YoloV5 es un modelo de detección de objetos basado en la arquitectura YOLO (You Only Look Once). Se utiliza para entrenar una red neuronal que puede identificar y ubicar las fichas de ajedrez en las imágenes capturadas.
El entrenamiento del modelo implica proporcionar un conjunto de datos anotados que contienen imágenes de fichas de ajedrez junto con sus etiquetas (ubicación y clase).

- Control del Brazo con Arduino: Arduino se utiliza para controlar el brazo robótico y coordinar la toma de fotos en diferentes posiciones. La integración entre Arduino y la ESP32-CAM permite la sincronización de la captura de imágenes con el movimiento del brazo.

- Procesamiento de Imágenes con Python: Python se utiliza para procesar las imágenes capturadas. En tu código, se aplican técnicas de visión por computadora utilizando bibliotecas como OpenCV y scikit-image.
Se realizan operaciones como conversión de espacio de color, umbralización, dilatación, y detección de contornos para identificar y segmentar las fichas en las imágenes.

## Lista de Materiales

Antes de comenzar, asegúrate de tener los siguientes materiales a tu disposición:

- Protoboard
- Cables macho-macho
- Capacitor electrolítico de 10uF
- Arduino Nano
- ATtiny88
- Resistencias
- LEDs

## Preparando Arduino nano

Para que arduino nano te permita cargar tus programas a ATtiny88 debes cargar un sketch que habilite esta opción.
Para cargar el sketch dirigete a File>Examples>11.ArduinoISP>ArduinoISP

![Ruta ubicación sketch ArduinoISP](/src/img/arduinoISP.png)

para cargar el programa siga los estos pasos:

- Configurar la placa: Dirijase a Tools>Board>Arduino AVR Boards>Arduino nano.
- Verifique el puerto: Conecte el arduino nano al computador por medio del calble USB y verifique que arduino nano aparece conectado a un puerto, por ejemplo COM3. Si no aparece conectado, seleccione el puerto en Tools>Port>COM##. En el caso que no lepermita seleccionar el puerto puede deberse a 2 factores:
    1. Conexión defectuosa: verifique que el cable este bien conectado y la integridad del cable y los puertos.
    2. Compruebe que los driver de la placa esten instalados, en el caso de nano se requiere el driver para el ch340.

- Cargue el programa pulsando el boton upload (laflecha a la derecha), al finalizar la carga solo debe quedar un led indicador encendido.
 
### Nota

El programa debe cargarse sin conectar el Capacitor de 10uF entre Reset y GND, si el capacitor esta conectado Arduino IDE podría presentar un error al cargar el sketch.

## Diagramas de Conexión

Para realizar las conexinoes debemos ubicar unos los pines que cumplen la función de comunicación SPI.

- MISO
- MOSI
- SCK
- SS
- RESET
- VCC
- GND

Las siguentes imagenes muestran donde están estos pines en Arduino nano y ATtiny88 respectivamente.
![PinOUT Arduino nano](/src/img/nano328.png)
![PinOUT Arduino nanoATtiny88](/src/img/attiny88.jpg)

### Conexión del Arduino Nano como ISP

Los piens a usar de nano serán los siguentes:

- PIN13-------SCK
- PIN12-------MISO
- PIN11-------MOSI
- PIN10-------SS
- PIN9--------LED_HB
- PIN8--------LED_ERR
- PIN7--------LED_PMODE

El pin SS se usara para resetear el ATtiny durante la carga del sketch, además se usarán los pines 9, 8 y 7 para poner indicadores LEDs.

* PIN9 Corresponde al HEARDBEAT (latidos del corazón) muestra atenuación y amplificación en la iluminación para indicar que Arduino nano esta en funcionamiento como ISP.
* PIN8 Se iluminará en caso de error.
* PIN7 Se ilumina en caso de estar activo el PMODE.

### Conexión del ATtiny88

Los pines a usar de ATtiny88:

- PIN13-------SCK
- PIN12-------MISO
- PIN11-------MOSI
- RESET-------RESET

En ATtiny88 solo usaremos 4 pines, excluyendo los indicadores, basicamente son los mismos que en nano a excepción del pin de RESET que estará conectado a SS de nano.
Para ver las conexiones de mejor manera observe el siguente diagrama:
![Diagrama de conexión Arduino nano como ISP con ATtiny88](/src/img/nano_isp_attiny88.png)

## Imágenes del Montaje

![Monteje en protoboard](/src/img/montaje.png)
El montaje en protoboard integra un dipswitch para facilitar conectar y desconectar el capacitor de 10uF.

## Cargar sketch en ATtiny88

Luego de cargar el programa ArduinoISP en el Arduino Nano y realizar las conexiones indicadas, es hora de pasar a cargar el código en el ATtiny88. Pero antes de cargar nuestro sketch, debemos verificar que se encuentre instalado el gestor de placas para ATtiny. Existen muchas opciones, pero recomiendo usar ATtinyCore, que cuenta con soporte para la gran mayoría de las placas ATtiny.

Dirigete a File>Preference>Additional boards nanager URLs y pega el siguente URL:

- http://drazzy.com/package_drazzy.com_index.json
![Librerías de ATtinyCore](/src/img/additional_URLs.png)

Luego dirigete a Tools>Board>Boards manager y escribe ATtinyCore
![Librerías de ATtinyCore](/src/img/ATtinyCore.png)

## Subir el Sketch.

Ya están todos los preparativos, solo falta que escribas tu programa para subirlo, una vez lo tengas dirigete a Tools>Board>ATtinyCore>ATtiny88(Micronucleus...)
![Selección de placa ATtinyCore](/src/img/selec_board.png)

Configura el programador como Arduino as ISP
![Selección Arduino as ISP](/src/img/conf_board.png)

Para cargar el código ve a sketch>Upload Using Programmer
![Selección Arduino as ISP](/src/img/upload.png)

## Recomendaciones

A lo largo del proceso de programación, ten en cuenta las siguientes recomendaciones:

1. Asegúrate de que todas las conexiones estén firmemente establecidas y sin cortocircuitos.
2. Verifica la polaridad correcta del capacitor electrolítico (10uF).
3. Confirma que los pines de programación del ATtiny88 estén conectados según el diagrama.
4. Usa Arduino IDE inferior a la versión 2.0

## Enlaces Útiles

Aquí tienes algunos enlaces útiles para continuar con este proyecto:

- [Descargar Arduino IDE](https://www.arduino.cc/en/software)
- [Librerías de ATtinyCore](http://drazzy.com/package_drazzy.com_index.json)
- [Proyecto en GitHub](https://github.com/morphyna/ATtiny.git)

## Conclusiones

En esta guía, has aprendido a programar un microcontrolador ATtiny88 utilizando un Arduino Nano como ISP. Este conocimiento te permitirá realizar proyectos electrónicos y de robótica de manera más versátil. Asegúrate de practicar y experimentar con diferentes programas para maximizar tu comprensión de este proceso.

Recuerda que la programación de microcontroladores es una habilidad valiosa en el campo de la electrónica y la ingeniería, y esta guía es un punto de partida para explorar aún más en este emocionante mundo. ¡Buena suerte en tus proyectos!
