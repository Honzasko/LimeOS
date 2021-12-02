#include "includes/stivale.h"
uint8_t stack[0x4000];
__attribute__((used, section(".stivalehdr"))) stivale_header_t header = {.stack=&stack[0x4000], .flags=1<<0|1<<3|1<<4};

#include "includes/basics.h"
#include "includes/memory.h"
#include "includes/ps1_font.h"
#include "includes/gop.h"
#include "includes/acpi.h"
#include "includes/pci.h"
#include "includes/io.h"

int strcmp(char* str1,char* str2,int len)
{
  int status = 1;
  for (int i = 0; i < len; i++)
  {
    if(str1[i] != str2[i])
    {
      status = 0;
      break;
    }
  }
  return status;
}

void _start(stivale_struct_t* stivale) {
        //loading font
    font = (ps1_font*)stivale->modules;
    int font_loaded = 0;
    char header_magic[2] = {PS1_MAGIC0,PS1_MAGIC1};
    if(strcmp(font->psf1_header->magic,header_magic,2) == 1)
    {
        font->psf1_header->char_size = 255;
        font_loaded = 1;
    }
    
    Framebuffer framebuffer;//creates framebuffer structure
    framebuffer.framebuffer_addr = stivale->framebuffer_addr;//get framebuffer address from stivale
    framebuffer.height = stivale->framebuffer_height;//get height of screen from stivale
    framebuffer.width = stivale->framebuffer_width;
    framebuffer.pitch = stivale->framebuffer_pitch;
    InitializeGOP(&framebuffer);
    if(font_loaded == 1)
    {
      PrintChar('H',10,10);
    }
    asm("cli");
    asm ("hlt");
}
