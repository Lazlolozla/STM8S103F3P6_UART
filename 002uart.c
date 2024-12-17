/* Creado por [Andrés] el lun 16 de dic del 2024 a las 17:54:29 CST
 * Proyecto: 002uart utilizando programación directa sobre el hardware "bare metal"
 * Descripción: [Tu descripción]
 */

#include <stdint.h>

#define F_CPU 2000000UL

#define _SFR_(mem_addr)     (*(volatile uint8_t *)(0x5000 + (mem_addr)))

/*UART*/
#define UART_SR 			 _SFR_(0x230)
#define UART_TXE		 			7
#define UART_TC 						6
#define UART_RXNE 				5
#define UART_DR 		 _SFR_(0x231)
#define UART_BRR1 	 _SFR_(0X232)
#define UART_BRR2 	 _SFR_(0x233)
#define UART_CR1 		_SFR_(0x234)
#define UART_CR2 		 _SFR_(0x235)
#define UART_TEN 					3
#define UART_REN 					2

/*En los microcontroladores STM8, debes habilitar explícitamente el reloj para el periférico que vas a usar. En este caso, la UART1. Esto se hace configurando el bit correspondiente en el registro PCKENR1 del módulo de control de reloj (CLK).*/

/*Inclusión de la habilitación del reloj de la UART*/
#define PCKENR1         _SFR_(0x0C7) // Define PCKENR1 para mayor claridad


/*Funciones*/

/*
 * PD5 -> TX
 * PD6 -> RX
 */

/*Esta calcula cuántas instrucciones "nop" se necesitan ejecutar por cada milisegundo*/
void static delay_ms(uint16_t ms){
		uint32_t i;
	for(i=0; i<((F_CPU/18000UL)*ms); i++){/*se asume que cada instrucción "nop# tarda aproximadamente 18 ciclos de reloj en ejecutarse*/
		__asm__("nop");
	}
}

 /*para inicializar el UART hay que calcular la velocidad en baudios y escribir el valor resultante en los registros HIGH y LOW correspondientes.
2 MHz, para baud = 9600 tenemos UART_DIV = 2000000/9600 = 208 (0xD0).*/
 
void uart_init() {/*el registro BRR2 debe escribirse antes que BRR1.*/
    UART_BRR2 = 0x00;
    UART_BRR1 = 0x0D;
    UART_CR2 = (1 << UART_TEN) | (1 << UART_REN);/*encendemos el receptor y el transmisor en el registro de control 2.*/
}

/*Función escritura*/
void uart_write(uint8_t data) {/*Escribes el registro de datos y esperas a que se establezca el bit apropiado en el registro de estado*/
    UART_DR = data;
    while (!(UART_SR & (1 << UART_TC)));
}

/*Función lectura */
uint8_t uart_read() {/*Lees el registro de datos y esperas a que se establezca el bit apropiado en el registro de estado*/
    while (!(UART_SR & (1 << UART_RXNE)));
    return UART_DR;
}
/*Función de reedirección de stdout*/
int putchar(int c) {
    uart_write(c);
    return 0;
}

void uart_send_string(const char *str) {
    while (*str) {
        uart_write(*str++);
    }
}

void main(void){
// Habilitar el reloj para la UART (esencial en STM8)
    // El registro PCKENR1 se encuentra en la dirección 0x0050C7
    PCKENR1 |= (1 << 5); // Habilita el reloj para la UART1 (bit 5)

    uart_init();
    
	while(1){
	  uart_send_string("Hola desde STM8S103F3P6 (Bare Metal - Custom Functions)!\r\n");
        // Retardo (bucle simple, no preciso)
        delay_ms(250); // Ajusta este valor para el retardo deseado
  	}
}
