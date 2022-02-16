/**
 * Sistema Operacional Embarcado - Projeto de 2021.1
 */

#include "scheduler.h"
#include "kernel.h"

u_int scheduler()
{
#if DEFAULT_SCHEDULER == RR_SCHEDULER
   return round_robin_scheduler();
#elif DEFAULT_SCHEDULER == PRIORITY_SCHEDULER
   return priority_scheduler();
#endif
}

u_int round_robin_scheduler()
{
   u_int next_task = f_aptos.running_task, try = 0;
   
   do {      
      next_task = (next_task+1) % f_aptos.fila_aptos_size;      
      if (try == f_aptos.fila_aptos_size) {
         return IDLE_TASK;
      }
      try++;
   } while (f_aptos.tasks[next_task].task_state != READY || 
           f_aptos.tasks[next_task].task_func == idle);
   
   return next_task;
}

u_int priority_scheduler()
{
   u_int next_task = f_aptos.running_task, trial = 0;
   u_int major_priority_task = next_task;
   
   do {      
      next_task = (next_task+1) % f_aptos.fila_aptos_size;      
      
      if(f_aptos.tasks[next_task].task_priority < 
            f_aptos.tasks[major_priority_task].task_priority){
         major_priority_task = next_task;
      }
   } while (f_aptos.fila_aptos_size != trial || 
           f_aptos.tasks[next_task].task_func == idle);
   
   if (f_aptos.tasks[major_priority_task].task_state != READY){
      return IDLE_TASK;
   }
      
   return major_priority_task;
}