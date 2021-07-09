#include "panic.h"
#include "../display/vga.h"

void Panic(const char* panicMessage){
    GlobalVga->ClearColour = 0x00ff0000;
    GlobalVga->Clear();

    GlobalVga->CursorPosition = {0, 0};

    GlobalVga->Colour = 0;

    GlobalVga->Print("Kernel Panic");

    GlobalVga->Next();
    GlobalVga->Next();

    GlobalVga->Print(panicMessage);
}