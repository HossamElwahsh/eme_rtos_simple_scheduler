/*
 * sos_private.h
 *
 *  Created on: Oct 12, 2023
 *      Author: Hossam Elwahsh
 */

#ifndef INC_SOS_PRIVATE_H_
#define INC_SOS_PRIVATE_H_

#include "std.h"

/* PRIVATE MACROS */
/* Number of tasks that the scheduler can handle */
#define SOS_MAX_TASKS_COUNT 10

#if SOS_MAX_TASKS_COUNT > MAX_8_BIT_VAL
#error 'SOS_MAX_TASKS_COUNT' CANNOT BE MORE THAN 'MAX_8_BIT_VAL'
#endif

/* fills data of new_task into task */
#define FILL_TASK_DATA(old_task, new_task)  old_task.uint8_task_priority = new_task.uint8_task_priority;\
                                        old_task.uint8_task_periodicity = new_task.uint8_task_periodicity;\
                                        old_task.vd_ptr_task_func = new_task.vd_ptr_task_func

#define GET_TASK_PERIODICITY(task) task.uint8_task_periodicity
/* PRIVATE TYPEDEFS */
typedef struct
{
    /* initialized tasks count */
    uint8_t_ uint8_tasks_count;

    /* tasks data */
    st_sos_task_t st_sos_tasks[SOS_MAX_TASKS_COUNT];
}st_sos_tasks;

typedef enum
{
    /* Scheduler is idle till next tick */
    SOS_SCH_STATE_IDLE  =   0   ,

    /* Scheduler is running */
    SOS_SCH_STATE_RUNNING       ,

    /* Scheduler Stop - Use in an event to stop scheduler execution */
    SOS_SCH_STATE_STOP          ,

    SOS_SCH_STATE_TOTAL
}en_sos_scheduler_state_t;

#endif /* INC_SOS_PRIVATE_H_ */
