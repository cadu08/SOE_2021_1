#include "user_tasks.h"
#include "semaphore.h"

int room_temperature;

// O mecanismo para acesso a t_ambiente baseia-se no pipe implementado em aula
// t_ambiente está funcionando como se fosse um pipe de tamanho 1

void thermostat_sensing_2()
{   
   while(1)
   {
      //Decrementa o semáforo binário de escrita
      //Apenas será possível escrever novamente quando este semáforo for incrementado (for dado um post)
      //Será dado um post neste semáforo quando a task do controlador estiver em processamento
      sem_wait(&sem_temp_w);
      
      //t_ambiente neste caso seria uma seção crítica
      room_temperature = thermostat_value();
      
      //Incrementa o semáforo binário de escrita
      //Agora a task do controlador pode acessar t_ambiente
      //A task do controlador dará um wait neste semáforo
      sem_post(&sem_temp_r);
   }
}

void ac_controller_2()
{
   while(1)
   {
      /*Se não tiver ocorrido uma atualização em t_ambiente,
        o despachante colocará esta task em WAITING         */
      sem_wait(&sem_temp_r);
      
      if(room_temperature >= (SETTED_TEMPERATURE + 2))
      {
         turn_on_ac();
      }
      
      if(room_temperature <= (SETTED_TEMPERATURE - 2))
      {
         turn_off_ac();
      }
      
      /* t_ambiente foi acessada, deve-se incrementar o semáforo
         para poder atualizar t_ambiente */ 
      sem_post(&sem_temp_w);
   }
}