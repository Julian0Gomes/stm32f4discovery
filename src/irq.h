#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_hd44780.h"
int display[4][21];

GPIO_InitTypeDef GPIO_LED_GREEN;
void Configure_PC0(void);
void Configure_PC1(void);
void Configure_PA4(void);
void Configure_PA3(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI4_IRQHandler(void);
void EXTI3_IRQHandler(void);
int configLEDPins(void);
