﻿#include <drv/keyboard.h>
#include <drv/video.h>
#include <interrupts.h>
#include <ports.h>

//#define ARR_LENGTH(a) (a/sizeof(a[0]))

typedef struct {
	uint8_t scancode;
	char chr; //Character it corresponds to.
} kybd_scancode;

static kybd_scancode regular_scancodes[] = {
	/* Numerical keys */
	{0x02, '1'}, {0x03, '2'}, {0x04, '3'}, {0x05, '4'}, {0x06, '5'}, {0x07, '6'}, {0x08, '7'}, {0x09, '8'}, {0x0A, '9'}, {0x0B, '0'},
	/* Some characters after numerical keys */
	{0x0C, '-'}, {0x0D, '='}, {0x0E, '\b'}, {0x0F, '\t'},
	/* Alphabet! */
	{0x10, 'q'}, {0x11, 'w'}, {0x12, 'e'}, {0x13, 'r'}, {0x14, 't'}, {0x15, 'y'}, {0x16, 'u'}, {0x17, 'i'}, {0x18, 'o'}, {0x19, 'p'}, {0x1A, '['}, {0x1B, ']'}, {0x1C, '\n'},
	{0x1E, 'a'}, {0x1F, 's'}, {0x20, 'd'}, {0x21, 'f'}, {0x22, 'g'}, {0x23, 'h'}, {0x24, 'j'}, {0x25, 'k'}, {0x26, 'l'}, {0x27, ';'}, {0x28, '\''}, {0x29, '`'},
	{0x2B, '\\'}, {0x2C, 'z'}, {0x2D, 'x'}, {0x2E, 'c'}, {0x2F, 'v'}, {0x30, 'b'}, {0x31, 'n'}, {0x32, 'm'}, {0x33, ','}, {0x34, '.'}, {0x35, '/'}, {0x37, '*'},
	{0x39, ' '}, {0x47, '7'}, {0x48, '8'}, {0x49, '9'}, {0x4A, '-'},
	{0x4B, '4'}, {0x4C, '5'}, {0x4D, '6'}, {0x4E, '+'},
	{0x4F, '1'}, {0x50, '2'}, {0x51, '3'},
	{0x52, '0'}, {0x53, '.'}, {0x00, '\0'}
};
static kybd_scancode uppercase_scancodes[] = {
	/* Numerical keys */
	{0x02, '1'}, {0x03, '2'}, {0x04, '3'}, {0x05, '4'}, {0x06, '5'}, {0x07, '6'}, {0x08, '7'}, {0x09, '8'}, {0x0A, '9'}, {0x0B, '0'},
	/* Some characters after numerical keys */
	{0x0C, '-'}, {0x0D, '='}, {0x0E, '\b'}, {0x0F, '\t'},
	/* Alphabet! */
	{0x10, 'Q'}, {0x11, 'W'}, {0x12, 'E'}, {0x13, 'R'}, {0x14, 'T'}, {0x15, 'Y'}, {0x16, 'U'}, {0x17, 'I'}, {0x18, 'O'}, {0x19, 'P'}, {0x1A, '['}, {0x1B, ']'}, {0x1C, '\n'},
	{0x1E, 'A'}, {0x1F, 'S'}, {0x20, 'D'}, {0x21, 'F'}, {0x22, 'G'}, {0x23, 'H'}, {0x24, 'J'}, {0x25, 'K'}, {0x26, 'L'}, {0x27, ';'}, {0x28, '\''}, {0x29, '`'},
	{0x2B, '\\'}, {0x2C, 'Z'}, {0x2D, 'X'}, {0x2E, 'C'}, {0x2F, 'V'}, {0x30, 'B'}, {0x31, 'N'}, {0x32, 'M'}, {0x33, ','}, {0x34, '.'}, {0x35, '/'}, {0x37, '*'},
	{0x39, ' '}, {0x47, '7'}, {0x48, '8'}, {0x49, '9'}, {0x4A, '-'},
	{0x4B, '4'}, {0x4C, '5'}, {0x4D, '6'}, {0x4E, '+'},
	{0x4F, '1'}, {0x50, '2'}, {0x51, '3'},
	{0x52, '0'}, {0x53, '.'}, {0x00, '\0'}
};
static kybd_scancode shift_modified_scancodes[] = {
	/* Numerical keys */
	{0x02, '!'}, {0x03, '@'}, {0x04, '#'}, {0x05, '$'}, {0x06, '%'}, {0x07, '^'}, {0x08, '&'}, {0x09, '*'}, {0x0A, '('}, {0x0B, ')'},
	/* Some characters after numerical keys */
	{0x0C, '_'}, {0x0D, '+'}, {0x0E, '\b'}, {0x0F, '\t'},
	/* Alphabet! */
	{0x10, 'Q'}, {0x11, 'W'}, {0x12, 'E'}, {0x13, 'R'}, {0x14, 'T'}, {0x15, 'Y'}, {0x16, 'U'}, {0x17, 'I'}, {0x18, 'O'}, {0x19, 'P'}, {0x1A, '{'}, {0x1B, '}'}, {0x1C, '\n'},
	{0x1E, 'A'}, {0x1F, 'S'}, {0x20, 'D'}, {0x21, 'F'}, {0x22, 'G'}, {0x23, 'H'}, {0x24, 'J'}, {0x25, 'K'}, {0x26, 'L'}, {0x27, ':'}, {0x28, '"'}, {0x29, '~'},
	{0x2B, '\\'}, {0x2C, 'Z'}, {0x2D, 'X'}, {0x2E, 'C'}, {0x2F, 'V'}, {0x30, 'B'}, {0x31, 'N'}, {0x32, 'M'}, {0x33, '<'}, {0x34, '>'}, {0x35, '?'}, {0x37, '*'},
	{0x39, ' '}, {0x47, '7'}, {0x48, '8'}, {0x49, '9'}, {0x4A, '-'},
	{0x4B, '4'}, {0x4C, '5'}, {0x4D, '6'}, {0x4E, '+'},
	{0x4F, '1'}, {0x50, '2'}, {0x51, '3'},
	{0x52, '0'}, {0x53, '.'}, {0x00, '\0'}
};

//why static??
static kbd_event keyboard_buffer[256] = {};//keyboard buffer
static uint32_t kbd_buf_in  = 0;//writing to buffer position
static uint32_t kbd_buf_out = 0;//reading from buffer position


void keyboard_buffer_push(kbd_event value)//add keyboard event to buffer
{
	keyboard_buffer[(kbd_buf_in++) % 256] = value;
	if(kbd_buf_in > 256 && kbd_buf_out > 256)
	{
		kbd_buf_in -= 256;
		kbd_buf_out -= 256;
	}
	if(kbd_buf_in - kbd_buf_out > 256)
	{
		//buffer overflow happened
	}
}

kbd_event keyboard_buffer_pop()//read last keyboard event from buffer
{
	static kbd_event none = {0};
	if(kbd_buf_in <= kbd_buf_out)
		return none;
	return keyboard_buffer[(kbd_buf_out++) % 256];
}

//volatile because it can change beacuse of external reasons
volatile bool kbd_irq_fired = false;//while with kb nothing happens it stays false
//any kb irq will make it true

void keyboard_wait_irq()
{
	while(!kbd_irq_fired);
	kbd_irq_fired=false;
}

char keyboard_event_convert(kbd_event e)//convert keyboard event structure to char
{
	if(!e.exists || e.release)
		return 0;

	uint8_t shift = (e.lshift || e.rshift) && !e.capslk;
	uint8_t uppercase = e.capslk && !e.lshift && !e.rshift;

	int i;
	if(uppercase)
	{
		for(i=0; uppercase_scancodes[i].scancode != 0x00; i++)
			if(uppercase_scancodes[i].scancode == e.code)
			  return uppercase_scancodes[i].chr;
		return 0;
	}
	else if(shift)
	{
		for(i=0; shift_modified_scancodes[i].scancode != 0x00; i++)
			if(shift_modified_scancodes[i].scancode == e.code)
			  return shift_modified_scancodes[i].chr;
		return 0;
	}
	else {
		for(i=0; regular_scancodes[i].scancode != 0x00; i++)
			if(regular_scancodes[i].scancode == e.code)
			  return regular_scancodes[i].chr;
		return 0;
	}
}

//keyboard irq handler
void keyboard_handler(__attribute__((unused)) struct regs *r)
{
	static kbd_event state = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	kbd_irq_fired = true;
	//We need to put every pressed printable key to the buffer.
	uint8_t scancode = inb(KBD_DATA);
	if(scancode > 0x80 && scancode < 0xE0)
	{
		state.release = 1;
		scancode -= 0x80;
	}

	switch(scancode)
	{
		case KEY_LSHIFT: state.lshift = !state.release; break;
		case KEY_RSHIFT: state.rshift = !state.release; break;
		case KEY_LCTRL:  state.lctrl  = !state.release; break;
		case KEY_RCTRL:  state.rctrl  = !state.release; break;
		case 0xE0: state.code |= 0x100;
		//case 0xE1: state.code |= 0x200;
		//case 0xF0: state.release = 1;
		//default:   state.release = 0;
	}

	if(scancode != 0xE0 && scancode != 0xE1)
	{
		state.code += scancode;
		keyboard_buffer_push(state);
		state.code = 0;
		state.release = 0;
	}
}

uint8_t keyboard_getchar()
{
	char ret = NULL;
	while(!ret)
	{
		if(kbd_buf_in == kbd_buf_out)
			keyboard_wait_irq();
		ret = keyboard_event_convert(keyboard_buffer_pop());
	}
	return ret;
}

char * keyboard_getstring()
{
	char * string = NULL;
	int gets_cursor_position = 0;
	while (1)
	{
		char ch = keyboard_getchar();
		
		if (ch == '\n') 
		{
			tty_printchar (ch, 0x0f);
			return string;
		}
		else if (ch == '\b') 
		{
			string[gets_cursor_position--] = NULL;
			tty_printchar ('\b', 0x0f);
		} else 
		{
			tty_printchar (ch, 0x0f);
			string[gets_cursor_position++] = ch;
			string[gets_cursor_position--] = NULL;
			string[gets_cursor_position++] = ch;
		}
	}
	return string;
}

/*
This function is waits for keyboard buffer to empty.
*/
void keyboard_waitForBufToEmpty()
{
	char c = inb(0x60);
	while (inb(0x60) == c)
		c = inb(0x60);
}

/*void keyboard_scancodes_setup()
{
}*/

//Keyboard-powered CPU reset.
void keyboard_reset_cpu()
{
	asm("cli");
	uint8_t good = 0x02;
	while (good & 0x02)
		good = inb(0x64);
	outb(0x64, 0xFE);
	tty_printf("Keyboard CPU reset failed.\n", 0x0f);
	asm("hlt");
}


void keyboard_install() {
	register_interrupt_handler(KEYBOARD_IDT_INDEX, keyboard_handler);
	//state.caps_lock = 0;
	//state.shift_held = 0;
	//printf("Keyboard installed.\n");
}
