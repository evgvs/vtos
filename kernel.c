#include "./drv/video.h"

void kernel_main(void) 
{
 	display_clear(0x00);

	for(int i = 0x00; i < 0xff; i++)
		tty_printf(i, "test");
} 