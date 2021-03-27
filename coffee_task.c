#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "coffee_task.h"

/**
 * \brief Boolean function to check task is done or no 
 */
inline bool IsDone(task_t task) {
    if (task.currentTimeConsume == task.timeForWorking) {
        return true;
    } else if (task.currentTimeConsume < task.timeForWorking) {
        return false;
    } else {
        /* somethings wrong here, currrent consume time is bigger than time needed to complete */
        printf("TASK: Error occur when check task is done \r\n");
    }  /* end if */
} /* end function */

/**
 * \brief Swap to task 
 */
void swapTask(task_t *first_task, task_t *second_task) {
    task_t temp_task = {0};
    memcpy(&temp_task, first_task, sizeof(task_t));     /* copy first task to temp */
    memcpy(first_task, second_task, sizeof(task_t));
    memcpy(second_task, &temp_task, sizeof(task_t));
} /* End function */

/**
 * \brief Compare task base on Priority 
 */
inline int compareTaskByPriority(const task_t *first_task, const task_t *second_task) 
{
    if (first_task->priority > second_task->priority) {
        return 1;
    } /* end if */

    if (first_task->priority < second_task->priority) {
        return -1;
    } /* end if */

    return 0;
} 

/**
 * \brief Compare task base on each task total time 
 */
inline int compareTaskByLLS(const task_t *first_task, const task_t *second_task) {
    if (first_task->taskStatus == task_ready && second_task->taskStatus == task_ready) {
        /* compute how long deadline will happend, negative number is accept
        * if task miss the deadline */
        int deadlineFirstTask = (first_task->deadline - first_task->counterToDeadline);
        int deadlineSecondTask = (second_task->deadline - second_task->counterToDeadline);

        if (deadlineFirstTask < deadlineSecondTask) {
            return 1;
        } /* end if */

        if (deadlineFirstTask > deadlineSecondTask) {
            return -1;
        } /* end if */

        return 0;
    } else if (first_task->taskStatus == task_ready) {
        /* only first task is ready so set it to higher position to be select */
        return 1;
    } else if (second_task->taskStatus == task_ready) {
        /* only second task is ready so set it to higher position to be select */
        return -1;
    } 
    return 0;
}

/**
 * \brief Compare task base on task time slice each time use cpu
 */
inline int compareTaskByEDF(const task_t *first_task, const task_t *second_task) {
    if ((first_task->taskStatus == task_ready) && (second_task->taskStatus == task_ready)) {
        if (first_task->deadline < second_task->deadline) {
            return 1;
        } /* end if */

        if (first_task->deadline > second_task->deadline) {
            return -1;
        } /* end if */
    } else if (first_task->taskStatus == task_ready) {
        /* only first task is ready so set it to higher position to be select */
        return 1;
    } else if (second_task->taskStatus == task_ready) {
        /* only second task is ready so set it to higher position to be select */
        return -1;
    }

    return 0;
}
