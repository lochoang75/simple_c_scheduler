#include <stdio.h>

#include "task_queue.h"
#include "coffee_task.h"

task_t gTaskQueue[MAX_TASK_NUMBER] = {0}; /*!< global task queue */

/**
 * \brief re-arrange task queue base on priority of each task 
 */
void reArrangeQueueByPriority() {
    /* use insertion sort */
    for (int i = 0; i < MAX_TASK_NUMBER; i++) {
        for (int j = 0; j < i; j++) {
            if (compareTaskByPriority(&gTaskQueue[i], &gTaskQueue[j] == 1)) {
                swapTask(&gTaskQueue[i], &gTaskQueue[j]);
            } /* end if */
        } /* end nested for */
    } /* end for */
}

/**
 * \brief re-arrange task queue base on EDF of task 
 */
void reArrangeQueueByEDF(int cur_time) {
    /* use insertion sort */
    for (int i = 0; i < MAX_TASK_NUMBER; i++) {
        for (int j = 0; j < i; j++) {
            if (compareTaskEDF(&gTaskQueue[i], &gTaskQueue[j] == 1)) {
                swapTask(&gTaskQueue[i], &gTaskQueue[j]);
            } /* end if */
        } /* end nested for */
    } /* end for */
}

/** 
 * \brief re-arrange task queue base on LLS of task
 */
void reArrangeQueueByLLS() {
    /* use insertion sort */
    for (int i = 0; i < MAX_TASK_NUMBER; i++) {
        for (int j = 0; j < i; j++) {
            if (compareTaskLLS(&gTaskQueue[i], &gTaskQueue[j] == 1)) {
                swapTask(&gTaskQueue[i], &gTaskQueue[j]);
            } /* end if */
        } /* end nested for */
    } /* end for */
}

/**
 * \brief update time counter waiting for all task in queue
 */
void updateTimeForAllTask(int time_increase) {
    task_t *selectTask = NULL;
    for (int i = 0; i < MAX_TASK_NUMBER; i++) {
        selectTask = &gTaskQueue[i];
        switch (selectTask->taskStatus)
        {
        case task_ready:
            selectTask->counterToDeadline += time_increase;
            break;
        case task_running:
            selectTask->currentTimeConsume += time_increase;
            selectTask->waittingTime += time_increase;
            break;
        case task_suspend:
            selectTask->waittingTime += time_increase;
            break;
        case task_done:
            selectTask->waittingTime += time_increase;
            break;
        default:
            break;
        } /* end switch*/
    } /* end for */
}

/**
 * \brief update status for all task in queue base on task attribute 
 */
void updateSatusForAllTask() {
    task_t *selectTask = NULL;
    for (int i = 0; i< MAX_TASK_NUMBER; i++) {
        selectTask = &gTaskQueue[i];
        switch (selectTask->taskStatus)
        {
        case task_running:
            if (selectTask->currentTimeConsume == selectTask->timeForWorking) {
                selectTask->taskStatus = task_done;
            } /* end if */
            break;
        case task_done:
            if (selectTask->waittingTime == selectTask->period) {
                selectTask->taskStatus = task_ready;
                /* when turn to ready, task will increase time to deadline 
                 * instead of waitting time so must set here for continue
                 * counter for next period */
                selectTask->waittingTime = 0; 
            }
            break;
        case task_suspend:
            /* only suspend when higher priority task come so 
             * set it to ready on next cpu circle */
            selectTask->taskStatus = task_ready;  
            break;
        case task_ready:
            /* will be handle and control by cpu, so just left it empty here*/
            break;
        
        default:
            break;
        } /* end switch */
    } /* end for loop */
}