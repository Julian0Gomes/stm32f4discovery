#include "display.h"

void preencher_vetor(){

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
	TM_HD44780_Puts(0,0, "GAME");
	TM_HD44780_Puts(0,1, "OVER");


	itoa(pnt, pont, 10);
	itoa(leveu,lvl,10);


	TM_HD44780_Puts(8, 0, "P");
	TM_HD44780_Puts(9, 0, "N");
	TM_HD44780_Puts(10, 0, "T");
	TM_HD44780_Puts(8, 1, pont);
	TM_HD44780_Puts(8, 2, "L");
	TM_HD44780_Puts(9, 2, "V");
	TM_HD44780_Puts(10, 2, "L");
	TM_HD44780_Puts(8, 3, lvl);



	Delayms(5000);
	NVIC_SystemReset();
}

void step (){
	int static aux = 0;
	int static div = 1;
	for(int j = 0; j < 4; j++){
		for (int i = 20; i > 4; i--){
			display[j][i] = display[j][i-1];
			display[j][i-1] = 0;
		}
		bounce[j] = display[j][20];
	}
	aux++;
	if(aux > 15){
		pnt++;
		if(pnt % passalvl == 0){
			leveu++;
			if(tempo > mintempo){
				tempo -= (int)(300/pow(1.4,div));
			}else{
				tempo = mintempo;
			}
			div++;
		}
	}
}

void verificaBotao(){
	for(int i = 0; i < 4; i++){
		if(((display[i][20] == 1) && (bounce[i] == 1)) || ((display[i][20] == 0) && (bounce[i] != 0))){
			TM_HD44780_PutCustom(19, i, 4);
			Delayms(1000);
			gameover();
		}
	}
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

void custom_char_init(void){
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


		uint8_t customChar4[] = {
			0x11,	// XXX 10001
			0x0A,	// XXX 01010
			0x64,	// XXX 00100
			0x1F,	// XXX 11111
			0x64,	// XXX 00100
			0x04,	// XXX 00100
			0x0A,	// XXX 01010
			0x1F	// XXX 10001
		};

	//Save custom character on location 0 in LCD
	TM_HD44780_CreateChar(0, &customChar[0]);
	TM_HD44780_CreateChar(1, &customChar2[0]);
	TM_HD44780_CreateChar(2, &customChar3[0]);
	TM_HD44780_CreateChar(3, &customChar4[0]);

	tempo = 1000;
	pnt = 0;
	leveu = 0;
	passalvl = 10;
	mintempo = 300;
}
