/*
 * Sistema Operacional Embarcado - Projeto de 2021.1
 */

#include <xc.h>
#include "time.h"
#include "kernel.h"
#include "user_tasks.h"
#include "motores.h"
#include "thermostat.h"

int main(void) {
    
    OS_config();
   
    // Tarefas do Usuário    
    if(EXAMPLE == 1)
    {
      OS_create_task(2, thermostat_sensing_1);
      OS_create_task(3, ac_controller_1);
    }else if(EXAMPLE == 2)
    {
      OS_create_task(2, thermostat_sensing_2);
      OS_create_task(3, ac_controller_2); 
    }
    
    // Coloca o kernel em execução
    OS_start();
    
    while(1){
    }
    
    return 0;
}
