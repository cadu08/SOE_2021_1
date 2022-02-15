#ifndef PIPE_H
#define	PIPE_H

#include "types.h"
#include "semaphore.h"
#include "user_config.h"
#define PIPE_SIZE 2

typedef struct pipe {
#if HEAP_MEMORY
    byte *msg;
#else
    u_int msg[PIPE_SIZE];
#endif
    u_int size;
    u_int read_pos;
    u_int write_pos;
    semaphore_t sem;
} pipe_t;

void pipe_init(pipe_t *pipe, int tamanho);
void pipe_read(pipe_t * pipe, int *dado);
void pipe_write(pipe_t *pipe, int dado);

#endif	/* PIPE_H */

