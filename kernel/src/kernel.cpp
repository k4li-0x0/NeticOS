#include "utils/kernelUtil.h"

extern "C" void _start(BootInfo* bootInfo){

    KernelInfo kernelInfo = InitializeKernel(bootInfo);
    PageTableManager* pageTableManager = kernelInfo.pageTableManager;

    GlobalVga->Next();
    GlobalVga->Colour = 0xFFFF00;
    GlobalVga->Print("FloppaKernel v0.1 loaded!");
    GlobalVga->Colour = 0xFFFFFF;
    GlobalVga->Next();

    while(true);
}