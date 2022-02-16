/* 
 * Projeto de Sistemas Operacionais Embarcados
 */

#ifndef KERNEL_H
#define	KERNEL_H

#include "types.h"
#include "scheduler.h"

// Variáveis Globais
extern faptos_t f_aptos; 
int index;

// Tarefa idle
void idle();

// Controle de Interrupções
void __interrupt() ISR_timer();
 
// Chamadas de sistema

void OS_config();
void OS_start();
void OS_delay(u_int time);
void OS_create_task(u_int prior, task_ptr func);
u_int get_task_id();

// rotinas auxiliares
u_int delay_release();

// Despachante

#define SAVE_CONTEXT(state)\
do{\
    di();\
    if(f_aptos.tasks[f_aptos.running_task].task_context.stack_size > 0){\
        index=0;\
        f_aptos.tasks[f_aptos.running_task].task_state = state;\
        f_aptos.tasks[f_aptos.running_task].task_context.WORK_reg = WREG;\
        f_aptos.tasks[f_aptos.running_task].task_context.BSR_reg = BSR;\
        f_aptos.tasks[f_aptos.running_task].task_context.STATUS_reg = STATUS;\
        f_aptos.tasks[f_aptos.running_task].task_context.stack_size = 0;\
        do{\
            f_aptos.tasks[f_aptos.running_task].task_context.STACK_regs[index] = TOS;\
            index++;\
            __asm("POP");\
        } while(STKPTR);\
    }\
    else{\
        f_aptos.tasks[f_aptos.running_task].task_state = state;\
    }\
    ei();\
}while(0);

void RESTORE_CONTEXT();

#endif	/* KERNEL_H */

