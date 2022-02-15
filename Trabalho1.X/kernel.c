#include "kernel.h"
#include "user_tasks.h"
#include "config_hw.h"
#include "user_config.h"

// Variáveis Globais
r_queue_t READY_QUEUE;
u_int rr_quantum = RR_QUANTUM;

// Tarefa idle
TASK idle(){
    TRISDbits.RD3 = 0;
    while (1){
        LATDbits.LATD3 = ~PORTDbits.RD3;
        NOP();
    }
}

void OS_config(){
    // Configura alguns registradores e variáveis do SO
    READY_QUEUE.nr_of_tasks = 0;
    READY_QUEUE.task_running = 0;
    
    // cria a tarefa idle
    OS_create_task(1, MIN_PRIOR, idle);
    __asm("GLOBAL _idle");
    
    // chama rotina que configura tarefas de usuário
    config_user_tasks();
}

void OS_start(){
    config_timer0();
    // Inicializa motores
#if MOTORES
    config_flywheel();   
#endif
    // inicializa conversor AD
#if CONVERSOR_AD
    config_ad_conversor();
#endif
    
    ei();
    T0CONbits.TMR0ON;
    
}

// Chamadas de Sistema
void OS_delay(u_int time){
    // Faz com que a tarefa aguarde por um tempo (sleep)
    di();
    //READY_QUEUE.QUEUE[READY_QUEUE.task_running].task_delay_time = time;
    SAVE_CONTEXT(WAITING);
    READY_QUEUE.QUEUE[READY_QUEUE.task_running].task_delay_time = time;
    RESTORE_CONTEXT();
    
    ei();
}

void OS_create_task(u_int id, u_int prior, task_ptr func){
    // Cria uma nova tarefa e a insere na fila de aptos
    tcb_t new_task;
    
    new_task.task_id = id;
    new_task.task_prior = prior;
    new_task.task_func = func;
    new_task.task_state = READY;
    new_task.task_context.stack_size = 0;
    new_task.task_delay_time = 0;
    
    
    // Inclui nova tarefa na fila de aptos
    READY_QUEUE.QUEUE[READY_QUEUE.nr_of_tasks] = new_task;
    READY_QUEUE.nr_of_tasks++;
}

u_int get_task_id(){
    // Retorna o identificados da tarefa que está em execução
    return READY_QUEUE.QUEUE[READY_QUEUE.task_running].task_id;
}

u_int delay_release(){
    u_int i, task_released = FALSE;
    for(i = 0; i < READY_QUEUE.nr_of_tasks; i++){
        if(READY_QUEUE.QUEUE[i].task_state == WAITING) {
            READY_QUEUE.QUEUE[i].task_delay_time--;
            if(READY_QUEUE.QUEUE[i].task_delay_time == 0) {
                READY_QUEUE.QUEUE[i].task_state = READY;
                task_released = TRUE;
            }
        }
    }
    return task_released;
}

void __interrupt() ISR_timer()
{
    // rotinas que são executadas para o escalonador RR
    TMR0L = 0;
    INTCONbits.TMR0IF = 0;
    rr_quantum--;
    // Verifica se existem tarefas que estão aguardando estouro de delay
    if (delay_release() && DEFAULT_SCHEDULER == PRIOR_SCHEDULER) {
        SAVE_CONTEXT(READY);
        RESTORE_CONTEXT();
    }
    if (rr_quantum == 0 && DEFAULT_SCHEDULER == PRIOR_SCHEDULER) {
        rr_quantum = RR_QUANTUM;
        SAVE_CONTEXT(READY);
        RESTORE_CONTEXT();
    }
    #if DEFAULT_SCHEDULER == RR_SCHEDULER
        // Rotinas são executadas para escalonar RR
        if(rr_quantum == 0){
            rr_quantum = RR_QUANTUM;
            SAVE_CONTEXT(READY);
            RESTORE_CONTEXT();
        }
    #else
//    rr_quantum = RR_QUANTUM;
//    SAVE_CONTEXT(READY);
//    RESTORE_CONTEXT();
    #endif
}

void RESTORE_CONTEXT(){
    do{ 
        di(); 
        READY_QUEUE.task_running = scheduler(); 
        u_int task_running = READY_QUEUE.task_running; 
        READY_QUEUE.QUEUE[task_running].task_state = RUNNING; 
        STKPTR = 0; 
        if(READY_QUEUE.QUEUE[task_running].task_context.stack_size > 0) { 
            BSR = READY_QUEUE.QUEUE[task_running].task_context.BSR_reg; 
            STATUS = READY_QUEUE.QUEUE[task_running].task_context.STATUS_reg; 
            WREG = READY_QUEUE.QUEUE[task_running].task_context.WORK_reg; 
            u_int stack_size = READY_QUEUE.QUEUE[task_running].task_context.stack_size; 
            while (stack_size) { 
                asm("PUSH"); 
                TOS = READY_QUEUE.QUEUE[task_running].task_context.STACK_regs[stack_size-1]; 
                stack_size--; 
            } 
        } 
        else { 
            asm("PUSH"); 
            TOS = READY_QUEUE.QUEUE[task_running].task_func; 
        } 
    ei(); 
    } while(0); 
}