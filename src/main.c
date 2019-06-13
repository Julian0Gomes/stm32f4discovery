/**
 *	Keil project example for HD44780 LCD driver
 *
 *	@author 	Tilen Majerle
 *	@email		tilen@majerle.eu
 *	@website	http://stm32f4-discovery.net
 *	@ide		Keil uVision 5
 */
#include "defines.h"
#include "stm32f4xx.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_hd44780.h"
//#include <conio.h>
#include <time.h>
#include <stdlib.h>




//int _gettimeofday( struct timeval *tv, void *tzvp )
//{
//    uint64_t t = ;  // get uptime in nanoseconds
//    tv->tv_sec = t / 1000000000;  // convert to seconds
//    tv->tv_usec = ( t % 1000000000 ) / 1000;  // get remaining microseconds
//    return 0;  // return non-zero for error
//}


int display[4][20] = {0};

void preencher_vetor(){
//	srand(time(NULL));
	int tiles_quant = rand() % 3;
	for(int i = 0; i < 4; i++){
		display[i][0] = 0; // zera as primeiras posicoes dos vetores
	}
	for(int i = 0; i < tiles_quant;i++){
		int vet = rand() % 4;
		display[vet][0] = 1;
	}
}
void step (){
	for(int j = 0; j < 4; j++){
		for (int i = 19; i > 0; i--){
			display[j][i] = display[j][i-1];
			display[j][i-1] = 0;
		}
	}


}
void print_vetor(){
	for(int j = 0; j<4; j++){
		for (int i = 0; i<20 ; i++){
			if (display[j][i] == 1)
				TM_HD44780_PutCustom(i, j, 1);
		}
	}
}

int main(void) {
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
	//Initialize system
	SystemInit();

	//Initialize LCD 20 cols x 4 rows
	TM_HD44780_Init(20, 4);

	//Save custom character on location 0 in LCD
	TM_HD44780_CreateChar(0, &customChar[0]);
	TM_HD44780_CreateChar(1, &customChar2[0]);

	//Put string to LCD




	while(1){
//
		TM_HD44780_PutCustom(19, 0, 0);
		TM_HD44780_PutCustom(19, 1, 0);
		TM_HD44780_PutCustom(19, 2, 0);
		TM_HD44780_PutCustom(19, 3, 0);
//
//		TM_HD44780_PutCustom(i, 1, 1);
//		TM_HD44780_PutCustom(i+1, 2, 1);
//		TM_HD44780_PutCustom(i+5, 2, 1);
		preencher_vetor();
		print_vetor();
		step();
		Delayms(1000);
		TM_HD44780_Clear();

	}

}
