#pragma once

#include <stdint.h>
#include "../display/vga.h"
#include "../utils/cstr.h"
#include "../memory/efiMemory.h"
#include "../memory/memory.h"
#include "../display/bitmap.h"
#include "../paging/PageFrameAllocator.h"
#include "../paging/PageMapIndexer.h"
#include "../paging/paging.h"
#include "../paging/PageTableManager.h"

struct BootInfo {
	Framebuffer* framebuffer;
	PSF1_FONT* psf1_Font;
	EFI_MEMORY_DESCRIPTOR* mMap;
	uint64_t mMapSize;
	uint64_t mMapDescSize;
} ;

extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;

struct KernelInfo {
    PageTableManager* pageTableManager;
	char* fullVersion;
	char* kernelVersion;
	char* osVersion;
};

KernelInfo InitializeKernel(BootInfo* BootInfo);