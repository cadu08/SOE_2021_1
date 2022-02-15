/*
 * Sistema Operacional Embarcado - Projeto de 2021.1
 */


#include <xc.h>
#include "time.h"
#include "kernel.h"
#include "user_tasks.h"
#include "motores.h"
#include "conversor.h"


int main(void) {
    
    OS_config();
   
    // Tarefas do Usuário
    
    OS_create_task(1, 4, sensoreamento_termostato);
    OS_create_task(2, 4, rot_process);
    // Coloca o kernel em execução
    OS_start();
    
    while(1){
    }
    
    return 0;
}
