/*
 * E220_900T22D.h
 *
 *  Created on: Apr 3, 2026
 *      Author: lucas
 */

#ifndef _E220_900T22D_H_
#define _E220_900T22D_H_

#include "stm32f4xx_hal.h"

/* ======================================= LORA ====================================================*/
#define LORA_M0_PIN			GPIO_PIN_14				// Config PIN, Digital Output Pin
#define LORA_M0_PORT		GPIOC					// Port

#define LORA_M1_PIN			GPIO_PIN_15				// Config Pin, Digital Output Pin
#define LORA_M1_PORT		GPIOC					// Port

#define LORA_AUX_PIN		GPIO_PIN_0				// Flag pin, Digital Input Pin [1: Idle , 0:Message being received]
#define LORA_AUX_PORT		GPIOA					// Port







#endif /* INC_E220_900T22D_H_ */
