typedef struct {
    unsigned char magic[2];
    unsigned char mode;
    unsigned char char_size;
}ps1_header;

#define PS1_MAGIC0 0x36
#define PS1_MAGIC1 0x04

typedef struct {
    ps1_header* psf1_header;
    void* glyphs;
    /* data */
}ps1_font;