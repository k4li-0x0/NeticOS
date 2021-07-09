#include "panic.h"
#include "../display/vga.h"

void Panic(const char* panicMessage) {
    GlobalVga->Colour = 0;
    GlobalVga->Print("!==== KERNEL PANIC ====!");
    GlobalVga->Next();
    GlobalVga->Print(panicMessage);
    asm volatile ( "hlt" );
}