#include "user_tasks.h"
#include "semaphore.h"

int room_temperature;
bool bsem_room_temperature = FALSE;

// O mecanismo para acesso a t_ambiente baseia-se no pipe implementado em aula
// t_ambiente está funcionando como se fosse um pipe de tamanho 1

void thermostat_sensing_2()
{   
   while(1)
   {
      if(bsem_room_temperature == FALSE)
      {
         //t_ambiente neste caso seria uma seção crítica
         room_temperature = thermostat_value();  
         bsem_room_temperature = TRUE;
      }
   }
}

void ac_controller_2()
{
   while(1)
   {
      if(bsem_room_temperature == TRUE)
      {
         if(room_temperature >= (SETTED_TEMPERATURE + 2))
         {
            turn_on_ac();
         }
      
         if(room_temperature <= (SETTED_TEMPERATURE - 2))
         {
            turn_off_ac();
         }
         
         bsem_room_temperature = FALSE;
      }
   }
}