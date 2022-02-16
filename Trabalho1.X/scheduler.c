/**
 * Sistema Operacional Embarcado - Projeto de 2021.1
 */

#include "scheduler.h"
#include "kernel.h"

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
   u_int next_task = f_aptos.running_task, try = 0;
   
   do {      
      next_task = (next_task+1) % f_aptos.nr_of_tasks;      
      if (try == f_aptos.nr_of_tasks) {
         return IDLE_TASK;
      }
      try++;
   } while (f_aptos.QUEUE[next_task].task_state != READY || 
            f_aptos.QUEUE[next_task].task_func == idle);
   
   return next_task;
}

u_int PRIORITY_sched()
{
   
}