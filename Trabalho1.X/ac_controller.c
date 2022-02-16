#include <pic18f4520.h>

#include "ac_controller.h"

void turn_off_ac(){
    AIR_CONDITIONER = 0;
}

void turn_on_ac(){
    AIR_CONDITIONER = 1;
}