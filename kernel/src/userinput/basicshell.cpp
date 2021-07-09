#include "basicshell.h"
#include "../display/vga.h"
#include "../utils/panic.h"
#include "../utils/string.h"
#include "../utils/cstr.h"

void RunCommand(char* cmd) {
    if (strcmp(cmd, "panic") == 0) {
        Panic("User-initiated panic.");
    } else if (strcmp(cmd, "hello") == 0) {
        GlobalVga->Print("Hello world!");
        GlobalVga->Next();
    } else {
        GlobalVga->Print("Unknown command!");
        GlobalVga->Next();
    }
    GlobalVga->Print(to_string(static_cast<uint64_t>(strcmp(cmd, "panic"))));
    GlobalVga->Next();
    GlobalVga->Print(to_string(static_cast<uint64_t>(strcmp(cmd, "hello"))));
    GlobalVga->Next();
    GlobalVga->Print(cmd);
    GlobalVga->Next();
}