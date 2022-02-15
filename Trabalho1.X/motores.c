#include <pic18f4520.h>

#include "motores.h"

void turn_off_ac(){
    AIR_CONDITIONER = 0;
}

void turn_on_ac(){
    AIR_CONDITIONER = 1;
}