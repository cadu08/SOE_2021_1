#include "pipe.h"
#include "user_config.h"

void pipe_init(pipe_t *pipe, int tamanho){
    // futuramente: tamanho é usado para alocação dinâmica, 
    // quando tivermos gerenciamento de memória
    pipe->size = pipe->read_pos = pipe->write_pos = 0;
    sem_init(&pipe->sem, 1);
}
void pipe_read(pipe_t * pipe, int *dado){
    di();
    
    bool read_flag = FALSE;
    
    do{
        if (pipe->size > 0){ // tem algo a ser lido
            *dado = pipe->msg[pipe->read_pos];
            pipe->read_pos = (pipe->read_pos + 1) % PIPE_SIZE;
            pipe->size--;
            read_flag = TRUE;
            if(sem_get_value(pipe->sem) < 0){
                sem_post(&pipe->sem);
            }
        }
        else { // se não há o que ser lido
            ei();
            sem_wait(&pipe->sem);
        }
    }while(!read_flag);
    ei();
}
void pipe_write(pipe_t *pipe, int dado){
    di();
    
    bool write_flag = FALSE;
    
    do{
        if(pipe->size < PIPE_SIZE) {
            pipe->msg[pipe->write_pos] = dado;
            pipe->write_pos = (pipe->write_pos + 1) % PIPE_SIZE;
            pipe->size++;
            write_flag = TRUE;
            if(sem_get_value(pipe->sem) < 0){
                sem_post(&pipe->sem);
            }
        }
        else {
            ei();
            sem_wait(&pipe->sem);
        }
    } while(!write_flag);
    
    ei();
    
}
