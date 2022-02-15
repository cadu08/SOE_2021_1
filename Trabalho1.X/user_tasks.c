#include "user_tasks.h"

pipe_t pipe_attitude;

void config_user_tasks()
{   
   // inicializa o pipe
   pipe_init(&pipe_attitude, 1);
   
   // Coloca tarefas como globais
   __asm("GLOBAL _rot_read, _rot_process");
}

TASK rot_read() {
    u_int valor_rot_lido;
    while (1) {
        valor_rot_lido = rot_ad_read();
        pipe_write(&pipe_attitude, valor_rot_lido);
    }
}

TASK rot_process() {
    int room_temperature;
    while (1) {
        pipe_read(&pipe_attitude, &room_temperature);
     
        if(room_temperature < (SETTED_TEMPERATURE - 2)){
            antihorario();
        }
        else if(room_temperature > (SETTED_TEMPERATURE + 2)){
            horario();
        }
    }   
}