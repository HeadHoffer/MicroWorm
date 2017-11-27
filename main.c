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

#define GRID_WIDTH 64
#define GRID_HEIGHT 32

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

int main(void)

{
	DDRD &= ~((1<<SW1)|(1<<SW2)|(1<<SW3)|(1<<SW4)|(1<<SW5));

	// IO-port INIT
	DDRA = 0xE0;
 
	LCD_Init_With_Flags(FLAG_LANDSCAPE | FLAG_IGNORE_WHITESPACE);

	int num_snake_cells = 5;
	char snake[GRID_WIDTH * GRID_HEIGHT][2] = {
		{ 20, 20 },
		{ 19, 20 },
		{ 18, 20 },
		{ 17, 20 },
		{ 16, 20 },
	};
	char food[2];

	bool up,down,left,right = false;

	DrawBox();

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
			Move(snake, &num_snake_cells, 0);
		}
		if(down)
		{
			Move(snake, &num_snake_cells, 1);
		}
		if(left)
		{
			Move(snake, &num_snake_cells, 2);
		}
		if(right)
		{
			Move(snake, &num_snake_cells, 3);
		}
		
		DrawSnake(snake, num_snake_cells);
		LCD_Display();
	}
}

void Move(char **snake, int *num_snake_cells, char direction)
{
	char new_pos[2];
	new_pos[0] = snake[0][0];
	new_pos[1] = snake[0][1];

	switch(direction) {
		case 0: // up
			new_pos[1]++;
			break;
		case 1: // down
			new_pos[1]--;
			break;
		case 2: // left
			new_pos[0]--;
			break;
		case 3: // right
			new_pos[0]++;
			break;	
	}

	int i;
	for(i = 1; i < *num_snake_cells; i++) {
		snake[i][0] = snake[i - 1][0];
		snake[i][1] = snake[i - 1][1];
	}

	snake[0][0] = new_pos[0];
	snake[0][1] = new_pos[1];
}

void DrawSnake(char **snake, int num_snake_cells)
{
	LCD_ClearArea(1,1,126,62);

	int i;
	for(i = 0; i < num_snake_cells; i++) {
		int x = snake[i][0];
		int y = snake[i][1];
		int screen_x = x * (SCREEN_WIDTH / GRID_WIDTH);
		int screen_y = y * (SCREEN_HEIGHT / GRID_HEIGHT);
		LCD_FillRect(screen_x, screen_y, screen_x + (SCREEN_WIDTH / GRID_WIDTH), screen_y + (SCREEN_HEIGHT / GRID_HEIGHT));
	}
}

void DrawBox()
{
	LCD_DrawLine(0,0,128,0); //bottom
	LCD_DrawLine(127,1,127,63); //left
	LCD_DrawLine(0,1,0,63); //right
	LCD_DrawLine(0,63,128,63); //top
}

