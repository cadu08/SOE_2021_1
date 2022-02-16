/**
 * Sistema Operacional Embarcado - Projeto de 2021.1
 */

#include "config_hw.h"

void config_timer0()
{
   // Configura��o dos registradores respons�veis pelo timer0
   INTCONbits.PEIE      = 1;    // Habilita a interrup��o por perif�rico
   INTCONbits.TMR0IE    = 1;  // Habilita o timer0
   INTCONbits.TMR0IF    = 0;  // Seta o flag de timer0 em 0
   T0CONbits.PSA        = 0;      // Habilita o uso do preescaler
   T0CONbits.T0PS       = 0b010; // Seta o preescaler em 1:4
   T0CONbits.T0CS       = 0;     // Seta a refer�ncia do timer (clock interno)
   TMR0L                = 0;
}

void config_ad_conversor(){
    // configurando pinos para input
    TRISA = 0b00000001;
    ADCON0bits.CHS = 0b0000;    // define canal de leitura como AN0
    // definindo tens�es de refer�ncia:
    ADCON1bits.VCFG1 = 0; //VSS
    ADCON1bits.VCFG0 = 0; //VDD
    // define AN0 e AN1 como anal�gicos:
    ADCON1bits.PCFG = 0b0000;
    ADCON1 = 0x0E;
//    ADCON2 = 0x9D;
    // formato do resultado (select bit);
    ADCON2bits.ADFM = 1; // right justified;
    // tempo de aquisi��o
    ADCON2bits.ACQT = 0b111; //20 TAD
    ADCON0bits.ADON = 1;
    ADCON2bits.ADCS = 0b110;    // FOSC/64
}

void io_config(){
    // pinos s�o de sa�da:
    TRISD = 0x00;
    
    //pinos s�o de entrada:
    TRISB = 0xFF;
}
