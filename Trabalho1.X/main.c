/*
 * Sistema Operacional Embarcado - Projeto de 2021.2
 */

#include <xc.h>
#include "time.h"
#include "kernel.h"
#include "user_tasks.h"
#include "ac_controller.h"
#include "thermostat.h"

int main(void) {
    
    config_os();
   
    // Tarefas do Usuário    
    if(EXAMPLE == 1)
    {
      //create_task(1, smoke_sensing);
      create_task(2, thermostat_sensing_1);
      create_task(2, ac_controller_1);
    }else if(EXAMPLE == 2)
    {
      //create_task(1, smoke_sensing);
      create_task(2, thermostat_sensing_2);
      create_task(2, ac_controller_2); 
    }
    
    // Coloca o kernel em execução
    start_os();
    
    while(1){
    }
    
    return 0;
}
