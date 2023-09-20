// En este archivo se implementarán las funciones de emisión-recepción de paquetes 
#include "frame_struct.h"
#include "funciones.h"
#include <stdio.h>

#define byte unsigned char 

/*

Función encargada de emitir los paquetes y asignarles valores

*/

frame emision(){

frame emision; // Crear el frame para enviar

printf("Ingrese el comando (Cmd):\n1. Enviar ping (bit 1)\n2. Enviar mensaje (bit 0)\n");
int opcion;
scanf("%d", &opcion);
if(opcion == 1){
	emision.cmd = 0x01;
	printf("Ha escogido enviar ping\n");
	printf("Enviando ping...\n");
	}


/* El paquete a crear tiene 42 btis, entonces se deben mandar 6 paquetes (o frames)
 1er frame:
	10000000 cmd 
	01110000 largo LSB
	00001111 dato0 (LSB)
2do frame:
	11110000 dato0(2da parte) (MSB)
	00001111 dato1 LSB
3er frame:
	11110000 dato1(2) MSB
	00001111 dato2(1) LSB
4to frame:
	11110000 dato2(2) MSB
	00001111 dato3(1) LSB
5to frame:
	11110000 dato3(2) MSB
	00001111 FCS LSB
6to frame:
	11000000 FSB(2) MSB
	

Valor de Long:
6 (6 frames)
Entonces 6 en hexa = 0x06

*/
emision.largo = 0x06;



emision.frame[0] = (emision.cmd & 0x01) | ((emision.largo & 0x07) << 1) | ((emision.datos[0] & 0x0F) << 4);
emision.frame[1] = ((emision.datos[0] & 0xF0) >> 4) | ((emision.datos[1] & 0x0F) << 4);
emision.frame[2] = ((emision.datos[1] & 0xF0) >> 4) | ((emision.datos[2] & 0x0F) << 4);
emision.frame[3] = ((emision.datos[2] & 0xF0) >> 4) | ((emision.datos[3] & 0x0F) << 4);
emision.frame[4] = ((emision.datos[3] & 0xF0) >> 4) | ((emision.FCS & 0x0F) << 4);
emision.frame[5] = (0x00 >>6) | (emision.FCS & 0xC0);


return emision;
}


/*
Función encargada de recibir frames enviados, la primera parte (hecha de forma provisional) ,
encargados de comprobar si se envió o no el ping, mi duda es cómo interpretar el cmd si es 0 o 1.

*/

bool recepcion(frame frames_recibido){

frame recepcion;
recepcion = frames_recibido;

unsigned char cmd = 0x01;
unsigned char largo = 0x06;

if(recepcion.frame[0] == cmd){
	printf("Ping recibido\n");
	return true;
}
if(recepcion.largo == largo){
	printf("El largo es compatible\n");
}

return false;

}