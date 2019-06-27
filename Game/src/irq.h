#ifndef IRQ_H
#define IRQ_H_
#include "tm_stm32f4_hd44780.h"
#include "display.h"

void Configure_PC0(void);
void Configure_PC1(void);
void Configure_PA4(void);
void Configure_PA3(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI4_IRQHandler(void);
void EXTI3_IRQHandler(void);

#endif
