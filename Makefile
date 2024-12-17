# Makefile para STM8S103F3

# Compilador y Enlazador
SDCC=sdcc
SDLD=sdld

# Herramientas para configuración y carga
FLASHTOOL=stm8flash
PROGRAMMER=stlinkv2
STM8=stm8s103?3

# Objetivo: Archivo binario de salida
OBJECTS=002uart.ihx

.PHONY: all clean flash

# Crear archivo binario
all: $(OBJECTS)

# Limpiar archivos
clean:
	@echo ""
	@echo "Eliminando archivos temporales..."
	rm -f $(OBJECTS)
	@echo""

# Compilar y enlazar archivo
%.ihx: %.c
	@echo ""
	@echo "Compilando y enlazando el código..."
	$(SDCC) -lstm8 -mstm8 --out-fmt-ihx $(CFLAGS) $(LDFLAGS) $<
	@echo""

# Programar el microcontrolador
flash: $(OBJECTS)
	@echo ""
	@echo "Programando el microcontrolador..."
	$(FLASHTOOL) -c $(PROGRAMMER) -p $(STM8) -w $<
	@echo""
