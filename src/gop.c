#include <stdint.h>
#include "../includes/ps1_font.h"
#include "../includes/gop.h"

Framebuffer buffer;


void InitializeGOP(Framebuffer* framebuffer)
{
    buffer.framebuffer_addr = framebuffer->framebuffer_addr;
    buffer.height = framebuffer->height;
    buffer.width = framebuffer->width;
    buffer.pitch = framebuffer->pitch;
}



void PrintChar(char _ascii,unsigned int xOff,unsigned int yOff)
{
  unsigned int* pixPtr = (unsigned int*)buffer.framebuffer_addr;
   char* fontPtr = font->glyphs + (_ascii * 255);
    for (unsigned long y = yOff; y < yOff + 16; y++){
        for (unsigned long x = xOff; x < xOff + 8; x++){
            if ((*fontPtr & (0b10000000 >> (x - xOff))) > 0){
                    *(unsigned int*)(pixPtr + x + (y * 4)) = 0xFFFFFFFF;
                }

        }
        fontPtr++;
    }

}