#include "utils/kernelUtil.h"
#include "utils/cstr.h"

BootInfo* bootInfoGlobal;
KernelInfo kernelInfoGlobal;
PageTableManager* pageTableManagerGlobal;
extern "C" void _start(BootInfo* bootInfo) {
    bootInfoGlobal = bootInfo;
    KernelInfo kernelInfo = InitializeKernel(bootInfo);
    kernelInfoGlobal = kernelInfo;
    PageTableManager* pageTableManager = kernelInfo.pageTableManager;
    pageTableManagerGlobal = pageTableManager;
    GlobalVga->Next();
    GlobalVga->Colour = 0xFFFF00;
    GlobalVga->PPrint("AirKernel loaded!");
    GlobalVga->Colour = 0xFFFFFF;
    GlobalVga->Next();
    GlobalVga->Print("> Screen: ");
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
    GlobalVga->PPrint("> Kernel ");
    GlobalVga->Print("  PML Entries Value: ");
    GlobalVga->PPrint(to_string(static_cast<uint64_t>(pageTableManager->PML4->entries->Value)));
    GlobalVga->PPrint("> Other ");
    GlobalVga->Print("  PML Entries Value: ");
    GlobalVga->PPrint(to_string(static_cast<uint64_t>(pageTableManager->PML4->entries->Value)));
    GlobalVga->Print("  Full version: ");
    GlobalVga->PPrint(kernelInfo.fullVersion);
    GlobalVga->Print("  Kernel version: ");
    GlobalVga->PPrint(kernelInfo.kernelVersion);
    GlobalVga->Print("  OS version: ");
    GlobalVga->PPrint(kernelInfo.osVersion);
    
    while(true);
}