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
   u_int task_selected = READY_QUEUE.task_running, try = 0;
   
   do {      
      task_selected = (task_selected+1) % READY_QUEUE.nr_of_tasks;      
      if (try == READY_QUEUE.nr_of_tasks) {
         return IDLE_TASK;
      }
      try++;
   } while (READY_QUEUE.QUEUE[task_selected].task_state != READY || 
            READY_QUEUE.QUEUE[task_selected].task_func == idle);
   
   return task_selected;
}

u_int PRIORITY_sched()
{
    for(u_int tentativa = 1; tentativa < READY_QUEUE.nr_of_tasks; tentativa++){
        possivel = (possivel+1)%(READY_QUEUE.nr_of_tasks);
        if (READY_QUEUE.QUEUE[possivel].task_state == READY){
            if (READY_QUEUE.QUEUE[possivel].task_prior > READY_QUEUE.QUEUE[prox_tarefa].task_prior)
                prox_tarefa = possivel;
            else if (READY_QUEUE.QUEUE[possivel].task_prior == READY_QUEUE.QUEUE[prox_tarefa].task_prior && prox_tarefa == READY_QUEUE.task_running)
                prox_tarefa = possivel;
//            else if(READY_QUEUE.QUEUE[READY_QUEUE.task_running].task_state!=READY)
//                prox_tarefa = possivel;
//            else if ((tentativa == READY_QUEUE.nr_of_tasks-1) && READY_QUEUE.QUEUE[possivel].task_state == READY)
//                prox_tarefa = possivel;
        }
        
    }
//    if(READY_QUEUE.QUEUE[prox_tarefa].task_state == READY) 
        return prox_tarefa;
//    else
//        return possivel;
}

void sort_ready_queue()
{
   prox_tarefa = READY_QUEUE.task_running;
   u_int i, j; 
   tcb_t aux;
   
   for (i = 1; i < READY_QUEUE.nr_of_tasks; i++) {
      for (j = 1; j < READY_QUEUE.nr_of_tasks-1; j++) {
         if (READY_QUEUE.QUEUE[j].task_prior < READY_QUEUE.QUEUE[j+1].task_prior) {
            aux = READY_QUEUE.QUEUE[j+1];
            READY_QUEUE.QUEUE[j+1] = READY_QUEUE.QUEUE[j];
            READY_QUEUE.QUEUE[j] = aux;
         }
      }
   }
}
