/**
 * Sistema Operacional Embarcado - Projeto de 2021.1
 */

#ifndef CONFIG_HW_H
#define	CONFIG_HW_H

#include <xc.h>


// Configuration bits
//#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config WDT = OFF   
#pragma config MCLRE = ON   
#pragma config CPD = OFF    
#pragma config BOREN = ON   
#pragma config IESO = OFF   
#pragma config FCMEN = OFF      
#pragma config LVP = OFF        

void config_timer0();
void config_ad_converter();
void io_config();

#endif	/* CONFIG_HW_H */

