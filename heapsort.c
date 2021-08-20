#include <stdio.h>
#include <stdlib.h>

#include "heap.h"
#include "heap_max.h"
#include "heap_min.h"
#include "heapsort.h"

int *heapsort_ascending(int *array, int size) {
	Heap heap = create_heap(size);

	for (int i = 0; i < size; ++i)
		heap_max_add(&heap, array[i]);

	// printf("Heap max of size %d:\n", heap.size);
	// for (int i = 0; i < heap.size; ++i)
	// 	printf("%d ", heap.data[i]);
	// printf("\n");

	int *sorted_array = malloc(sizeof(int) * size);
	for (int i = size - 1; i >= 0; --i) {
		sorted_array[i] = heap_get_top(heap);
		heap_max_pop(&heap);
	}

	// printf("Ascendingly sorted array:\n");
	// for (int i = 0; i < size; ++i)
	// 	printf("%d ", sorted_array[i]);
	// printf("\n");

	free(heap.data);
	return sorted_array;
}

void inplace_heapsort_ascending(int *array, int size) {
	Heap heap;
	heap.capacity = size;
	heap.size = 1;
	heap.data = array;

	while (heap.size < size)
		heap_max_propagate_top(&heap, heap.size++);

	// printf("Heap max of size %d:\n", heap.size);
	// for (int i = 0; i < heap.size; ++i)
	// 	printf("%d ", heap.data[i]);
	// printf("\n");

	for (int i = 0; i < size; ++i)
		heap_max_pop(&heap);

	// printf("Ascendingly sorted array:\n");
	// for (int i = 0; i < size; ++i)
	// 	printf("%d ", array[i]);
	// printf("\n");
}

int *heapsort_descending(int *array, int size) {
	Heap heap = create_heap(size);

	for (int i = 0; i < size; ++i)
		heap_min_add(&heap, array[i]);

	// printf("Heap min of size %d:\n", heap.size);
	// for (int i = 0; i < heap.size; ++i)
	// 	printf("%d ", heap.data[i]);
	// printf("\n");

	int *sorted_array = malloc(sizeof(int) * size);
	for (int i = size - 1; i >= 0; --i) {
		sorted_array[i] = heap_get_top(heap);
		heap_min_pop(&heap);
	}

	// printf("Descendingly sorted array:\n");
	// for (int i = 0; i < size; ++i)
	// 	printf("%d ", sorted_array[i]);
	// printf("\n");

	free(heap.data);
	return sorted_array;
}

void inplace_heapsort_descending(int *array, int size) {
	Heap heap;
	heap.capacity = size;
	heap.size = 1;
	heap.data = array;

	while (heap.size < size)
		heap_min_propagate_top(&heap, heap.size++);

	// printf("Heap min of size %d:\n", heap.size);
	// for (int i = 0; i < heap.size; ++i)
	// 	printf("%d ", heap.data[i]);
	// printf("\n");

	for (int i = 0; i < size; ++i)
		heap_min_pop(&heap);

	// printf("Descendingly sorted array:\n");
	// for (int i = 0; i < size; ++i)
	// 	printf("%d ", array[i]);
	// printf("\n");
}
