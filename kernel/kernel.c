#include "display/vga.h"
 
void kernel_main(void) 
{
	terminal_initialize();
	terminal_writestring("> Initializing...\n");
	terminal_writestring(" Chlenus\n");
	terminal_writestring("> Hui\n");
	terminal_writestring(" Penis");
}