#include "kernelUtil.h"
#include "../gdt/gdt.h"
#include "../interrupts/IDT.h"
#include "../interrupts/interrupts.h"
#include "IO.h"

KernelInfo kernelInfo; 
PageTableManager pageTableManager = NULL;
void PrepareMemory(BootInfo* bootInfo) {
    uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescSize;

    GlobalAllocator = PageFrameAllocator();
    GlobalAllocator.ReadEFIMemoryMap(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescSize);

    uint64_t kernelSize = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;
    uint64_t kernelPages = (uint64_t)kernelSize / 4096 + 1;

    GlobalAllocator.LockPages(&_KernelStart, kernelPages);

    PageTable* PML4 = (PageTable*)GlobalAllocator.RequestPage();
    memset(PML4, 0, 0x1000);

    pageTableManager = PageTableManager(PML4);

    for (uint64_t t = 0; t < GetMemorySize(bootInfo->mMap, mMapEntries, bootInfo->mMapDescSize); t+= 0x1000){
        pageTableManager.MapMemory((void*)t, (void*)t);
    }

    uint64_t fbBase = (uint64_t)bootInfo->framebuffer->BaseAddress;
    uint64_t fbSize = (uint64_t)bootInfo->framebuffer->BufferSize + 0x1000;

    GlobalAllocator.LockPages((void*)fbBase, fbSize/ 0x1000 + 1);
    for (uint64_t t = fbBase; t < fbBase + fbSize; t += 4096){
        pageTableManager.MapMemory((void*)t, (void*)t);
    }

    asm ("mov %0, %%cr3" : : "r" (PML4));

    kernelInfo.pageTableManager = &pageTableManager;
}

IDTR idtr;
void PrepareInterrupts() {
    idtr.Limit = 0x0FFF;
    idtr.Offset = (uint64_t)GlobalAllocator.RequestPage();

    GlobalVga->Print("  Initializing PageFault interrupt...");
    GlobalVga->Next();
    IDTDescEntry* int_PageFault = (IDTDescEntry*)(idtr.Offset + 0xE * sizeof(IDTDescEntry));
    int_PageFault->SetOffset((uint64_t)PageFault_Handler);
    int_PageFault->type_attr = IDT_TA_InterruptGate;
    int_PageFault->selector = 0x08;

    GlobalVga->Print("  Initializing DoubleFault interrupt...");
    GlobalVga->Next();
    IDTDescEntry* int_DoubleFault = (IDTDescEntry*)(idtr.Offset + 0x8 * sizeof(IDTDescEntry));
    int_DoubleFault->SetOffset((uint64_t)DoubleFault_Handler);
    int_DoubleFault->type_attr = IDT_TA_InterruptGate;
    int_DoubleFault->selector = 0x08;

    GlobalVga->Print("  Initializing GPFault interrupt...");
    GlobalVga->Next();
    IDTDescEntry* int_GPFault = (IDTDescEntry*)(idtr.Offset + 0xD * sizeof(IDTDescEntry));
    int_GPFault->SetOffset((uint64_t)GPFault_Handler);
    int_GPFault->type_attr = IDT_TA_InterruptGate;
    int_GPFault->selector = 0x08;

    GlobalVga->Print("  Initializing DivideByZero interrupt...");
    GlobalVga->Next();
    IDTDescEntry* int_DBZFault = (IDTDescEntry*)(idtr.Offset + 0x0 * sizeof(IDTDescEntry));
    int_DBZFault->SetOffset((uint64_t)DivideByZero_Handler);
    int_DBZFault->type_attr = IDT_TA_InterruptGate;
    int_DBZFault->selector = 0x08;

    GlobalVga->Print("  Initializing Overflow interrupt...");
    GlobalVga->Next();
    IDTDescEntry* int_OFault = (IDTDescEntry*)(idtr.Offset + 0x4 * sizeof(IDTDescEntry));
    int_OFault->SetOffset((uint64_t)Overflow_Handler);
    int_OFault->type_attr = IDT_TA_TrapGate;
    int_OFault->selector = 0x08;

    GlobalVga->Print("  Initializing BoundRangeExceeded interrupt...");
    GlobalVga->Next();
    IDTDescEntry* int_BREFault = (IDTDescEntry*)(idtr.Offset + 0x5 * sizeof(IDTDescEntry));
    int_BREFault->SetOffset((uint64_t)BoundRangeExceeded_Handler);
    int_BREFault->type_attr = IDT_TA_InterruptGate;
    int_BREFault->selector = 0x08;

    GlobalVga->Print("  Initializing InvalidOpcode interrupt...");
    GlobalVga->Next();
    IDTDescEntry* int_IOFault = (IDTDescEntry*)(idtr.Offset + 0x6 * sizeof(IDTDescEntry));
    int_IOFault->SetOffset((uint64_t)InvalidOpcode_Handler);
    int_IOFault->type_attr = IDT_TA_InterruptGate;
    int_IOFault->selector = 0x08;

    GlobalVga->Print("  Initializing VirtualizationException interrupt...");
    GlobalVga->Next();
    IDTDescEntry* int_VEFault = (IDTDescEntry*)(idtr.Offset + 0x14 * sizeof(IDTDescEntry));
    int_VEFault->SetOffset((uint64_t)VirtualizationException_Handler);
    int_VEFault->type_attr = IDT_TA_InterruptGate;
    int_VEFault->selector = 0x08;

    GlobalVga->Print("  Initializing DeviceNotFound interrupt...");
    GlobalVga->Next();
    IDTDescEntry* int_DNFFault = (IDTDescEntry*)(idtr.Offset + 0x7 * sizeof(IDTDescEntry));
    int_DNFFault->SetOffset((uint64_t)DeviceNotFound_Handler);
    int_DNFFault->type_attr = IDT_TA_InterruptGate;
    int_DNFFault->selector = 0x08;

    asm ("lidt %0" : : "m" (idtr));

    RemapPIC();

    outb(PIC1_DATA, 0b11111101);
    outb(PIC2_DATA, 0b11111111);

    asm ("sti");
}

VgaDriver r = VgaDriver(NULL, NULL);
KernelInfo InitializeKernel(BootInfo* bootInfo) {
    r = VgaDriver(bootInfo->framebuffer, bootInfo->psf1_Font);
    GlobalVga = &r;

    PrepareMemory(bootInfo);
    memset(bootInfo->framebuffer->BaseAddress, 0, bootInfo->framebuffer->BufferSize);

    GlobalVga->Colour = 0xFFFF00;
    GlobalVga->PPrint("Initializing AirKernel...");
    GlobalVga->Next();
    GlobalVga->Colour = 0xFFFFFF;

    GlobalVga->Print("> Preparing interrupts...");
    GlobalVga->Next();
    PrepareInterrupts();

    GlobalVga->Print("> Initializing GDT descriptor...");
    GlobalVga->Next();
    GDTDescriptor gdtDescriptor;
    gdtDescriptor.Size = sizeof(GDT) - 1;
    gdtDescriptor.Offset = (uint64_t)&DefaultGDT;
    GlobalVga->Print("  Loading GDT descriptor...");
    GlobalVga->Next();
    LoadGDT(&gdtDescriptor);

    GlobalVga->Print("> Kernel initialization done!");
    GlobalVga->Next();

    return kernelInfo;
}