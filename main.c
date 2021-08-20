#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>

#include "heap.h"
#include "heap_max.h"
#include "heap_min.h"
#include "heapsort.h"
#include "benchmark.h"

bool check_heap_max(int *array, int size) {
	for (int i = 1; i < size; ++i) {
		if (array[i] > array[(i - 1) / 2])
			return false;
	}
	return true;
}

bool check_heap_min(int *array, int size) {
	for (int i = 1; i < size; ++i) {
		if (array[i] < array[(i - 1) / 2])
			return false;
	}
	return true;
}

int input_int(char *text) {
	int result, n;

	do {
		printf("%s", text);
		n = scanf("%d", &result);
		if (!n) scanf("%*[^\n]");
		getchar();
	} while (!n);

	return result;
}

int main() {
	srand(time(NULL));

	char choice;
	int *array = NULL, size = 0;
	do {
		if (size > 0) {
			printf("The current array (size %d) is:\n", size);
			for (int i = 0; i < size; ++i)
				printf("%d ", array[i]);
			printf("\n\n");
		} else {
			printf("The current array is empty.\n\n");
		}

		int n;
		do {
			printf("Choose an option amongst:\n");
			printf("0. Initialize with a random array\n");
			printf("1. Enter an array of numbers\n");
			printf("2. Check if the array is a heap\n");
			printf("3. Convert the array into a heap-max\n");
			printf("4. Convert the array into a heap-min\n");
			printf("5. Shuffle the array randomly\n");
			printf("6. Pop the root of the heap\n");
			printf("7. Sort the array in ascending order\n");
			printf("8. Sort the array in descending order\n");
			printf("9. Compare sorting algorithms' efficiency\n");
			printf("Q. Quit\n");
			n = scanf("%c", &choice);
			if (!n) scanf("%*[^\n]");
			getchar();
		} while (!n);

		choice = toupper(choice);
		switch (choice) {
		case '0':
			{
				do {
					size = input_int("Please enter a number of integers for the array: ");
				} while (size < 0);

				if (array != NULL)
					free(array);

				if (size > 0) {
					array = malloc(sizeof(int) * size);

					int min = input_int("Please enter the minimum bound for the integers in the array: ");

					int max;
					do {
						max = input_int("Please enter the maximum bound for the integers in the array: ");
					} while (max <= min);

					for (int i = 0; i < size; ++i)
						array[i] = random() % (max - min + 1) + min;

					printf("Successfully filled the array with %d random values between %d and %d.\n", size, min, max);
				} else {
					array = NULL;
					printf("Successfully cleared the array.\n");
				}
			}
			break;

		case '1':
			{
				int capacity;
				do {
					capacity = input_int("Please enter a number of integers (max) for the array: ");
				} while (capacity <= 0);

				if (array != NULL)
					free(array);

				if (capacity > 0) {
					array = malloc(sizeof(int) * capacity);

					printf("Please enter %d integers at most (type a non-number to end prematurely):\n", capacity);
					size = 0;
					do {
						n = scanf("%d", &array[size++]);
						if (!n) scanf("%*[^\n]");
						getchar();
					} while (n && size < capacity);

					printf("Successfully stored the provided array.\n");
				} else {
					size = 0;
					array = NULL;
					printf("Successfully cleared the array.\n");
				}
			}
			break;

		case '2':
			if (check_heap_max(array, size)) {
				if (check_heap_min(array, size)) {
					printf("This array is both a heap max and a heap min (constant).\n");
				} else {
					printf("This array is a heap max.\n");
				}
			} else if (check_heap_min(array, size)) {
				printf("This array is a heap min.\n");
			} else {
				printf("This array is neither a heap max nor a heap min.\n");
			}
			break;

		case '3':
			if (!check_heap_max(array, size)) {
				Heap heap;
				heap.capacity = size;
				heap.size = 1;
				heap.data = array;

				while (heap.size < size)
					heap_max_propagate_top(&heap, heap.size++);
				printf("Successfully converted this array into a heap max.\n");
			} else {
				printf("This array is already a heap max.\n");
			}
			break;

		case '4':
			if (!check_heap_min(array, size)) {
				Heap heap;
				heap.capacity = size;
				heap.size = 1;
				heap.data = array;

				while (heap.size < size)
					heap_min_propagate_top(&heap, heap.size++);
				printf("Successfully converted this array into a heap min.\n");
			} else {
				printf("This array is already a heap min.\n");
			}
			break;

		case '5':
			for (int i = size - 1; i > 0; --i) {
				int j = random() % (i + 1);

				int value = array[i];
				array[i] = array[j];
				array[j] = value;
			}
			printf("Successfully shuffled the array randomly.\n");
			break;

		case '6':
			if (check_heap_max(array, size)) {
				Heap heap;
				heap.capacity = size;
				heap.size = size;
				heap.data = array;

				if (heap_max_pop(&heap)) {
					printf("Successfully popped the root.\n");
				} else {
					printf("No value to be popped.\n");
				}
				size = heap.size;
			} else if (check_heap_min(array, size)) {
				Heap heap;
				heap.capacity = size;
				heap.size = size;
				heap.data = array;

				if (heap_min_pop(&heap)) {
					printf("Successfully popped the root.\n");
				} else {
					printf("No value to be popped.\n");
				}
				size = heap.size;
			} else {
				printf("This array is neither a heap max nor a heap min.\n");
			}
			break;

		case '7':
			inplace_heapsort_ascending(array, size);
			printf("Successfully sorted the array in ascending order.\n");
			break;

		case '8':
			inplace_heapsort_descending(array, size);
			printf("Successfully sorted the array in descending order.\n");
			break;

		case '9':
			benchmark();
			break;

		case 'Q':
		default:
			continue;
		}

		sleep(2);
		printf("\n");
	} while (choice != 'Q');

	return 0;
}
