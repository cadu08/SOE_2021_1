/* 
 * Projeto de Sistemas Operacionais Embarcados
 */

#ifndef KERNEL_H
#define	KERNEL_H

#include "types.h"
#include "scheduler.h"

// Variáveis Globais
extern r_queue_t READY_QUEUE; 
int index;

// Tarefa idle
TASK idle();

// Controle de Interrupções
void __interrupt() ISR_timer();
 
// Chamadas de sistema

void OS_config();
void OS_start();
void OS_delay(u_int time);
void OS_create_task(u_int id, u_int prior, task_ptr func);
u_int get_task_id();

// rotinas auxiliares
u_int delay_release();

// Despachante

#define SAVE_CONTEXT(state)\
do{\
    di();\
    if(READY_QUEUE.QUEUE[READY_QUEUE.task_running].task_context.stack_size > 0){\
        index=0;\
        READY_QUEUE.QUEUE[READY_QUEUE.task_running].task_state = state;\
        READY_QUEUE.QUEUE[READY_QUEUE.task_running].task_context.WORK_reg = WREG;\
        READY_QUEUE.QUEUE[READY_QUEUE.task_running].task_context.BSR_reg = BSR;\
        READY_QUEUE.QUEUE[READY_QUEUE.task_running].task_context.STATUS_reg = STATUS;\
        READY_QUEUE.QUEUE[READY_QUEUE.task_running].task_context.stack_size = 0;\
        do{\
            READY_QUEUE.QUEUE[READY_QUEUE.task_running].task_context.STACK_regs[index] = TOS;\
            index++;\
            __asm("POP");\
        } while(STKPTR);\
    }\
    else{\
        READY_QUEUE.QUEUE[READY_QUEUE.task_running].task_state = state;\
    }\
    ei();\
}while(0);


//#define SAVE_CONTEXT(state) \
//do{ \
//    di(); \
//    u_int task_running = READY_QUEUE.task_running; \
//    if(READY_QUEUE.QUEUE[task_running].task_state == RUNNING) { \
//        READY_QUEUE.QUEUE[task_running].task_context.BSR_reg = BSR; \
//        READY_QUEUE.QUEUE[task_running].task_context.STATUS_reg = STATUS; \
//        READY_QUEUE.QUEUE[task_running].task_context.WORK_reg = WREG; \
//        u_int stack_size = 0; \
//        do { \
//            READY_QUEUE.QUEUE[task_running].task_context.STACK_regs[stack_size] = TOS; \
//            stack_size++; \
//            asm("POP"); \
//        } while (STKPTR); \
//        READY_QUEUE.QUEUE[task_running].task_context.stack_size = stack_size; \
//        READY_QUEUE.QUEUE[task_running].task_state = state; \
//    } \
//    ei(); \
//} while(0); \



//#define RESTORE_CONTEXT() \
//do {\
//    di();\
//    READY_QUEUE.task_running = scheduler();\
//    if(READY_QUEUE.QUEUE[READY_QUEUE.task_running].task_context.stack_size==0){\
//        TOS = READY_QUEUE.QUEUE[READY_QUEUE.task_running].task_func;\
//    }\
//    else{\
//        READY_QUEUE.QUEUE[READY_QUEUE.task_running].task_state = RUNNING;\
//        WREG = READY_QUEUE.QUEUE[READY_QUEUE.task_running].task_context.WORK_reg;\
//        BSR = READY_QUEUE.QUEUE[READY_QUEUE.task_running].task_context.BSR_reg;\
//        STATUS = READY_QUEUE.QUEUE[READY_QUEUE.task_running].task_context.STATUS_reg;\
//        index = READY_QUEUE.QUEUE[READY_QUEUE.task_running].task_context.stack_size-1;\
//        STKPTR = 0;\
//        while(index){\
//            __asm("PUSH");\
//            TOS = READY_QUEUE.QUEUE[READY_QUEUE.task_running].task_context.STACK_regs[index];\
//            index --;\
//        }\
//    }\
//    ei();\
//} while (0)\

void RESTORE_CONTEXT();
//#define RESTORE_CONTEXT() \
//do{ \
//    di(); \
//    READY_QUEUE.task_running = scheduler(); \
//    u_int task_running = READY_QUEUE.task_running; \
//    READY_QUEUE.QUEUE[task_running].task_state = RUNNING; \
//    STKPTR = 0; \
//    if(READY_QUEUE.QUEUE[task_running].task_context.stack_size > 0) { \
//        BSR = READY_QUEUE.QUEUE[task_running].task_context.BSR_reg; \
//        STATUS = READY_QUEUE.QUEUE[task_running].task_context.STATUS_reg; \
//        WREG = READY_QUEUE.QUEUE[task_running].task_context.WORK_reg; \
//        u_int stack_size = READY_QUEUE.QUEUE[task_running].task_context.stack_size; \
//        while (stack_size) { \
//            asm("PUSH"); \
//            TOS = READY_QUEUE.QUEUE[task_running].task_context.STACK_regs[stack_size-1]; \
//            stack_size--; \
//        } \
//    } \
//    else { \
//        asm("PUSH"); \
//        TOS = READY_QUEUE.QUEUE[task_running].task_func; \
//    } \
//    ei(); \
//} while(0);\

#endif	/* KERNEL_H */

