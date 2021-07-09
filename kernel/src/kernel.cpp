#include "utils/kernelUtil.h"
#include "utils/cstr.h"

BootInfo* bootInfoGlobal;
extern "C" void _start(BootInfo* bootInfo) {
    bootInfoGlobal = bootInfo;
    KernelInfo kernelInfo = InitializeKernel(bootInfo);
    PageTableManager* pageTableManager = kernelInfo.pageTableManager;

    GlobalVga->Next();
    GlobalVga->Colour = 0xFFFF00;
    GlobalVga->PPrint("AirKernel v0.4 loaded!");
    GlobalVga->PPrint(to_string(static_cast<uint64_t>(GlobalVga->TargetFramebuffer->Height)));
    GlobalVga->Print("  Buffer size: ");
    GlobalVga->PPrint(to_string(static_cast<uint64_t>(GlobalVga->TargetFramebuffer->BufferSize)));
    GlobalVga->Print("  Pixel per Scanline: ");
    GlobalVga->PPrint(to_string(static_cast<uint64_t>(GlobalVga->TargetFramebuffer->PixelsPerScanLine)));
    GlobalVga->PPrint("> Memory ");
    GlobalVga->Print("  Map Descriptor Size: ");
    GlobalVga->PPrint(to_string(static_cast<uint64_t>(bootInfo->mMapDescSize)));
    GlobalVga->Print("  Map Size: ");
    GlobalVga->PPrint(to_string(static_cast<uint64_t>(bootInfo->mMapSize)));
    GlobalVga->Print("  RAM free: ");
    GlobalVga->PPrint(to_string(static_cast<uint64_t>(GlobalAllocator.GetFreeRAM())));
    GlobalVga->Print("  RAM used: ");
    GlobalVga->PPrint(to_string(static_cast<uint64_t>(GlobalAllocator.GetUsedRAM())));
    GlobalVga->Print("  RAM total: ");
    GlobalVga->PPrint(to_string(static_cast<uint64_t>(GlobalAllocator.GetFreeRAM() + GlobalAllocator.GetUsedRAM())));
    GlobalVga->Print("  RAM used: ");
    GlobalVga->PPrint(to_string(static_cast<uint64_t>(GlobalAllocator.GetReservedRAM())));
    //GlobalVga->Fill(0,0,50,50,0xFFFF00);

    while(true);
}