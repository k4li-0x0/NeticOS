#pragma once
#include "../utils/math.h"
#include "framebuffer.h"
#include "simpleFonts.h" 
#include <stdint.h>

class VgaDriver {
    public:
    VgaDriver(Framebuffer* targetFramebuffer, PSF1_FONT* psf1_Font);
    Point CursorPosition;
    Framebuffer* TargetFramebuffer;
    PSF1_FONT* PSF1_Font;
    unsigned int Colour;
    unsigned int ClearColour;
    void Print(const char* str);
    void PPrint(const char* str);
    void PutChar(char chr, unsigned int xOff, unsigned int yOff);
    void PutChar(char chr);
    void ClearChar();
    void Clear();
    void DrawPixel(int x, int y, int color);
    void Fill(int x1, int y1, int x2, int y2, int color);
    void Next();
};

extern VgaDriver* GlobalVga;