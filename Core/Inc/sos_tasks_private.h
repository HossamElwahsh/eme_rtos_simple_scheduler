/*
 * sos_tasks_private.h
 *
 *  Created on: Oct 12, 2023
 *      Author: Hossam Elwahsh
 */

#ifndef INC_SOS_TASKS_PRIVATE_H_
#define INC_SOS_TASKS_PRIVATE_H_

#include "stm32f1xx_hal.h"

/* LEDs PORTS, PINS ARGS */
#define TASKS_RED1_LED_ARGS     GPIOA, GPIO_PIN_2
#define TASKS_RED2_LED_ARGS     GPIOA, GPIO_PIN_1
#define TASKS_YELLOW_LED_ARGS   GPIOC, GPIO_PIN_13

#endif /* INC_SOS_TASKS_PRIVATE_H_ */
