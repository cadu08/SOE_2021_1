#include "user_tasks.h"

pipe_t pipe_temperature;

void config_user_tasks()
{   
   // inicializa o pipe
   pipe_init(&pipe_temperature, 1);
   
   // Coloca tarefas como globais
   __asm("GLOBAL _sensoreamento_termostato, _ac_controller");
}

void sensoreamento_termostato() {
    int readed_temperature;
    while (1) {
       readed_temperature = thermostat_value();
       pipe_write(&pipe_temperature, readed_temperature);
    }
}

void ac_controller()
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