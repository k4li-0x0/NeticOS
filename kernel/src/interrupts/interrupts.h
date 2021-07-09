#pragma once
#include "../display/vga.h"
#include "../utils/panic.h"
#include "../utils/IO.h"

#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA 0xA1
#define PIC_EOI 0x20

#define ICW1_INIT 0x10
#define ICW1_ICW4 0x01
#define ICW4_8086 0x01

struct interrupt_frame;
struct trap_frame;
__attribute__((interrupt)) void PageFault_Handler(struct interrupt_frame* frame);
__attribute__((interrupt)) void DoubleFault_Handler(struct interrupt_frame* frame);
__attribute__((interrupt)) void GPFault_Handler(struct interrupt_frame* frame);
__attribute__((interrupt)) void DivideByZero_Handler(struct interrupt_frame* frame);
__attribute__((interrupt)) void Overflow_Handler(struct trap_frame* frame);
__attribute__((interrupt)) void BoundRangeExceeded_Handler(struct interrupt_frame* frame);
__attribute__((interrupt)) void InvalidOpcode_Handler(struct interrupt_frame* frame);
__attribute__((interrupt)) void VirtualizationException_Handler(struct interrupt_frame* frame);
__attribute__((interrupt)) void DeviceNotFound_Handler(struct interrupt_frame* frame);

void RemapPIC();
void PIC_EndMaster();
void PIC_EndSlave();