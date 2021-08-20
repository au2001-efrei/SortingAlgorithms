#ifndef HEAP_MAX_H
#define HEAP_MAX_H

#include <stdbool.h>

#include "heap.h"

void heap_max_propagate_top(Heap *heap, int position);
void heap_max_propagate_bottom(Heap *heap, int position);

bool heap_max_add(Heap *heap, int value);
bool heap_max_pop(Heap *heap);

#endif
