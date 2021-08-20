#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "benchmark.h"
#include "benchmark_sorts.h"

void display_benchmark(Benchmark benchmark, char *title) {
	printf("Benchmark for the %s sorting algorithm:\n", title);
	printf("Speed:\t\t\t%.2f sorts per second\n", benchmark.runs / benchmark.elapsed);
	printf("Average time:\t\t%.6f ms\n", benchmark.elapsed * 1000 / benchmark.runs);
	printf("Average comparisons:\t%lld\n", benchmark.comparisons / benchmark.runs);
	printf("Average operations:\t%lld\n", benchmark.operations / benchmark.runs);
	printf("Sampled on %d runs.\n", benchmark.runs);
}

void fill_arrays(int **arrays, int max_runs, int size) {
	for (int i = 0; i < max_runs; ++i) {
		if (BENCHMARK_MAX_VAL > BENCHMARK_MIN_VAL) {
			for (int j = 0; j < size; ++j)
				arrays[i][j] = rand() % (BENCHMARK_MAX_VAL - BENCHMARK_MIN_VAL + 1) + BENCHMARK_MIN_VAL;
		} else {
			memset(arrays[i], BENCHMARK_MIN_VAL, sizeof(int) * size);
		}
	}
}

void benchmark() {
	int size = BENCHMARK_SIZE;
	int max_runs = BENCHMARK_OPERATIONS / (size * log(size) / log(2));

	int **arrays = malloc(sizeof(int *) * max_runs);
	for (int i = 0; i < max_runs; ++i)
		arrays[i] = malloc(sizeof(int) * size);

	fill_arrays(arrays, max_runs, size);
	printf("Testing %s on arrays of size %d...\n", "Heap Sort", size);
	display_benchmark(benchmark_heap_sort(arrays, max_runs, size), "Heap Sort");

	fill_arrays(arrays, max_runs, size);
	printf("\nTesting %s on arrays of size %d...\n", "Counting Sort", size);
	display_benchmark(benchmark_counting_sort(arrays, max_runs, size), "Counting Sort");

	fill_arrays(arrays, max_runs, size);
	printf("\nTesting %s on arrays of size %d...\n", "Quick Sort", size);
	display_benchmark(benchmark_quick_sort(arrays, max_runs, size), "Quick Sort");

	fill_arrays(arrays, max_runs, size);
	printf("\nTesting %s on arrays of size %d...\n", "Merge Sort", size);
	display_benchmark(benchmark_merge_sort(arrays, max_runs, size), "Merge Sort");

	if (size > 10000) size = 10000;
	fill_arrays(arrays, max_runs, size);
	printf("\nTesting %s on arrays of size %d...\n", "Insertion Sort", size);
	display_benchmark(benchmark_insertion_sort(arrays, max_runs, size), "Insertion Sort");

	fill_arrays(arrays, max_runs, size);
	printf("\nTesting %s on arrays of size %d...\n", "Selection Sort", size);
	display_benchmark(benchmark_selection_sort(arrays, max_runs, size), "Selection Sort");

	fill_arrays(arrays, max_runs, size);
	printf("\nTesting %s on arrays of size %d...\n", "Bubble Sort", size);
	display_benchmark(benchmark_bubble_sort(arrays, max_runs, size), "Bubble Sort");

	if (size > 100) size = 100;
	fill_arrays(arrays, max_runs, size);
	printf("\nTesting %s on arrays of size %d...\n", "Slow Sort", size);
	display_benchmark(benchmark_slow_sort(arrays, max_runs, size), "Slow Sort");

	if (size > 10) size = 10;
	fill_arrays(arrays, max_runs, size);
	printf("\nTesting %s on arrays of size %d...\n", "Bogo Sort", size);
	display_benchmark(benchmark_bogo_sort(arrays, max_runs, size), "Bogo Sort");

	for (int i = 0; i < max_runs; ++i)
		free(arrays[i]);
	free(arrays);
}

Benchmark benchmark_heap_sort(int **arrays, int max_runs, int size) {
	Benchmark benchmark;
	benchmark.runs = 0;
	benchmark.comparisons = 0;
	benchmark.operations = 0;

	clock_t start = clock();
	do {
		heap_sort(arrays[benchmark.runs], size, &benchmark);

		benchmark.elapsed = (double) (clock() - start) / CLOCKS_PER_SEC;
	} while (++benchmark.runs < max_runs && benchmark.elapsed < BENCHMARK_LENGTH);

	return benchmark;
}

Benchmark benchmark_counting_sort(int **arrays, int max_runs, int size) {
	Benchmark benchmark;
	benchmark.runs = 0;
	benchmark.comparisons = 0;
	benchmark.operations = 0;

	clock_t start = clock();
	do {
		counting_sort(arrays[benchmark.runs], size, &benchmark);

		benchmark.elapsed = (double) (clock() - start) / CLOCKS_PER_SEC;
	} while (++benchmark.runs < max_runs && benchmark.elapsed < BENCHMARK_LENGTH);

	return benchmark;
}

Benchmark benchmark_quick_sort(int **arrays, int max_runs, int size) {
	Benchmark benchmark;
	benchmark.runs = 0;
	benchmark.comparisons = 0;
	benchmark.operations = 0;

	clock_t start = clock();
	do {
		quick_sort(arrays[benchmark.runs], size, &benchmark);

		benchmark.elapsed = (double) (clock() - start) / CLOCKS_PER_SEC;
	} while (++benchmark.runs < max_runs && benchmark.elapsed < BENCHMARK_LENGTH);

	return benchmark;
}

Benchmark benchmark_merge_sort(int **arrays, int max_runs, int size) {
	Benchmark benchmark;
	benchmark.runs = 0;
	benchmark.comparisons = 0;
	benchmark.operations = 0;

	clock_t start = clock();
	do {
		merge_sort(arrays[benchmark.runs], size, &benchmark);

		benchmark.elapsed = (double) (clock() - start) / CLOCKS_PER_SEC;
	} while (++benchmark.runs < max_runs && benchmark.elapsed < BENCHMARK_LENGTH);

	return benchmark;
}

Benchmark benchmark_bubble_sort(int **arrays, int max_runs, int size) {
	Benchmark benchmark;
	benchmark.runs = 0;
	benchmark.comparisons = 0;
	benchmark.operations = 0;

	clock_t start = clock();
	do {
		bubble_sort(arrays[benchmark.runs], size, &benchmark);

		benchmark.elapsed = (double) (clock() - start) / CLOCKS_PER_SEC;
	} while (++benchmark.runs < max_runs && benchmark.elapsed < BENCHMARK_LENGTH);

	return benchmark;
}

Benchmark benchmark_insertion_sort(int **arrays, int max_runs, int size) {
	Benchmark benchmark;
	benchmark.runs = 0;
	benchmark.comparisons = 0;
	benchmark.operations = 0;

	clock_t start = clock();
	do {
		insertion_sort(arrays[benchmark.runs], size, &benchmark);

		benchmark.elapsed = (double) (clock() - start) / CLOCKS_PER_SEC;
	} while (++benchmark.runs < max_runs && benchmark.elapsed < BENCHMARK_LENGTH);

	return benchmark;
}

Benchmark benchmark_selection_sort(int **arrays, int max_runs, int size) {
	Benchmark benchmark;
	benchmark.runs = 0;
	benchmark.comparisons = 0;
	benchmark.operations = 0;

	clock_t start = clock();
	do {
		selection_sort(arrays[benchmark.runs], size, &benchmark);

		benchmark.elapsed = (double) (clock() - start) / CLOCKS_PER_SEC;
	} while (++benchmark.runs < max_runs && benchmark.elapsed < BENCHMARK_LENGTH);

	return benchmark;
}

Benchmark benchmark_slow_sort(int **arrays, int max_runs, int size) {
	Benchmark benchmark;
	benchmark.runs = 0;
	benchmark.comparisons = 0;
	benchmark.operations = 0;

	clock_t start = clock();
	do {
		slow_sort(arrays[benchmark.runs], size, &benchmark);

		benchmark.elapsed = (double) (clock() - start) / CLOCKS_PER_SEC;
	} while (++benchmark.runs < max_runs && benchmark.elapsed < BENCHMARK_LENGTH);

	return benchmark;
}

Benchmark benchmark_bogo_sort(int **arrays, int max_runs, int size) {
	Benchmark benchmark;
	benchmark.runs = 0;
	benchmark.comparisons = 0;
	benchmark.operations = 0;

	clock_t start = clock();
	do {
		bogo_sort(arrays[benchmark.runs], size, &benchmark);

		benchmark.elapsed = (double) (clock() - start) / CLOCKS_PER_SEC;
	} while (++benchmark.runs < max_runs && benchmark.elapsed < BENCHMARK_LENGTH);

	return benchmark;
}
