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
    GlobalVga->CPPrint("> Screen: ", 0x00FFFF);
    GlobalVga->CPrint("  Height: ", 0xAFEEEE);
    GlobalVga->CPPrint(to_string(static_cast<uint64_t>(GlobalVga->TargetFramebuffer->Height)), 0xAFEEEE);
    GlobalVga->CPrint("  Width: ", 0xAFEEEE);
    GlobalVga->CPPrint(to_string(static_cast<uint64_t>(GlobalVga->TargetFramebuffer->Width)), 0xAFEEEE);
    GlobalVga->CPrint("  Buffer size: ", 0xAFEEEE);
    GlobalVga->CPPrint(to_string(static_cast<uint64_t>(GlobalVga->TargetFramebuffer->BufferSize)), 0xAFEEEE);
    GlobalVga->CPrint("  Pixel per Scanline: ", 0xAFEEEE);
    GlobalVga->CPPrint(to_string(static_cast<uint64_t>(GlobalVga->TargetFramebuffer->PixelsPerScanLine)), 0xAFEEEE);
    GlobalVga->CPPrint("> Memory ", 0x00FFFF);
    GlobalVga->CPrint("  Map Descriptor Size: ", 0xAFEEEE);
    GlobalVga->CPPrint(to_string(static_cast<uint64_t>(bootInfo->mMapDescSize)), 0xAFEEEE);
    GlobalVga->CPrint("  Map Size: ", 0xAFEEEE);
    GlobalVga->CPPrint(to_string(static_cast<uint64_t>(bootInfo->mMapSize)), 0xAFEEEE);
    GlobalVga->CPrint("  RAM free: ", 0xAFEEEE);
    GlobalVga->CPPrint(to_string(static_cast<uint64_t>(GlobalAllocator.GetFreeRAM())), 0xAFEEEE);
    GlobalVga->CPrint("  RAM used: ", 0xAFEEEE);
    GlobalVga->CPPrint(to_string(static_cast<uint64_t>(GlobalAllocator.GetUsedRAM())), 0xAFEEEE);
    GlobalVga->CPrint("  RAM total: ", 0xAFEEEE);
    GlobalVga->CPPrint(to_string(static_cast<uint64_t>(GlobalAllocator.GetFreeRAM() + GlobalAllocator.GetUsedRAM())), 0xAFEEEE);
    GlobalVga->CPrint("  RAM used: ", 0xAFEEEE);
    GlobalVga->CPPrint(to_string(static_cast<uint64_t>(GlobalAllocator.GetReservedRAM())), 0xAFEEEE);
    GlobalVga->CPPrint("> Kernel ", 0x00FFFF);
    GlobalVga->CPrint("  PML Entries Value: ", 0xAFEEEE);
    GlobalVga->CPPrint(to_string(static_cast<uint64_t>(pageTableManager->PML4->entries->Value)), 0xAFEEEE);
    GlobalVga->CPPrint("> Other ", 0x00FFFF);
    GlobalVga->CPrint("  PML Entries Value: ", 0xAFEEEE);
    GlobalVga->CPPrint(to_string(static_cast<uint64_t>(pageTableManager->PML4->entries->Value)), 0xAFEEEE);
    GlobalVga->CPrint("  Full version: ", 0xAFEEEE);
    GlobalVga->CPPrint(kernelInfo.fullVersion, 0xAFEEEE);
    GlobalVga->CPrint("  Kernel version: ", 0xAFEEEE);
    GlobalVga->CPPrint(kernelInfo.kernelVersion, 0xAFEEEE);
    GlobalVga->CPrint("  OS version: ", 0xAFEEEE);
    GlobalVga->CPPrint(kernelInfo.osVersion, 0xAFEEEE);
    
    while(true);
}