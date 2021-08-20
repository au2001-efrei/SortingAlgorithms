#ifndef HEAP_H
#define HEAP_H

typedef struct {
	int capacity, size;
	int *data;
} Heap;

Heap create_heap(int capacity);

int heap_get_top(Heap heap);

#endif
