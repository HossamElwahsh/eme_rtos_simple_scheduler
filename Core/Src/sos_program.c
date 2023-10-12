/*
 * sos_program.c
 *
 *  Created on: Oct 12, 2023
 *      Author: Hossam Elwahsh
 */

#include "sos_interface.h"
#include "sos_private.h"

/* Initialize SOS Tasks Queue */
static st_sos_tasks gs_st_sos_tasks;

/* Initialize SOS Scheduler State */
static en_sos_scheduler_state_t gs_en_sos_scheduler_state = SOS_SCH_STATE_IDLE;

/* Initialize current tick count */
static uint16_t_ gs_uint16_current_tick_count = ZERO;

/**
 * @brief                           :   Creates a new task
 * @param[in] st_a_sos_task         :   Structure holding task data
 *
 * @return  SOS_STATUS_OK           :   If successful
 *          SOS_STATUS_TASKS_FULL   :   If failed due to tasks queue full
 *          SOS_STATUS_INVALID_ARGS :   If failed due to invalid arguments passed
 */
en_sos_status_t sos_create_task(st_sos_task_t st_a_sos_task)
{
    /* Declare variables */

    /* index of created task */
    uint8_t_ uint8_l_new_task_index = ZERO;

    /* flag indicating shifting old tasks is required to make room for new task */
    boolean bool_l_require_shifting = FALSE;

    /* return value */
    en_sos_status_t en_l_sos_status_retval = SOS_STATUS_OK;

    /* Arguments Check */
    if(
            (st_a_sos_task.uint8_task_periodicity == ZERO) ||
            (st_a_sos_task.vd_ptr_task_func == NULL_PTR)
            )
    {
        /* set retval to invalid arguments */
        en_l_sos_status_retval = SOS_STATUS_INVALID_ARGS;
    }
    else
    {
        /* valid arguments */
        /* check if tasks queue is full */
        if(gs_st_sos_tasks.uint8_tasks_count == SOS_MAX_TASKS_COUNT)
        {
            /* Tasks queue is full */
            /* set retval to TASKS FULL */
            en_l_sos_status_retval = SOS_STATUS_TASKS_FULL;
        }
        else
        {
            /* Proceed with new task creation */
            /* Loop over tasks and insert task into the correct position
             * w.r.t its priority */
            for (int i = 0; i < gs_st_sos_tasks.uint8_tasks_count; ++i)
            {
                /* update new task index */
                uint8_l_new_task_index = i;

                /* Check if task priority is lower (higher in value) than new task priority */
                if(gs_st_sos_tasks.st_sos_tasks[i].uint8_task_priority > st_a_sos_task.uint8_task_priority)
                {
                    /* new task index is found, break loop */
                    break;
                }
                else
                {
                    /* Check if reached last loop without finding a spot
                     * (meaning new task to be inserted has a priority lower than all the current queue tasks) */
                    if(i == gs_st_sos_tasks.uint8_tasks_count - 1)
                    {
                        /* update task index to be at the end of queue */
                        uint8_l_new_task_index++;
                    }
                    else
                    {
                        /* Check next old task priority */
                        continue;
                    }
                }
            }

            /* Check if shifting is required for old tasks */
            if(TRUE == bool_l_require_shifting)
            {
                /* Shift tasks - starting from last task till new (to be added) task index to free a spot */
                for (int i = gs_st_sos_tasks.uint8_tasks_count-1; i >= uint8_l_new_task_index; i--)
                {
                    /* Store task in temp */
                    FILL_TASK_DATA(gs_st_sos_tasks.st_sos_tasks[i+1], gs_st_sos_tasks.st_sos_tasks[i]);
                }

                /* Insert new task in freed spot */
                FILL_TASK_DATA(gs_st_sos_tasks.st_sos_tasks[gs_st_sos_tasks.uint8_tasks_count], st_a_sos_task);

            }
            else if(FALSE == bool_l_require_shifting)
            {
                /* No shifting is required */
                /* insert new task directly */
                FILL_TASK_DATA(gs_st_sos_tasks.st_sos_tasks[uint8_l_new_task_index], st_a_sos_task);
            }

            /* Increment tasks count */
            gs_st_sos_tasks.uint8_tasks_count++;
        }
    }

    /* Return status */
    return en_l_sos_status_retval;
}

/**
 * @brief                           :   Starts the scheduler
 * @param void
 *
 * @return  SOS_STATUS_ERROR        :   If failed to start
 *          otherwise blocks inside the scheduler infinitely
 */
en_sos_status_t sos_start_scheduler(void)
{
    en_sos_status_t en_sos_status_retval = SOS_STATUS_OK;

    /* Update state to IDLE */
    gs_en_sos_scheduler_state = SOS_SCH_STATE_IDLE;

    /* Check if there's no tasks created */
    if(ZERO == gs_st_sos_tasks.uint8_tasks_count)
    {
        /* report error */
        en_sos_status_retval = SOS_STATUS_NO_TASKS;
    }
    else
    {
        /* Run Scheduler */

        /* Scheduler Loop */
        while(SOS_SCH_STATE_STOP != gs_en_sos_scheduler_state)
        {
            if(SOS_SCH_STATE_RUNNING == gs_en_sos_scheduler_state)
            {
                /* Loop over and run tasks based on their priorities */
                /* P.S. sos_task_create() already sorts tasks based on their priorities */

                for (int i = 0; i < gs_st_sos_tasks.uint8_tasks_count; ++i)
                {
                    if((GET_TASK_PERIODICITY(gs_st_sos_tasks.st_sos_tasks[i]) % gs_uint16_current_tick_count) == ZERO)
                    {
                        /* Run Task Function */
                        gs_st_sos_tasks.st_sos_tasks[i].vd_ptr_task_func();
                    }
                    else
                    {
                        /* Check next task */
                        continue;
                    }
                }

                /* revert scheduler to IDLE */
                gs_en_sos_scheduler_state = SOS_SCH_STATE_IDLE;
            }
            else
            {
                /* DO NOTHING - SCHEDULER IS IDLING */
            }
        }
    }


    return en_sos_status_retval;
}

/**
 * @brief   :   Called when a systick/timer event has occurred indicating a Tick
 */
void sos_tick_event(void)
{
    /* Increment tick counts */
    gs_uint16_current_tick_count++;

    /* Update scheduler state to RUNNING */
    gs_en_sos_scheduler_state = SOS_SCH_STATE_RUNNING;
}
