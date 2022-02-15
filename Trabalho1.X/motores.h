#ifndef MOTORES_H
#define	MOTORES_H

#define AIR_CONDITIONER PORTDbits.RD0
#define fly_MA PORTDbits.RD1
#define ref_MF PORTDbits.RD2
#define ref_MA PORTDbits.RD3


void antihorario(); // motor rot rotaciona anti-horario
void horario();     // motor rotaciona horario

#endif	/* MOTORES_H */

