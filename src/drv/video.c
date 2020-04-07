#include <drv/video.h>
#include <string.h>

const int TERM_SIZE_X = 80;
const int TERM_SIZE_Y = 25;

int cursor_pos = 0;
int cursor_current_line = 0;

volatile char *video = (volatile char*)0xC00B8000; //video memory

void move_cursor(uint16_t pos)
{
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void display_clear(int color) 
{
	cursor_pos = 0;
	cursor_current_line = 0;
	for (int i = 0; i < TERM_SIZE_Y * TERM_SIZE_X; i++)
		tty_printchar(' ', color);
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
void tty_printf(const char *string, int color) 
{
	while( *string != 0 ) 
	{
		tty_printchar(*string++, color);
	}
}
void tty_printchar(char char1, int color) 
{
	if( char1 == '\n' ) 
	{
		cursor_current_line++;
		cursor_pos = cursor_current_line * 80 * 2;
		if(cursor_current_line > TERM_SIZE_Y - 1)
			tty_scroll();
		move_cursor (cursor_pos / 2);
	}
	else if ( char1 == '\b' )
	{
		cursor_pos -= 2;
		video[cursor_pos++] = ' ';
		video[cursor_pos++] = color;
		cursor_pos -= 2;
		move_cursor (cursor_pos / 2);
	}
	else if ( char1 == '\r' )
	{
		cursor_pos = cursor_current_line * 80 * 2;
		move_cursor (cursor_pos / 2);
	} 
	else
	{
		move_cursor (cursor_pos / 2);
		video[cursor_pos++] = char1;
		video[cursor_pos++] = color;
	}
}

void tty_scroll() // TODO
{
	for (int i = 0; i < 4000; i++)
	{
		if (i > 3949)
		{
			video[i]=0x00;
		} else
		{
			video[i]=video[i + TERM_SIZE_X * 2];
		}
		cursor_pos = 3840;
		cursor_current_line = 24;
	}

}
