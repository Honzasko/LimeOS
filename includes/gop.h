ps1_font* font;

typedef struct Framebuffer 
{
    uint64_t framebuffer_addr;
    uint32_t height;
    uint32_t width;
    uint32_t pitch;

}Framebuffer;


void InitializeGOP(Framebuffer* framebuffer);

void PrintChar(char _ascii,unsigned int xOff,unsigned int yOff);
