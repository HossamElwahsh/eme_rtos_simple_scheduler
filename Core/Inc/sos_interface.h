/*
 * sos_interface.h
 *
 *  Created on: Oct 12, 2023
 *      Author: Hossam Elwahsh
 */

#ifndef INC_SOS_INTERFACE_H_
#define INC_SOS_INTERFACE_H_

#include "std.h"

/* TYPEDEFS */
/* SOS Task Structure */
typedef struct
{
    /* Periodicity of task in ticks */
    uint8_t_ uint8_task_periodicity;

    /* Task Priority 0 (highest) -> 255 (lowest) */
    uint8_t_ uint8_task_priority;

    /* Pointer to Task Function to be executed */
    void (* vd_ptr_task_func) (void);
}st_sos_task_t;

/* SOS STATUS */
typedef enum
{
    /* OK */
    SOS_STATUS_OK   =   0   ,
    /* no tasks created */
    SOS_STATUS_NO_TASKS     ,
    /* invalid arguments passed */
    SOS_STATUS_INVALID_ARGS ,
    /* tasks queue full, cannot add more tasks */
    SOS_STATUS_TASKS_FULL   ,

    SOS_STATUS_TOTAL
}en_sos_status_t;

/**
 * @brief                           :   Creates a new task
 * @param[in] st_a_sos_task         :   Structure holding task data
 *
 * @return  SOS_STATUS_OK           :   If successful
 *          SOS_STATUS_TASKS_FULL   :   If failed due to tasks queue full
 *          SOS_STATUS_INVALID_ARGS :   If failed due to invalid arguments passed
 */
en_sos_status_t sos_create_task(st_sos_task_t st_a_sos_task);


/**
 * @brief                           :   Starts the scheduler
 * @param void
 *
 * @return  SOS_STATUS_NO_TASKS     :   If failed to start due to no tasks was created
 *          otherwise blocks inside the scheduler infinitely
 */
en_sos_status_t sos_start_scheduler(void);

/**
 * @brief   :   Called when a systick/timer event has occurred indicating a Tick
 */
void sos_tick_event(void);

#endif /* INC_SOS_INTERFACE_H_ */
