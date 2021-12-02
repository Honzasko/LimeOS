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
   char* fontPtr = font.psf1_header->headersize + (_ascii * font.psf1_header->bytesperglyph);
    for (unsigned long y = yOff; y < yOff + 16; y++){
        for (unsigned long x = xOff; x < xOff + 8; x++){
            if ((*fontPtr & (0b10000000 >> (x - xOff))) > 0){
                    *(uint32_t*)((uint64_t)buffer.framebuffer_addr + (x * 4) + (y * (buffer.pitch / 4) * 4)) = 0xFFFFFFFF;
                }

        }
        fontPtr++;
    }

}