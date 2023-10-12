/*
 * sos_tasks.c
 *
 *  Created on: Oct 12, 2023
 *      Author: Hossam Elwahsh
 */

#include "sos_tasks_interface.h"
#include "sos_tasks_private.h"

/**
 * @brief   :   Blinks Red1 LED
 */
void task_red1_led_blink(void)
{
    /* Toggle LED */
    HAL_GPIO_TogglePin(TASKS_RED1_LED_ARGS);
}

/**
 * @brief   :   Blinks Yellow LED
 */
void task_yellow_led_blink(void)
{
    /* Toggle LED */
    HAL_GPIO_TogglePin(TASKS_YELLOW_LED_ARGS);
}

/**
 * @brief   :   Blinks Red2 LED
 */
void task_red2_led_blink(void)
{
    /* Toggle LED */
    HAL_GPIO_TogglePin(TASKS_RED2_LED_ARGS);
}