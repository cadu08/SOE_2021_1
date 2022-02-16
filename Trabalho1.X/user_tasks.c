#include "user_tasks.h"

pipe_t pipe_temperature;

void config_user_tasks()
{   
   // inicializa o pipe
   create_pipe(&pipe_temperature);
  
   // Coloca tarefas como globais
   if(EXAMPLE == 1){
      __asm("GLOBAL _thermostat_sensing_1, _ac_controller_1");
   }else if(EXAMPLE ==2){
      __asm("GLOBAL _thermostat_sensing_2, _ac_controller_2");
   }
   
}

void thermostat_sensing_1() {
    int readed_temperature;
    while (1) {
       readed_temperature = thermostat_value();
       pipe_write(&pipe_temperature, readed_temperature);
    }
}

void ac_controller_1()
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

void smoke_sensing() {
    while (1) {
       if(SMOKE_SENSOR)
       {
          FIRE_LED = 1;
       }
    }
}
