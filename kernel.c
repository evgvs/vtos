#include "./drv/video.h"

void kernel_main(void) 
{
 	display_clear(0x00);

	int xxx = 0;
	while ( xxx < 39 ){
		tty_printf(0x0F, "M");
		xxx++;
	}
	tty_printf(0x0F, "\n");
	xxx=0;
	while ( xxx < 6 ){
                tty_printf(0x0F, "M");
		xxx++;
        }
	tty_printf(0x0F, 'E');
	xxx=0;
	while ( xxx < 5 ){
                tty_printf(0x02, "0");
                xxx++;
        }
	tty_printf(0x0F, "XWMMMMMMMMMMMMMMMMMMMMMMMM");
	tty_printf(0x0F, "\n");
	tty_printf(0x0F, "MMMMMMN");
	tty_printf(0x02, "kkkkkkk");
	tty_printf(0x0F, "KMMMMMMMMMMMMMMMMMMMMMMM");
	tty_printf(0x0F, "\n");
	tty_printf(0x0F, "MMMMMMMX");
	tty_printf(0x02, "kkkxkkk");
	tty_printf(0x0F, "XMMMMMMMMMMMMMMMMMMMMMM");
	tty_printf(0x0F, "\n");
	tty_printf(0x0F, "MMMMMMMMMXK");
	tty_printf(0x02, "KKK");
	tty_printf(0x0F, "XK0NMMMMMMMMMMMMMMMMMMMM");
	tty_printf(0x0F, "\n");
	tty_printf(0x0F, "MMMMMMMMMMMMMMMN");
	tty_printf(0x06, "OO");
	tty_printf(0x0F, "MMMMMMMMMMMMMMMMMMMM");
	tty_printf(0x0F, "\n");
	tty_printf(0x0F, "MMMMMMMMMMMMMMX");
	tty_printf(0x06, "R");
	tty_printf(0x0F, "MX");
	tty_printf(0x06, "R");
	tty_printf(0x0F, "MMMMMMMMMMMMMMMMMMM");
	tty_printf(0x0F, "\n");
	tty_printf(0x0F, "MMMMMMMMMMMMW");
	tty_printf(0x06, "R");
	tty_printf(0x0F, "XMMM");
	tty_printf(0x06, "R");
	tty_printf(0x0F, "XMMMMMMMMMMMMMMMMMM");
        tty_printf(0x0F, "\n");
	tty_printf(0x0F, "MMMMMMMMMMMM");
	tty_printf(0x06, "O");
	tty_printf(0x0F, "NMMMMW");
	tty_printf(0x06, "O");
	tty_printf(0x0F, "NMMMMMMMMMMMMMMMMM");
	tty_printf(0x0F, "\n");
	tty_printf(0x0F, "MMMMMMMMMMMX");
	tty_printf(0x06, "K");
	tty_printf(0x0F, "MMMMMMW");
	tty_printf(0x06, "OX");
	tty_printf(0x0F, "MMMMMMMMMMMMMMMM");
	tty_printf(0x0F, "\n");
	tty_printf(0x0F, "MMMMMMMMMMW");
	tty_printf(0x06, "O");
	tty_printf(0x0F, "WMMMMMMMM");
	tty_printf(0x06, "KO");
	tty_printf(0x0F, "WMMMMMMMMMMMMMM");
	tty_printf(0x0F, "\n");
	tty_printf(0x0F, "MMMMMMMMMMN");
	tty_printf(0x06, "O");
	tty_printf(0x0F, "MMMMMMMMMMX");
	tty_printf(0x04, "X0KWX0OO0X");
	tty_printf(0x0F, "WMMMM");
	tty_printf(0x0F, "\n");
	tty_printf(0x0F, "MMMMMMW");
	tty_printf(0x04, "NXXKOK00KX");
	tty_printf(0x0F, "WMMM");
	tty_printf(0x04, "WX0OOOOOOOOOW");
	tty_printf(0x0F, "MMMM");
	tty_printf(0x0F, "\n");
	tty_printf(0x0F, "MMMMM");
	tty_printf(0x04, "NOOOOOOOOOOO0");
	tty_printf(0x0F, "WM");
	tty_printf(0x04, "XOOOOOOOOOOOOX");
	tty_printf(0x0F, "MMMM");
	tty_printf(0x0F, "\n"); 
	tty_printf(0x0F, "MMMMM");
	tty_printf(0x04, "NOOOOOOOOOOO0N");
	tty_printf(0x0F, "M");
	tty_printf(0x04, "XOOOOOOOOOOOOX");
	tty_printf(0x0F, "MMMM");
	tty_printf(0x0F, "\n");
	tty_printf(0x0F, "MMMMM");
	tty_printf(0x04, "NOOOOOOOOOOO0");
	tty_printf(0x0F, "WM");
	tty_printf(0x04, "XOOOOOOOOOOOOX");
	tty_printf(0x0F, "MMMM");
	tty_printf(0x0F, "\n");
	tty_printf(0x0F, "MMMMM");
	tty_printf(0x04, "W0OOOOOOOOOOX");
	tty_printf(0x0F, "MMM");
	tty_printf(0x04, "WKOOOOOOOOK");
	tty_printf(0x0F, "WMMMMM");
	tty_printf(0x0F, "\n");
	tty_printf(0x0F, "MMMMMMW");
	tty_printf(0x04, "XK0OOO00KN");
	tty_printf(0x0F, "MMMMMM");
	tty_printf(0x04, "WXXKXXN");
	tty_printf(0x0F, "WMMMMMMM");
	tty_printf(0x0F, "\n");
	tty_printf(0x0F, "MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM");
	tty_printf(0x0F, "\n");
	tty_printf(0x0F, "\n");
	tty_printf(0xE2, "     vtOS");





	

} 
