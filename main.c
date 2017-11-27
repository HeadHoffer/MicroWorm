/********************************************************
** Kajaani Amk
** Markku Karppinen 25.5. 2012
** Muokattu: 26.10.2014 (Batron_2 LCD)/ Risto A.
**
** Näyttö Opetuskortti Rew2. 
*	PC0: Reset
*	PC1: Sce 
*	PC2: D / C
*	PC3: SDin (Data)
*	PC4: SCLK (Kello)
**
**  Alusta:
** 	Opetukortti ATMEGA 128:: AVR-GCC
**	Fuse Bits:0xFF, 0xB9, 0xE4
**
*************!!!!!!  Power 3.3c !!!!!*********************
**
**********************************************************/

#define	true	1
#define false	0
#define	NB_SHOTS	5
#define STEP_MAX	1

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <math.h>
#include "lcd_utils.h"
#include <stdbool.h>

//Portteihin kytketyt laitteet
#define Switch PIND
#define SW1 PD0
#define SW2 PD1
#define SW3 PD2
#define SW4 PD3
#define SW5 PD4




int main(void)

{
	DDRD &= ~((1<<SW1)|(1<<SW2)|(1<<SW3)|(1<<SW4)|(1<<SW5));

	// IO-port INIT
	DDRA = 0xE0;
 
	LCD_Init_With_Flags(FLAG_LANDSCAPE | FLAG_IGNORE_WHITESPACE);
	
	int x = 30;
	int y = 30;

	bool up,down,left,right = false;

	int coords[2] = {x,y};

	while(true)
	{
		if(~Switch & (1<<SW4))
		{
			up = true;
			down = left = right = false;
		}
		if(~Switch & (1<<SW1))
		{
			left = true;
			down = up = right = false;
		}
		if(~Switch & (1<<SW3))
		{
			right = true;
			down = left = up = false;
		}
		if(~Switch & (1<<SW2))
		{
			down = true;
			up = left = right = false;
		}
		if(up)
		{
			Move(&coords[1], 1);
		}
		if(down)
		{
			Move(&coords[1], -1);
		}
		if(left)
		{
			Move(&coords[0], 1);
		}
		if(right)
		{
			Move(&coords[0], -1);
		}
		
		PrintPixel(coords[0],coords[1]);
		LCD_Display();
	}
}

void PrintPixel(int x, int y)
{
	LCD_Clear();
	LCD_DrawPixel(x,y);
}

void Move(int *coord, int moveValue)
{
	*coord += moveValue;
}




