#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "benchmark_sorts.h"

void heap_sort(int *array, int size, Benchmark *benchmark) {
	for (int i = 1; i < size; ++i) {
		int j = i;

		while (j > 0 && array[j] > array[(j - 1) / 2]) {
			int value = array[j];
			array[j] = array[(j - 1) / 2];
			array[(j - 1) / 2] = value;
			j = (j - 1) / 2;
			++benchmark->operations;
			++benchmark->comparisons;
		}
	}

	while (size > 1) {
		--size;
		int value = array[size];
		array[size] = array[0];
		array[0] = value;
		++benchmark->operations;

		int j = 0;
		while (j < size) {
			int k = j;
			++benchmark->comparisons;
			if (j * 2 + 1 < size && array[j * 2 + 1] > array[k])
				k = j * 2 + 1;
			++benchmark->comparisons;
			if (j * 2 + 2 < size && array[j * 2 + 2] > array[k])
				k = j * 2 + 2;

			if (k == j) break;

			int value = array[j];
			array[j] = array[k];
			array[k] = value;
			++benchmark->operations;
			j = k;
		}
	}
}

void counting_sort(int *array, int size, Benchmark *benchmark) {
	int *counts = malloc(sizeof(int) * (BENCHMARK_MAX_VAL - BENCHMARK_MIN_VAL + 1));
	memset(counts, 0, sizeof(int) * (BENCHMARK_MAX_VAL - BENCHMARK_MIN_VAL + 1));
	++benchmark->operations;

	for (int i = 0; i < size; ++i) {
		++counts[array[i] - BENCHMARK_MIN_VAL];
		++benchmark->comparisons;
	}

	int n = 0;
	for (int i = BENCHMARK_MIN_VAL; i <= BENCHMARK_MAX_VAL; ++i) {
		for (int j = 0; j < counts[i - BENCHMARK_MIN_VAL]; ++j) {
			array[n] = i;
			++benchmark->operations;
			++n;
		}
	}

	free(counts);
}

void quick_sort(int* array, int size, Benchmark *benchmark) {
	if (size <= 1) return;

	int pivot = array[size - 1];
	int index = 0;

	for (int j = 0; j < size - 1; ++j) {
		++benchmark->comparisons;
		if (array[j] <= pivot) {
			int value = array[index];
			array[index] = array[j];
			array[j] = value;
			++benchmark->operations;
			++index;
		}
	}

	array[size - 1] = array[index];
	array[index] = pivot;
	++benchmark->operations;

	quick_sort(array, index, benchmark);
	quick_sort(array + index, size - index - 1, benchmark);
}

void merge_sort(int *array, int size, Benchmark *benchmark) {
	if (size <= 1) return;

	int m = size / 2;
	merge_sort(array, m, benchmark);
	merge_sort(array + m, size - m, benchmark);

	int *copy = malloc(sizeof(int) * size);
	memcpy(copy, array, sizeof(int) * size);
	++benchmark->operations;

	int i = 0, j = 0;
	while (i < m && j < size - m) {
		++benchmark->comparisons;
		if (copy[i] <= copy[m + j]) {
			array[i + j] = copy[i];
			++benchmark->operations;
			++i;
		} else {
			array[i + j] = copy[m + j];
			++benchmark->operations;
			++j;
		}
	}

	while (i < m) {
		array[i + j] = copy[i];
		++benchmark->operations;
		i++;
	}

	while (j < size - m) {
		array[i + j] = copy[m + j];
		++benchmark->operations;
		j++;
	}
}

void bubble_sort(int *array, int size, Benchmark *benchmark) {
	do {
		int n = 0;
		for (int i = 1; i < size; ++i) {
			++benchmark->comparisons;
			if (array[i - 1] > array[i]) {
				int value = array[i - 1];
				array[i - 1] = array[i];
				array[i] = value;
				++benchmark->operations;
				n = i;
			}
		}
		size = n;
	} while (size > 1);
}

void insertion_sort(int *array, int size, Benchmark *benchmark) {
	for (int i = 1; i < size; ++i) {
		int x = array[i];
		int j;
		++benchmark->comparisons;
		for (j = i - 1; j >= 0 && array[j] > x; --j) {
			array[j + 1] = array[j];
			++benchmark->operations;
			++benchmark->comparisons;
		}
		array[j + 1] = x;
	}
}

void selection_sort(int *array, int size, Benchmark *benchmark) {
	for (int i = 0; i < size - 1; ++i) {
		int min = i;
		for (int j = i + 1; j < size; ++j) {
			++benchmark->comparisons;
			if (array[j] < array[min])
				min = j;
		}

		if (min != i) {
			int value = array[min];
			array[min] = array[i];
			array[i] = value;
			++benchmark->operations;
		}
	}
}

void slow_sort(int *array, int size, Benchmark *benchmark) {
	if (size <= 1) return;

	int m = size / 2;
	slow_sort(array, m, benchmark);
	slow_sort(array + m, size - m, benchmark);

	++benchmark->comparisons;
	if (array[size - 1] < array[m - 1]) {
		int value = array[m - 1];
		array[m - 1] = array[size - 1];
		array[size - 1] = value;
		++benchmark->operations;
	}

	slow_sort(array, size - 1, benchmark);
}

void bogo_sort(int *array, int size, Benchmark *benchmark) {
	bool sorted;
	do {
		for (int i = size - 1; i > 0; --i) {
			int j = random() % (i + 1);

			int value = array[i];
			array[i] = array[j];
			array[j] = value;
			++benchmark->operations;
		}

		sorted = true;
		for (int i = 1; i < size; ++i) {
			++benchmark->comparisons;
			if (array[i] < array[i - 1]) {
				sorted = false;
				break;
			}
		}
	} while (!sorted);
}
