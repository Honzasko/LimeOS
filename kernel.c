#include "includes/stivale2.h"

static uint8_t stack[0x4000];

static struct stivale2_header_tag_terminal terminal = {
  .tag = {
    .identifier = STIVALE2_HEADER_TAG_TERMINAL_ID,
    .next = 0
  },
  .flags = 0
};

static struct stivale2_struct_tag_framebuffer buff = {
  .tag = {
    .identifier = STIVALE2_HEADER_TAG_FRAMEBUFFER_ID,
    .next = (uint64_t)&terminal
  },
  .framebuffer_height = 0,
  .framebuffer_width = 0,
  .framebuffer_bpp = 0
};

__attribute__((section(".stivale2hdr"), used)) 
static struct stivale2_header header = {
  .entry_point = 0,
  .stack = (uint64_t)&stack + sizeof(stack),
  .flags = (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4),
  .tags = (uint64_t)&buff
};

#include "includes/basics.h"
#include "includes/io.h"
#include "includes/pci.h"

void *stivale2_get_tag(struct stivale2_struct *stivale2_struct, uint64_t id) {
    struct stivale2_tag *current_tag = (void *)stivale2_struct->tags;
    for (;;) {
        // If the tag pointer is NULL (end of linked list), we did not find
        // the tag. Return NULL to signal this.
        if (current_tag == NULL) {
            return NULL;
        }
 
        // Check whether the identifier matches. If it does, return a pointer
        // to the matching tag.
        if (current_tag->identifier == id) {
            return current_tag;
        }
 
        // Get a pointer to the next tag in the linked list and repeat.
        current_tag = (void *)current_tag->next;
    }
}

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

void _start(struct stivale2_struct* stivale2) {
    struct stivale2_struct_tag_terminal *term_str_tag;
    term_str_tag = stivale2_get_tag(stivale2, STIVALE2_STRUCT_TAG_TERMINAL_ID);
    if(term_str_tag == NULL)
    {
      asm("cli");
      asm("hlt");
    }
    void *term_write_ptr = (void *)term_str_tag->term_write;
    void (*term_write)(const char *string, size_t length) = term_write_ptr;
    struct stivale2_struct_tag_rsdp *rsdp_tag;
    rsdp_tag = stivale2_get_tag(stivale2, STIVALE2_STRUCT_TAG_RSDP_ID);
    if(rsdp_tag != NULL)
    {
      struct ACPI_RSDP* rsdp = (ACPI_RSDP*)rsdp_tag->rsdp;
      ACPI_SDTHeader* xsdt = (ACPI_SDTHeader*)rsdp->xsdt_address;
      MCFGHeader* mcfg = (MCFGHeader*)ACPI_FindTable(xsdt,(char*)"MCFG");
      if(mcfg != 0)
      {
        EnumeratePCI(mcfg,term_write);
      }
    }

    asm("cli");
    asm ("hlt");
}
