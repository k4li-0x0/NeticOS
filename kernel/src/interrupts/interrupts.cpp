#include "interrupts.h"

__attribute__((interrupt)) void PageFault_Handler(struct interrupt_frame* frame){
    Panic("Page Fault Detected");
}

__attribute__((interrupt)) void DoubleFault_Handler(struct interrupt_frame* frame){
    Panic("Double Fault Detected");
}

__attribute__((interrupt)) void GPFault_Handler(struct interrupt_frame* frame){
    Panic("General Protection Fault Detected");
}

__attribute__((interrupt)) void DivideByZero_Handler(struct interrupt_frame* frame) {
    Panic("Divide by Zero Detected");
}

__attribute__((interrupt)) void Overflow_Handler(struct trap_frame* frame) {
    Panic("Overflow Detected");
}

__attribute__((interrupt)) void BoundRangeExceeded_Handler(struct interrupt_frame* frame) {
    Panic("Bound Range Exceeded"); 
}

__attribute__((interrupt)) void InvalidOpcode_Handler(struct interrupt_frame* frame) {
    Panic("Invalid Opcode"); 
}

__attribute__((interrupt)) void VirtualizationException_Handler(struct interrupt_frame* frame) {
    Panic("Virtualization Exception Detected"); 
}

__attribute__((interrupt)) void DeviceNotFound_Handler(struct interrupt_frame* frame) {
    Panic("Device not found"); 
}


void PIC_EndMaster(){
    outb(PIC1_COMMAND, PIC_EOI);
}

void PIC_EndSlave(){
    outb(PIC2_COMMAND, PIC_EOI);
    outb(PIC1_COMMAND, PIC_EOI);
}
   

void RemapPIC(){
    uint8_t a1, a2; 

    a1 = inb(PIC1_DATA);
    io_wait();
    a2 = inb(PIC2_DATA);
    io_wait();

    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();

    outb(PIC1_DATA, 0x20);
    io_wait();
    outb(PIC2_DATA, 0x28);
    io_wait();

    outb(PIC1_DATA, 4);
    io_wait();
    outb(PIC2_DATA, 2);
    io_wait();

    outb(PIC1_DATA, ICW4_8086);
    io_wait();
    outb(PIC2_DATA, ICW4_8086);
    io_wait();

    outb(PIC1_DATA, a1);
    io_wait();
    outb(PIC2_DATA, a2);
}