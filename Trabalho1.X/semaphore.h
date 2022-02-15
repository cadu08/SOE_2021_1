/* 
 * Projeto de Sistemas Operacionais Embarcados
 */

#ifndef SEMAPHORE_H
#define	SEMAPHORE_H

#include "types.h"
#include "kernel.h"

// aguarda por um tempo ou aguarda infinitamente?]
typedef struct sem_queue {
    u_int TASKS[MAX_TASKS];
    u_int queue_size;
    u_int queue_wait_pos; // posição de inserção
    u_int queue_post_pos; // posição de liberação (saída)
} sem_queue_t;
typedef struct semaphore{
    int s_count;
    sem_queue_t s_queue;
    
} semaphore_t;

void sem_init(semaphore_t* s, int val);
void sem_wait(semaphore_t* s);
bool sem_wait_time(semaphore_t* s, int time);
void sem_post(semaphore_t* s);
int sem_get_value(semaphore_t s);


#endif	/* SEMAPHORE_H */

