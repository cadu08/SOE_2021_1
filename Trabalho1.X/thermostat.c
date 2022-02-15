#include "thermostat.h"

int thermostat_value(){
    di(); //Desabilita interrup��es
    
    ADCON0bits.ADON = 1;     //Liga o conversor AD
    ADCON0bits.CHS = 0b0000; //Seleciona o canal AN0
    
    // A refer�ncia de tens�o ser� a da pr�pria alimenta��o do MCU
    ADCON1bits.VCFG1 = 0; //VSS
    ADCON1bits.VCFG0 = 0; //VDD
    
    // Configura AN0 como entrada anal�gica
    ADCON1bits.PCFG = 0b1110;
    
    // Justifica � direita o resultado da convers�o AD
    ADCON2bits.ADFM = 1;
    
    // Inicia a convers�o
    ADCON0bits.GODONE = 1; 
    
    // Aguarda a finaliza��o da convers�o
    while (ADCON0bits.GODONE);

    // Salva o resultado da convers�o AD
    int resultadoAD = ADRES;
    
    ei(); //Habilita interrup��es
    
    int temperatura_ambiente = (150*resultadoAD)/307;
    
    return temperatura_ambiente;
}