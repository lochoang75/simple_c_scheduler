#include <stdio.h>

#include "task_queue.h"
#include "task_schedule.h"


int main(int argc, char* argv[]) 
{
    /* set schedule type */
    setSchedulerType(task_schedule_custom);
    /* Prepare for schedule */
    prepareSchedule();

    /* start schedule */
    startSchedule();

    return 0;
}