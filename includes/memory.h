#pragma once
#include <stdint.h>
#include <stddef.h>

void asmmemcpy(void *d, const void *s, size_t n);
void memset(void* start, uint64_t value, uint64_t num);

