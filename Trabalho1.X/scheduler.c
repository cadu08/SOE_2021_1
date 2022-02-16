/**
 * Sistema Operacional Embarcado - Projeto de 2021.1
 */

#include "scheduler.h"
#include "kernel.h"

u_int scheduler()
{
#if DEFAULT_SCHEDULER == RR_SCHEDULER
   return round_robin_scheduler();
#elif DEFAULT_SCHEDULER == PRIOR_SCHEDULER
   return PRIORITY_sched();
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

u_int PRIORITY_sched()
{
   u_int next_task = f_aptos.running_task;
   u_int max_priority = f_aptos.tasks[(next_task+1) % f_aptos.fila_aptos_size].task_priority;
   u_int initial_value_max_priority = max_priority;
   u_int initial_position_max_priority = (next_task+1) % f_aptos.fila_aptos_size;
   int i = 0;
    
   for(i = 0; i < f_aptos.fila_aptos_size; i++)
   {  
      if(i != f_aptos.running_task)
      {  
         //A prioridade é inversamente proporcional
         if(f_aptos.tasks[i].task_priority < max_priority && f_aptos.tasks[i].task_state == READY)
         {
            max_priority = f_aptos.tasks[i].task_priority;
            next_task = i;
         }
      }
   }
   
   //Se não tem uma outra tarefa em maior prioridade, continua com a que está rodando
   if(max_priority == initial_value_max_priority && f_aptos.tasks[initial_position_max_priority].task_state == READY)
   {
     max_priority = initial_value_max_priority;
     next_task = initial_position_max_priority;
   } 
   return next_task;
}