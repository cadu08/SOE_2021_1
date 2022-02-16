/**
 * Sistema Operacional Embarcado - Projeto de 2021.2
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