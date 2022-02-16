#include "semaphore.h"
void sem_init(semaphore_t* s, int val){
    di();
    s->s_count = val;
    s->s_queue.queue_size = s->s_queue.queue_wait_pos = s->s_queue.queue_post_pos = 0;
    
    ei();    
}

void sem_wait(semaphore_t* s){
    di();
    
    s->s_count--;
    if(s->s_count < 0){
        // bloqueia a tarefa até que uma instância do recurso seja liberada, 
        // ou até que o tempo limite de espera seja atingido
        s->s_queue.TASKS[s->s_queue.queue_wait_pos] = READY_QUEUE.task_running;
        s->s_queue.queue_wait_pos = (s->s_queue.queue_wait_pos + 1) % MAX_TASKS;
        s->s_queue.queue_size++;
        SAVE_CONTEXT(WAITING_SEM);
        RESTORE_CONTEXT();
    }
    ei();
}

void sem_post(semaphore_t* s){
    di();
    s->s_count++;
    if(s->s_count <= 0) {
        // Desbloqueia tarefa que está bloqueada a mais tempo
        READY_QUEUE.QUEUE[s->s_queue.TASKS[s->s_queue.queue_post_pos]].task_state = READY;
        s->s_queue.queue_post_pos = (s->s_queue.queue_post_pos+1)%MAX_TASKS;
        s->s_queue.queue_size--;
    }
    ei();
}

int sem_get_value(semaphore_t s){
    return s.s_count;
}