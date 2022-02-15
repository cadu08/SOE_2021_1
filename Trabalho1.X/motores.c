#include <pic18f4520.h>

#include "motores.h"

void antihorario(){
    AIR_CONDITIONER = 0;
}

void horario(){
    AIR_CONDITIONER = 1;
}