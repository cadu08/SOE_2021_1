#ifndef USER_CONFIG_H
#define	USER_CONFIG_H  

#include "types.h"

#define MAX_TASKS 3
#define RR_QUANTUM 8
#define CONVERSOR_AD TRUE
#define MOTORES TRUE
#define DISPLAY FALSE

#define SETTED_TEMPERATURE 32

/*
 * RR_SCHEDULER
 * PRIOR_SCHEDULER
 * RM_SCHEDULER
 * EDF_SCHEDULER
 */

#define DEFAULT_SCHEDULER RR_SCHEDULER //PRIORITY_SCHEDULER//RR_SCHEDULER

#endif	/* USER_CONFIG_H */

