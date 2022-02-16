#ifndef TYPES_H
#define	TYPES_H

#include <xc.h>
#include "user_config.h"

#define HW_STACK 32

#define TRUE 1
#define FALSE 0

#define MIN_PRIOR 1
#define DEFAULT_PRIOR 3
#define MAX_PRIOR 5


#define RR_SCHEDULER 1      // TEMPO VIRTUAL
#define PRIORITY_SCHEDULER 2   // TEMPO VIRTUAL
#define RM_SCHEDULER 3      // TEMPO REAL
#define EDF_SCHEDULER 4     // TEMPO REAL

// unsigned: inteiro sem sinal

typedef unsigned u_int;
typedef void (*task_ptr) (void);
typedef unsigned byte;
typedef unsigned char bool;
typedef enum {READY, RUNNING, WAITING, WAITING_SEM} state;

typedef struct context {
    byte STATUS_reg;
    byte WORK_reg;
    byte BSR_reg;
    __uint24 STACK_regs[HW_STACK];
    u_int stack_size;
} context_t;

typedef struct tcb {
    u_int task_id;
    u_int task_priority;
    state task_state;
    context_t task_context;
    task_ptr task_func;
    u_int task_delay_time;
} tcb_t;

typedef struct r_queue {
    tcb_t tasks[MAX_TASKS+1]; // Tarefas de usuário mais tarefa idle
    u_int running_task;
    u_int fila_aptos_size;
} faptos_t;

#endif	/* TYPES_H */

