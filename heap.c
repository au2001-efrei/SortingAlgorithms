#include <stdlib.h>
#include <limits.h>

#include "heap.h"

Heap create_heap(int capacity) {
	Heap heap;
	heap.capacity = capacity;
	heap.size = 0;
	heap.data = malloc(sizeof(int) * capacity);
	return heap;
}

int heap_get_top(Heap heap) {
	if (heap.size <= 0)
		return INT_MIN;
	return heap.data[0];
}
