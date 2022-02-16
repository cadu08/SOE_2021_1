#include "user_tasks.h"
#include "semaphore.h"

int room_temperature;

// O mecanismo para acesso a t_ambiente baseia-se no pipe implementado em aula
// t_ambiente est� funcionando como se fosse um pipe de tamanho 1

void thermostat_sensing_2()
{   
   while(1)
   {
      //Decrementa o sem�foro bin�rio de escrita
      //Apenas ser� poss�vel escrever novamente quando este sem�foro for incrementado (for dado um post)
      //Ser� dado um post neste sem�foro quando a task do controlador estiver em processamento
      sem_wait(&sem_temp_w);
      
      //t_ambiente neste caso seria uma se��o cr�tica
      room_temperature = thermostat_value();
      
      //Incrementa o sem�foro bin�rio de escrita
      //Agora a task do controlador pode acessar t_ambiente
      //A task do controlador dar� um wait neste sem�foro
      sem_post(&sem_temp_r);
   }
}

void ac_controller_2()
{
   while(1)
   {
      /*Se n�o tiver ocorrido uma atualiza��o em t_ambiente,
        o despachante colocar� esta task em WAITING         */
      sem_wait(&sem_temp_r);
      
      if(room_temperature >= (SETTED_TEMPERATURE + 2))
      {
         turn_on_ac();
      }
      
      if(room_temperature <= (SETTED_TEMPERATURE - 2))
      {
         turn_off_ac();
      }
      
      /* t_ambiente foi acessada, deve-se incrementar o sem�foro
         para poder atualizar t_ambiente */ 
      sem_post(&sem_temp_w);
   }
}