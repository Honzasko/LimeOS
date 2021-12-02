#include <stdint.h>
#include "../../includes/io.h"
#include "../../includes/keyboard/ps2.h"



void init()
{
    for (uint8_t i = 0; i < 72; i++)
    {
        if(i == KEY_0)
        {
            keys[i] = '0';
        }
        else if(i == KEY_1)
        {
            keys[i] = '1'; 
        }
        else if(i == KEY_2)
        {
            keys[i] = '2';
        }
        else if(i == KEY_3)
        {
            keys[i] = '3';
        }
        else if(i == KEY_4)
        {
            keys[i] = '4';
        }
        else if(i == KEY_5)
        {
            keys[i] = '5';
        }
        else if(i == KEY_6)
        {
            keys[i] = '6';
        }
        else if(i == KEY_7)
        {
            keys[i] = '7';
        }
        else if(i == KEY_8)
        {
            keys[i] = '8';
        }
        else if(i == KEY_9)
        {
            keys[i] = '9';
        }
        else if(i == KEY_A)
        {
            keys[i] = 'a';
        }
        else if(i == KEY_B)
        {
            keys[i] = 'b';
        }
        else if(i == KEY_C)
        {
            keys[i] = 'c';
        }
        else if(i == KEY_D)
        {
            keys[i] = 'd';
        }
        else if(i == KEY_E)
        {
            keys[i] = 'e';
        }
        else if(i == KEY_F)
        {
            keys[i] = 'f';
        }
        else if(i == KEY_G)
        {
            keys[i] = 'g';
        }
        else if(i == KEY_H)
        {
            keys[i] = 'h';
        }
        else if(i == KEY_I)
        {
            keys[i] = 'i';
        }
        else if (i == KEY_J)
        {
            keys[i] = 'j';
        }
        else if(i == KEY_K)
        {
            keys[i] = 'k';
        }
        else if(i == KEY_L)
        {
            keys[i] = 'l';
        }
        else if(i == KEY_M)
        {
            keys[i] = 'm';
        }
        else if(i == KEY_N)
        {
            keys[i] = 'n';
        }
        else if(i == KEY_O)
        {
            keys[i] = 'o';
        }
        else if(i == KEY_P)
        {
            keys[i] = 'p';
        }
        else if(i == KEY_Q)
        {
            keys[i] = 'q';
        }
        else if(i == KEY_R)
        {
            keys[i] = 'r';
        }
        else if (i == KEY_S)
        {
            keys[i] = 's';
        }
        else if(i == KEY_T)
        {
            keys[i] = 't';
        }
        else if(i == KEY_U)
        {
            keys[i] = 'u';
        }
        else if(i == KEY_V)
        {
            keys[i] = 'v';
        }
        else if(i == KEY_W)
        {
            keys[i] = 'w';
        }
        else if(i == KEY_X)
        {
            keys[i] = 'x';
        }
        else if(i == KEY_Y)
        {
            keys[i] = 'y';
        }
        else if(i == KEY_Z)
        {
            keys[i] = 'z';
        }
        else if(i == KEY_SPACE)
        {
            keys[i] = ' ';
        }
        else 
        {
            keys[i] = 0;
        }
        
        
    }
    
}

uint8_t PS2_GetKeyboardKey()
{
    uint8_t key = inb(0x60);
    while (inb(0x60) == key)
    {
        /* code */
    }
    return key;
}