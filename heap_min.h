#ifndef HEAP_MIN_H
#define HEAP_MIN_H

#include <stdbool.h>

#include "heap.h"

void heap_min_propagate_top(Heap *heap, int position);
void heap_min_propagate_bottom(Heap *heap, int position);

bool heap_min_add(Heap *heap, int value);
bool heap_min_pop(Heap *heap);

#endif
