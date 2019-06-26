#include "defines.h"
#include "stm32f4xx.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_hd44780.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <strings.h>
#include "irq.h"
#include "misc.h"


extern int display[4][21];
int tempo = 1000;
int pnt = 0;
int leveu = 0;
int passalvl = 10;
int mintempo = 300;
char pont[3];
char lvl[3];



void preencher_vetor(){
//	srand(time(NULL));
	int tiles_quant = rand() % 3;
	for(int i = 0; i < 4; i++){
		display[i][4] = 0; // zera as primeiras posicoes dos vetores
	}
	for(int i = 0; i < tiles_quant;i++){
		int vet = rand() % 4;
		display[vet][4] = 1;
	}
}
void gameover(){
	TM_HD44780_Clear();
	TM_HD44780_Puts(2,8, "GAME OVER");
	Delayms(3000);
	NVIC_SystemReset();
}
void verificaBotao(){
	for(int i = 0; i < 4; i++){
		if(display[i][20] != 0){
			gameover();
		}
	}
}
void step (){
	int static aux = 0;
	int static div = 1;
	for(int j = 0; j < 4; j++){
		for (int i = 20; i > 4; i--){
			display[j][i] = display[j][i-1];
			display[j][i-1] = 0;
		}
	}
	aux++;
	if(aux > 15){
		pnt++;
		if(pnt % passalvl == 0){
			leveu++;
//			if(leveu % 1 == 0){
//				jequiti();
//			}
			if(tempo > mintempo){
				tempo -= (int)(300/pow(1.4,div));
			}else{
				tempo = mintempo;
			}
			div++;
		}

	}


}
void jequiti(){
	TM_HD44780_Clear();
	TM_HD44780_Puts(8, 1, "J");
	TM_HD44780_Puts(9, 1, "E");
	TM_HD44780_Puts(10, 1, "Q");
	TM_HD44780_Puts(11, 1, "U");
	TM_HD44780_Puts(12, 1, "I");
	TM_HD44780_Puts(13, 1, "T");
	TM_HD44780_Puts(14, 1, "I");
	Delayms(50);
	TM_HD44780_Clear();
 }



void header(){
	itoa(pnt, pont, 10);
	itoa(leveu,lvl,10);

	TM_HD44780_Puts(0, 0, "P");
	TM_HD44780_Puts(1, 0, "N");
	TM_HD44780_Puts(2, 0, "T");
	TM_HD44780_Puts(0, 1, pont);
	TM_HD44780_Puts(0, 2, "L");
	TM_HD44780_Puts(1, 2, "V");
	TM_HD44780_Puts(2, 2, "L");
	TM_HD44780_Puts(0, 3, lvl);

	//static
	TM_HD44780_PutCustom(19, 0, 0);
	TM_HD44780_PutCustom(19, 1, 0);
	TM_HD44780_PutCustom(19, 2, 0);
	TM_HD44780_PutCustom(19, 3, 0);

	TM_HD44780_PutCustom(3, 0, 2);
	TM_HD44780_PutCustom(3, 1, 2);
	TM_HD44780_PutCustom(3, 2, 2);
	TM_HD44780_PutCustom(3, 3, 2);
}
void print_vetor(){
	for(int j = 0; j<4; j++){
		for (int i = 4; i<20 ; i++){
			if (display[j][i] == 1){
				TM_HD44780_PutCustom(i, j, 1);
			}
		}
	}
}


//void verifica_slot(){
//	if ()
//}
int main(void) {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	//Rectangle for custom character
	//XXX means doesn't care, lower 5 bits are important for LCD
	uint8_t customChar[] = {
		0x1F,	// XXX 11111
		0x11,	// XXX 10001
		0x11,	// XXX 10001
		0x11,	// XXX 10001
		0x11,	// XXX 10001
		0x11,	// XXX 10001
		0x11,	// XXX 10001
		0x1F	// XXX 11111
	};

	uint8_t customChar2[] = {
		0x1F,	// XXX 11111
		0x1F,	// XXX 11111
		0x1F,	// XXX 11111
		0x1F,	// XXX 11111
		0x1F,	// XXX 11111
		0x1F,	// XXX 11111
		0x1F,	// XXX 11111
		0x1F	// XXX 11111
	};

	uint8_t customChar3[] = {
		0x64,	// XXX 00100
		0x64,	// XXX 00100
		0x64,	// XXX 00100
		0x64,	// XXX 00100
		0x64,	// XXX 00100
		0x64,	// XXX 00100
		0x64,	// XXX 00100
		0x64	// XXX 00100
	};

	//Initialize system
	configLEDPins();
	SystemInit();

	//Delayms(tempo);
	//Initialize LCD 20 cols x 4 rows
	TM_HD44780_Init(20, 4);

	//Save custom character on location 0 in LCD
	TM_HD44780_CreateChar(0, &customChar[0]);
	TM_HD44780_CreateChar(1, &customChar2[0]);
	TM_HD44780_CreateChar(2, &customChar3[0]);

	//Put string to LCD

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
