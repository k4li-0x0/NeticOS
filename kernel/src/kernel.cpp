#include "utils/kernelUtil.h"

extern "C" void _start(BootInfo* bootInfo){

    KernelInfo kernelInfo = InitializeKernel(bootInfo);
    PageTableManager* pageTableManager = kernelInfo.pageTableManager;

    GlobalVga->Next();
    GlobalVga->Colour = 0xFFFF00;
    GlobalVga->Print("AirKernel v0.2 loaded!");
    GlobalVga->Colour = 0xFFFFFF;
    GlobalVga->Next();

    while(true);
}