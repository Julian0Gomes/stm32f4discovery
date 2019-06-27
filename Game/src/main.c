#include "main.h"

int main(void) {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	custom_char_init();

	configLEDPins();

	SystemInit();

	TM_HD44780_Init(20, 4);

	Configure_PC0();
	Configure_PC1();
	Configure_PA4();
	Configure_PA3();

	GPIO_WriteBit(GPIOD, GPIO_Pin_12, Bit_SET);

	while(1){

		header();
		preencher_vetor();
		print_vetor();
		step();
		Delayms(tempo);
		verificaBotao();

		TM_HD44780_Clear();
	}
}


int configLEDPins(void){
	// LED Green
	GPIO_LED_GREEN.GPIO_Pin = GPIO_Pin_12;
	GPIO_LED_GREEN.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_LED_GREEN.GPIO_OType = GPIO_OType_PP;
	GPIO_LED_GREEN.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_LED_GREEN);
	return 1;
}

