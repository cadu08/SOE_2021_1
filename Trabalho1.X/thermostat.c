#include "thermostat.h"

int thermostat_value(){
    di(); //Desabilita interrupções
    
    ADCON0bits.ADON = 1;     //Liga o conversor AD
    ADCON0bits.CHS = 0b0000; //Seleciona o canal AN0
    
    // A referência de tensão será a da própria alimentação do MCU
    ADCON1bits.VCFG1 = 0; //VSS
    ADCON1bits.VCFG0 = 0; //VDD
    
    // Configura AN0 como entrada analógica
    ADCON1bits.PCFG = 0b1110;
    
    // Justifica à direita o resultado da conversão AD
    ADCON2bits.ADFM = 1;
    
    // Inicia a conversão
    ADCON0bits.GODONE = 1; 
    
    // Aguarda a finalização da conversão
    while (ADCON0bits.GODONE);

    // Salva o resultado da conversão AD
    int resultadoAD = ADRES;
    
    ei(); //Habilita interrupções
    
    int temperatura_ambiente = (150*resultadoAD)/307;
    
    return temperatura_ambiente;
}