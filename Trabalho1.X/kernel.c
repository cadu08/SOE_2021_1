#include "kernel.h"
#include "user_tasks.h"
#include "config_hw.h"
#include "user_config.h"

// Variáveis Globais
faptos_t f_aptos;
u_int rr_quantum = RR_QUANTUM;

// Tarefa idle
void idle(){
    TRISDbits.RD3 = 0;
    while (1){
        LATDbits.LATD3 = ~PORTDbits.RD3;
        NOP();
    }
}

void config_os(){
    // Configura alguns registradores e variáveis do SO
    f_aptos.fila_aptos_size = 0;
    f_aptos.running_task = 0;
    
    // cria a tarefa idle
    create_task(MIN_PRIOR, idle);
    __asm("GLOBAL _idle");
    
    // chama rotina que configura tarefas de usuário
    config_user_tasks();
}

void start_os(){
    config_timer0();
    ei();
    T0CONbits.TMR0ON;
}

// Chamadas de Sistema
void OS_delay(u_int time){
    // Faz com que a tarefa aguarde por um tempo (sleep)
    di();
    //READY_QUEUE.QUEUE[READY_QUEUE.running_task].task_delay_time = time;
    SAVE_CONTEXT(WAITING);
    f_aptos.tasks[f_aptos.running_task].task_delay_time = time;
    RESTORE_CONTEXT();
    
    ei();
}

void create_task(u_int priority, task_ptr func){
    // Cria uma nova tarefa e a insere na fila de aptos
    tcb_t new_task;
    
    new_task.task_priority = priority;
    new_task.task_func = func;
    new_task.task_state = READY;
    new_task.task_context.stack_size = 0;
    new_task.task_delay_time = 0;
    
    
    // Inclui nova tarefa na fila de aptos
    f_aptos.tasks[f_aptos.fila_aptos_size] = new_task;
    f_aptos.fila_aptos_size++;
}

u_int get_task_id(){
    // Retorna o identificados da tarefa que está em execução
    return f_aptos.tasks[f_aptos.running_task].task_id;
}

u_int delay_release(){
    u_int i, task_released = FALSE;
    for(i = 0; i < f_aptos.fila_aptos_size; i++){
        if(f_aptos.tasks[i].task_state == WAITING) {
            f_aptos.tasks[i].task_delay_time--;
            if(f_aptos.tasks[i].task_delay_time == 0) {
                f_aptos.tasks[i].task_state = READY;
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
    if (delay_release() && DEFAULT_SCHEDULER == PRIORITY_SCHEDULER) {
        SAVE_CONTEXT(READY);
        RESTORE_CONTEXT();
    }
    if (rr_quantum == 0 && DEFAULT_SCHEDULER == PRIORITY_SCHEDULER) {
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
        f_aptos.running_task = scheduler(); 
        u_int running_task = f_aptos.running_task; 
        f_aptos.tasks[running_task].task_state = RUNNING; 
        STKPTR = 0; 
        if(f_aptos.tasks[running_task].task_context.stack_size > 0) { 
            BSR = f_aptos.tasks[running_task].task_context.BSR_reg; 
            STATUS = f_aptos.tasks[running_task].task_context.STATUS_reg; 
            WREG = f_aptos.tasks[running_task].task_context.WORK_reg; 
            u_int stack_size = f_aptos.tasks[running_task].task_context.stack_size; 
            while (stack_size) { 
                asm("PUSH"); 
                TOS = f_aptos.tasks[running_task].task_context.STACK_regs[stack_size-1]; 
                stack_size--; 
            } 
        } 
        else { 
            asm("PUSH"); 
            TOS = f_aptos.tasks[running_task].task_func; 
        } 
    ei(); 
    } while(0); 
}