#ifndef DISPLAY_H
#define DISPLAY_H_

#include <math.h>
#include "tm_stm32f4_hd44780.h"

int display[4][21];
int bounce[4];
int tempo;
int pnt;
int leveu;
int passalvl;
int mintempo;
char pont[3];
char lvl[3];




void gameover();
void step ();
void jequiti();
void verificaBotao();
void header();
void print_vetor();
void custom_char_init(void);



#endif
