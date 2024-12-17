# STM8S103F3P6_UART
Código Bare Metal para STM8S103F3P6 que inicializa y usa la UART para enviar texto a la PC.
# STM8S103F3P6 Bare Metal UART Communication

Este proyecto proporciona un ejemplo de comunicación UART "Bare Metal" para el microcontrolador STM8S103F3P6. El código está basado en los conceptos presentados en el excelente artículo de [lujji.github.io](https://lujji.github.io/blog/bare-metal-programming-stm8/).

## Descripción

Este programa demuestra cómo inicializar y utilizar la UART del STM8S103F3P6 para enviar datos de texto a una computadora. Se implementa un enfoque "Bare Metal", es decir, se accede directamente a los registros del hardware sin depender en gran medida de bibliotecas de abstracción de hardware (HAL) o bibliotecas periféricas estándar (SPL). Esto proporciona un mayor control y comprensión del funcionamiento del microcontrolador.

## Características

*   **Programación Bare Metal:** Acceso directo a los registros del hardware para un mayor control y eficiencia.
*   **Comunicación UART:** Configuración y uso de la UART1 para la transmisión de datos.
*   **Código optimizado:** Se busca la claridad y la eficiencia en el código.
*   **Fácil de entender:** Comentarios detallados para explicar el funcionamiento del código.

## Hardware Requerido

*   Placa de desarrollo con STM8S103F3P6.
*   Programador ST-Link V2.
*   Convertidor USB a TTL (CP2102).
*   Cables de conexión.

## Software Requerido

*   Linux (probado en distribuciones como Ubuntu).
*   SDCC (Small Device C Compiler) para STM8.
*   `st-flash` (o similar) para programar el microcontrolador.
*   `screen` (u otro programa de terminal serial como `minicom` o `PuTTY`).

## Conexiones

Las conexiones entre los dispositivos son las siguientes:

*   **STM8S103F3P6 <-> ST-Link V2:** Conectar los pines SWDIO, SWCLK, GND y VCC.
*   **STM8S103F3P6 <-> CP2102:**
    *   STM8S103F3P6 (PD5/TX) -> CP2102 (RXD)
    *   STM8S103F3P6 (PD6/RX) -> CP2102 (TXD)
    *   STM8S103F3P6 (GND) -> CP2102 (GND)
    *   **IMPORTANTE:** Alimentar el STM8S103F3P6 con **3.3V** desde la salida de 3.3V del CP2102. **No usar 5V**, ya que esto podría dañar el microcontrolador.
*   **CP2102 <-> PC:** Conectar el CP2102 a un puerto USB de la computadora.

## Compilación y Programación

1.  **Instalar SDCC:** Sigue las instrucciones de instalación para tu distribución de Linux.
2.  **Compilar el código:**
    ```bash
    sdcc -mstm8 --std-c99 main.c
    ```
    Esto generará un archivo `main.ihx` (formato Intel HEX).

3.  **Convertir a formato binario:**
    ```bash
    packihx main.ihx > main.hex
    sdobjcopy -O binary main.hex main.bin
    ```

4.  **Programar el STM8S103F3P6:**
    ```bash
    st-flash write main.bin 0x8000
    ```
    (Ajusta la dirección `0x8000` si es necesario según tu configuración).

    O utiliza el archivo Makefile probado en linux

## Visualización de la Salida Serial

1.  **Identificar el puerto serial:** Ejecuta `ls /dev/tty*` para encontrar el dispositivo correspondiente al CP2102 (probablemente `/dev/ttyUSB0` o `/dev/ttyACM0`).

2.  **Abrir la terminal serial con `screen`:**
    ```bash
    screen /dev/ttyUSB0 9600
    ```
    Reemplaza `/dev/ttyUSB0` con el puerto correcto y `9600` con la velocidad de baudios configurada en el código (si la modificaste).

3.  **Salir de `screen`:** Presiona `Ctrl+a` y luego `k`, y confirma con `y`.

## Contribuciones

¡Las contribuciones son bienvenidas! Si encuentras errores, tienes sugerencias de mejora o quieres añadir nuevas funcionalidades, por favor, abre un *issue* o envía un *pull request*.

## Descarga

Puedes descargar el código fuente desde este repositorio.

## Licencia

[Añadir licencia (ej. MIT, GPL)]
