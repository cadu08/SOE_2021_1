/**
 * Sistema Operacional Embarcado - Projeto de 2021.1
 */

#include "config_hw.h"

void config_timer0()
{
   // Configuração dos registradores responsáveis pelo timer0
   INTCONbits.PEIE      = 1;    // Habilita a interrupção por periférico
   INTCONbits.TMR0IE    = 1;  // Habilita o timer0
   INTCONbits.TMR0IF    = 0;  // Seta o flag de timer0 em 0
   T0CONbits.PSA        = 0;      // Habilita o uso do preescaler
   T0CONbits.T0PS       = 0b010; // Seta o preescaler em 1:4
   T0CONbits.T0CS       = 0;     // Seta a referência do timer (clock interno)
   TMR0L                = 0;
}

void config_ad_conversor(){
    // configurando pinos para input
    TRISA = 0b00000001;
    ADCON0bits.CHS = 0b0000;    // define canal de leitura como AN0
    // definindo tensões de referência:
    ADCON1bits.VCFG1 = 0; //VSS
    ADCON1bits.VCFG0 = 0; //VDD
    // define AN0 e AN1 como analógicos:
    ADCON1bits.PCFG = 0b0000;
    ADCON1 = 0x0E;
//    ADCON2 = 0x9D;
    // formato do resultado (select bit);
    ADCON2bits.ADFM = 1; // right justified;
    // tempo de aquisição
    ADCON2bits.ACQT = 0b111; //20 TAD
    ADCON0bits.ADON = 1;
    ADCON2bits.ADCS = 0b110;    // FOSC/64
}

void io_config(){
    // pinos são de saída:
    TRISD = 0x00;
    
    //pinos são de entrada:
    TRISB = 0xFF;
}
