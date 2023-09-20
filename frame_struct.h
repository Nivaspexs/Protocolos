// Se describe en este archivo la estructura utilizada para formar el frame (que es la trama de datos de un byte) para así poder utilizarlo como paquetes enviados
//(o recibidos) en las proximas funciones 

#ifndef FRAME_STRUCT_H
#define FRAME_STRUCT_H
//#include <wiringPi.h>


#define byte unsigned char 

struct frame{
	byte cmd;	// 1 bit (para emisión-recepción)
	byte largo;	// 3 bits
	byte datos[4];	// 4 btyes de datos (se ajusta a necesidad) (0-3 bytes)
	byte FCS;	// 6 bits
	byte frame[6]; // 48 bits

};


#endif