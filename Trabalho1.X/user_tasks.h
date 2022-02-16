/* 
 * File:   user_tasks.h
 * Authors: Carlos Ferreira | Wellinton Barcelos 
 */

#ifndef USER_TASKS_H
#define	USER_TASKS_H

#define EXAMPLE 1
#define SMOKE_SENSOR PORTBbits.RB0
#define FIRE_LED LATDbits.LD0 

#include "types.h"
#include "kernel.h"
#include "semaphore.h"
#include "pipe.h"
#include "ac_controller.h"
#include "thermostat.h"

void config_user_tasks();
void thermostat_sensing_1();
void thermostat_sensing_2();
void ac_controller_1();
void ac_controller_2();
void smoke_sensing();

#endif	/* USER_TASKS_H */