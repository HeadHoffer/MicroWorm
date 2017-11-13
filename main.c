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
#include "lcd.h"

//Portteihin kytketyt laitteet
#define Switch PIND
#define SW1 PD0
#define SW2 PD1
#define SW3 PD2
#define SW4 PD3
#define SW5 PD4



//typedef char bool;
/********************************
 main 

 *******************************/
int main(void)
{
	DDRD &= ~((1<<SW1)|(1<<SW2)|(1<<SW3)|(1<<SW4)|(1<<SW5));

	// IO-port INIT
	DDRA = 0xE0;
 
	// LCD - Display Init
	lcd_init();

	lcd_clear();

	
	int aStartValue = 20;
	int bStartValue = aStartValue + 10;
	int speed = 10;

	//PrintSquare(aStartValue, bStartValue);
	//PrintCircle(40,40,12);

	while(true)
	{
	
	if(~Switch & (1<<SW1))
	{
		lcd_clear();
		aStartValue += 10;
		PrintSquare(aStartValue, bStartValue);
	}

	if(~Switch & (1<<SW3))
	{
		lcd_clear();
		aStartValue -= 10;
		PrintSquare(aStartValue, bStartValue);
	}

	if(~Switch & (1<<SW4))
	{
		lcd_clear();
		bStartValue += 10;
		PrintSquare(aStartValue, bStartValue);
	}

	if(~Switch & (1<<SW2))
	{
		lcd_clear();
		bStartValue -= 10;
		PrintSquare(aStartValue, bStartValue);
	}

	}

	
	
	
	// Testataan viivan piirtoa
	//lcd_Line_vert(40, 40, 50); // proto Fungtio 
	//lcd_Line_Hor(5, 5, 20);
}

void PrintSquare(int x, int y)
{
	// Piirtää näytölle "neliön" pikseli kerrallaan
	for(int a = x; a < (x + 10); a++)
	{
		for(int b = y; b < (y + 10); b++)
		{
			lcd_pixel(a,b);
		}
	}
	/*
	for(int i = x; i < (x + 10); i++)
	{
		lcd_pixel(x,i);
		lcd_pixel(i,x);
	}
	for(int j = y; j > (y - 10); j--)
	{
		lcd_pixel(y,j);
		lcd_pixel(j,y);
	}
	*/
}

void PrintCircle(int x, int y, int radius)
{
	int iterations = 180;
	float scaler = 1.3;

	for(int i = 0; i < iterations; ++i)
	{
		float rad = (360.0 / iterations * i) * M_PI / 180.0;
		lcd_pixel(
			round(x + (cos(rad) * radius * scaler)), round(y + (sin(rad) * radius)));
	}
}
