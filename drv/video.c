#include "video.h"


const int TERM_SIZE_X = 80;
const int TERM_SIZE_Y = 25;

int cursor_pos = 0;
int cursor_current_line = 0;

volatile char *video = (volatile char*)0xB8000; //video memory

void display_clear(int color) { //clear
	for (int i = 0; i < 2000; i++)
		video[i] = color;
}

	/*
		0	Black
		1	Dark blue
		2	Green
		3	Blue
		4	Red
		5	Violet
		6	Brown
		7	Gray
		8	Navy
		9	Medium blue
		A	Light green
		B	Light blue
		C	Light red
		D	Pink
		E	Yellow
		F	White

		tty_printf takes 2 arguments - color 
		and string with text, which you want 
		to print. Color - hexadecimal number 0xYZ,
		where Y - background color number, Z - 
		text color number.

		For example:

		0x01 - Black background, Dark blue text.
		0xe4 - Yellow background, Red text.

		tty_printf("blue on black\n", 0x01);
		tty_printf("red on yellow\n", 0xe4);
	*/
void tty_printf(const char *string, int color) {
	while( *string != 0 ) {
		if( *string =='\n') {
			cursor_current_line++;
			cursor_pos = cursor_current_line * 80 * 2;
			return;
		}
		video[cursor_pos++] = *string++;
		video[cursor_pos++] = color;
	}
}

void tty_printchar(char char1, int color) {
	if( char1 =='\n') {
		cursor_current_line++;
		cursor_pos = cursor_current_line * 80 * 2;
		return;
	}

	video[cursor_pos++] = char1;
	video[cursor_pos++] = color;
	
}
