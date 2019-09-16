#include "./video.h"


const int TERM_SIZE_X = 80;
const int TERM_SIZE_Y = 25;

int cursor_pos = 0;
int cursor_current_line = 0;

volatile char *video = (volatile char*)0xB8000; //video memory

void display_clear( int colour) //clear
{
	for (int i = 0; i < 2000; i++)
		video[i] = colour;
}

 	/*
 		0 	Черный
		1 	Синий
		2 	Зеленый
		3 	Голубой
		4 	Красный
		5 	Фиолетовый
		6 	Brown
		7 	Серый
		8 	Темно-серый
		9 	Светло-синий
		A 	Светло-зеленый
		B 	Светло-голубой
		C 	Светло-красный
		D 	Розовый
		E 	Желтый
		F 	Белый 

		функции tty_printf необходимо передать два параметра - цвет 
		и саму строку для вывода на экран. Цвет - шестнадцатеричное 
		число 0xYZ, где Y - номер цвета фона, а Z - номер цвета 
		текста. Например:

		0x01 - черный фон, синий текст
		0xe4 - желтый фон, красный текст

		tty_printf(0x01, "blue on black\n");
 		tty_printf(0xe4, "red on yellow\n");
 	*/

void tty_printf( int colour, const char *string )
{
    while( *string != 0 )
    {
    	if( *string =='\n')
    	{
    		cursor_current_line++;
    		cursor_pos = cursor_current_line * 80 * 2;
    	}
    	
    	video[cursor_pos++] = *string++;
       	video[cursor_pos++] = colour;
    }
}