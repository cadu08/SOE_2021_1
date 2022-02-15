#include "display.h"

u_int tmp;
u_int dezenas = 0;
u_int unidades;

void show_rot(u_int rot){
    tmp = rot/11.367;
    u_int dezenas = 0;
    u_int unidades;
    u_int current_d;
    u_int current_u;
    
    
    while(tmp > 0){
        tmp -= 10;
        if(tmp < 0)
            dezenas++;
    }
    unidades = tmp+10;
    
    current_d = dezenas & 1;
    current_u = unidades & 1;
    if(current_d != 0)
        ROT_DEZENAS_0 = 1;
    else
        ROT_DEZENAS_0 = 0;
    if(current_u != 0)
        ROT_UNIDADES_0 = 1;
    else
        ROT_UNIDADES_0 = 0;
    
    current_d = dezenas & 2;
    current_u = unidades & 2;
    if(current_d != 0)
        ROT_DEZENAS_1 = 1;
    else
        ROT_DEZENAS_1 = 0;
    if(current_u != 0)
        ROT_UNIDADES_1 = 1;
    else
        ROT_UNIDADES_1 = 0;
    
    current_d = dezenas & 4;
    current_u = unidades & 4;
    if(current_d != 0)
        ROT_DEZENAS_2 = 1;
    else
        ROT_DEZENAS_2 = 0;
    if(current_u != 0)
        ROT_UNIDADES_2 = 1;
    else
        ROT_UNIDADES_2 = 0;
    
    current_d = dezenas & 8;
    current_u = unidades & 8;
    if(current_d != 0)
        ROT_DEZENAS_3 = 1;
    else
        ROT_DEZENAS_3 = 0;
    if(current_u != 0)
        ROT_UNIDADES_3 = 1;
    else
        ROT_UNIDADES_3 = 0;
}