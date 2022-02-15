/* 
 * File:   display.h
 * Author: milena
 *
 * Created on 11 de Setembro de 2021, 21:15
 */

#ifndef DISPLAY_H
#define	DISPLAY_H

#include "types.h"

//#define TEMP_DEZENAS_0 PORTCbits.RC0
//#define TEMP_DEZENAS_1 PORTCbits.RC1
//#define TEMP_DEZENAS_2 PORTCbits.RC2
//#define TEMP_DEZENAS_3 PORTCbits.RC3
//
//#define TEMP_UNIDADES_0 PORTCbits.RC0
//#define TEMP_UNIDADES_1 PORTCbits.RC1
//#define TEMP_UNIDADES_2 PORTCbits.RC2
//#define TEMP_UNIDADES_3 PORTCbits.RC3

#define ROT_DEZENAS_0 PORTDbits.RD0
#define ROT_DEZENAS_1 PORTDbits.RD1
#define ROT_DEZENAS_2 PORTDbits.RD2
#define ROT_DEZENAS_3 PORTDbits.RD3

#define ROT_UNIDADES_0 PORTDbits.RD0
#define ROT_UNIDADES_1 PORTDbits.RD1
#define ROT_UNIDADES_2 PORTDbits.RD2
#define ROT_UNIDADES_3 PORTDbits.RD3

void show_rot(u_int rot);

#endif	/* DISPLAY_H */

