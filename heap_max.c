#include <stdbool.h>

#include "heap.h"
#include "heap_max.h"

void heap_max_propagate_top(Heap *heap, int position) {
	int parent = (position - 1) / 2;
	if (position <= 0 || heap->data[parent] >= heap->data[position])
		return;

	int value = heap->data[position];
	heap->data[position] = heap->data[parent];
	heap->data[parent] = value;

	heap_max_propagate_top(heap, parent);
}

void heap_max_propagate_bottom(Heap *heap, int position) {
	int child1 = position * 2 + 1, child2 = position * 2 + 2;
	bool invert1 = child1 < heap->size && heap->data[position] < heap->data[child1];
	bool invert2 = child2 < heap->size && heap->data[position] < heap->data[child2];

	if (!invert1 && !invert2)
		return;

	int value = heap->data[position];
	if (invert1 && (!invert2 || heap->data[child1] >= heap->data[child2])) {
		heap->data[position] = heap->data[child1];
		heap->data[child1] = value;

		heap_max_propagate_bottom(heap, child1);
	} else {
		heap->data[position] = heap->data[child2];
		heap->data[child2] = value;

		heap_max_propagate_bottom(heap, child2);
	}
}

bool heap_max_add(Heap *heap, int value) {
	if (heap->size >= heap->capacity)
		return false;

	heap->data[heap->size++] = value;

	heap_max_propagate_top(heap, heap->size - 1);
	return true;
}

bool heap_max_pop(Heap *heap) {
	if (heap->size <= 0)
		return false;

	--heap->size;

	if (heap->size > 0) {
		int value = heap->data[heap->size];
		heap->data[heap->size] = heap->data[0];
		heap->data[0] = value;
		heap_max_propagate_bottom(heap, 0);
	}

	return true;
}
