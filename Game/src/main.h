/*
 * main.h
 *
 *  Created on: 26 de jun de 2019
 *      Author: jsgom
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "defines.h"
#include "stm32f4xx.h"
#include "tm_stm32f4_delay.h"
#include <time.h>
#include <stdlib.h>
#include <strings.h>
#include "irq.h"
#include "misc.h"


int configLEDPins(void);



GPIO_InitTypeDef GPIO_LED_GREEN;


#endif /* MAIN_H_ */
