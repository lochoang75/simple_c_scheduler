#include <stdio.h>
#include <stdlib.h>

#include "task_shedule.h"
#include "task_queue.h"

#ifndef TASK_SCHELDULE_H
#define TASK_SCHEDULE_H

static inline task_t* getTask();
static const int timeslot = 1;              /*!< Set time slot to 1 seconds */

/**
 * \brief schedule task for all task in queue
 */
void start_schedule() {
    task_t* selectedTask = NULL;
    while (true) {
        selectedTask = getTask();
        selectedTask->taskStatus = task_running;
        selectedTask->taskAction(NULL);
        
        /* delay for 1 sec */
        delay(1000);
        
        /* task queue variable update */
        updateTimeForAllTask(1);
        updateStatusForAllTask();

        /* re-arange queue maybe modify later */
        reArrangeQueueByPriority();
    } /* end while */
}

#endif /* TASK_SCHEDULE_H */