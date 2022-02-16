/* 
 * File:   user_tasks.h
 * Author: milena
 *
 * Created on 21 de Julho de 2021, 15:24
 */

#ifndef USER_TASKS_H
#define	USER_TASKS_H

#define EXAMPLE 1

#include "types.h"
#include "kernel.h"
#include "semaphore.h"
#include "pipe.h"
#include "motores.h"
#include "thermostat.h"


void config_user_tasks();
void thermostat_sensing_1();
void thermostat_sensing_2();
void ac_controller_1();
void ac_controller_2();

semaphore_t sem_temp_w;
semaphore_t sem_temp_r;

#endif	/* USER_TASKS_H */
