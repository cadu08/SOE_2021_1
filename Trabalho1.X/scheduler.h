#ifndef SCHEDULER_H
#define	SCHEDULER_H

#include "types.h"
#define IDLE_TASK 0

u_int scheduler();
u_int ROUND_ROBIN_sched();
u_int PRIORITY_sched();

#endif	/* SCHEDULER_H */

