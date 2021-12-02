#include <stdint.h>
#include <stddef.h>
#include "../includes/memory.h"


void asmmemcpy(void *d, const void *s, size_t n) {
    uint64_t d0, d1, d2; 
    asm volatile(
        "rep ; movsq\n\t""movq %4,%%rcx\n\t""rep ; movsb\n\t": "=&c" (d0),                                                                                   
        "=&D" (d1),
        "=&S" (d2): "0" (n >> 3), 
        "g" (n & 7), 
        "1" (d),
        "2" (s): "memory"
    );  //not mine (found it on reddit: https://www.reddit.com/r/C_Programming/comments/ivoqhk/understanding_the_assembly_code_of_memcpy/)
}

__attribute__((optimize("-fno-tree-loop-distribute-patterns"))) void memset(void* start, uint64_t value, uint64_t num)  {
    if (num <= 8) {
        uint8_t* valPtr = (uint8_t*)&value;
        for (uint8_t* ptr = (uint8_t*)start; ptr < (uint8_t*)((uint64_t)start + num); ptr++) {
            *ptr = *valPtr;
            valPtr++;
        }
        return;
    }
    uint64_t proceedingBytes = num % 8;
    uint64_t newnum = num - proceedingBytes;

    for (uint64_t* ptr = (uint64_t*)start; ptr < (uint64_t*)((uint64_t)start + newnum); ptr++) {
        *ptr = value;
    }
    uint8_t* valPtr = (uint8_t*)&value;
    for (uint8_t* ptr = (uint8_t*)((uint64_t)start + newnum); ptr < (uint8_t*)((uint64_t)start + newnum); ptr++) {
        *ptr = *valPtr;
        valPtr++;
    }
};