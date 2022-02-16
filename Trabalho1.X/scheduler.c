/**
 * Sistema Operacional Embarcado - Projeto de 2021.1
 */

#include "scheduler.h"
#include "kernel.h"

u_int prox_tarefa;
u_int possivel;

u_int scheduler()
{
#if DEFAULT_SCHEDULER == RR_SCHEDULER
   return ROUND_ROBIN_sched();
#elif DEFAULT_SCHEDULER == PRIOR_SCHEDULER
   return PRIORITY_sched();
#endif
}

u_int ROUND_ROBIN_sched()
{
   u_int task_selected = f_aptos.running_task, try = 0;
   
   do {      
      task_selected = (task_selected+1) % f_aptos.nr_of_tasks;      
      if (try == f_aptos.nr_of_tasks) {
         return IDLE_TASK;
      }
      try++;
   } while (f_aptos.QUEUE[task_selected].task_state != READY || 
            f_aptos.QUEUE[task_selected].task_func == idle);
   
   return task_selected;
}

u_int PRIORITY_sched()
{
   
}

void sort_ready_queue()
{
   prox_tarefa = f_aptos.running_task;
   u_int i, j; 
   tcb_t aux;
   
   for (i = 1; i < f_aptos.nr_of_tasks; i++) {
      for (j = 1; j < f_aptos.nr_of_tasks-1; j++) {
         if (f_aptos.QUEUE[j].task_prior < f_aptos.QUEUE[j+1].task_prior) {
            aux = f_aptos.QUEUE[j+1];
            f_aptos.QUEUE[j+1] = f_aptos.QUEUE[j];
            f_aptos.QUEUE[j] = aux;
         }
      }
   }
}
