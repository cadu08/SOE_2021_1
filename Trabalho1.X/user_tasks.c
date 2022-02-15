#include "user_tasks.h"

pipe_t pipe_temperature;

void config_user_tasks()
{   
   // inicializa o pipe
   pipe_init(&pipe_temperature, 1);
   
   // Coloca tarefas como globais
   __asm("GLOBAL _sensoreamento_termostato, _rot_process");
}

TASK sensoreamento_termostato() {
    u_int valor_rot_lido;
    while (1) {
       valor_rot_lido = rot_ad_read();
       pipe_write(&pipe_temperature, valor_rot_lido);
    }
}

TASK rot_process()
{
   int room_temperature;
   while (1) {
      pipe_read(&pipe_temperature, &room_temperature);
     
      if(room_temperature < (SETTED_TEMPERATURE - 2)){
         turn_off_ac();
      }else if(room_temperature > (SETTED_TEMPERATURE + 2)){
         turn_on_ac();
      }
    }   
}