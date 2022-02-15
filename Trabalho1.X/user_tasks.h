/* 
 * File:   user_tasks.h
 * Author: milena
 *
 * Created on 21 de Julho de 2021, 15:24
 */

#ifndef USER_TASKS_H
#define	USER_TASKS_H

#include "types.h"
#include "kernel.h"
#include "semaphore.h"
#include "pipe.h"
#include "motores.h"
#include "conversor.h"


void config_user_tasks();

void sensoreamento_termostato();
void ac_controller();


#endif	/* USER_TASKS_H */
