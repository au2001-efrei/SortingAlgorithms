#ifndef BENCHMARK_H
#define BENCHMARK_H

#define BENCHMARK_MIN_VAL 0
#define BENCHMARK_MAX_VAL 99999
#define BENCHMARK_SIZE (BENCHMARK_MAX_VAL - BENCHMARK_MIN_VAL + 1)
#define BENCHMARK_OPERATIONS 100000000
#define BENCHMARK_LENGTH 1.0

typedef struct {
	int runs;
	double elapsed;
	long long comparisons;
	long long operations;
} Benchmark;

void display_benchmark(Benchmark benchmark, char *title);
void benchmark();

Benchmark benchmark_heap_sort(int **arrays, int max_runs, int size);
Benchmark benchmark_counting_sort(int **arrays, int max_runs, int size);
Benchmark benchmark_quick_sort(int **arrays, int max_runs, int size);
Benchmark benchmark_merge_sort(int **arrays, int max_runs, int size);
Benchmark benchmark_bubble_sort(int **arrays, int max_runs, int size);
Benchmark benchmark_insertion_sort(int **arrays, int max_runs, int size);
Benchmark benchmark_selection_sort(int **arrays, int max_runs, int size);
Benchmark benchmark_slow_sort(int **arrays, int max_runs, int size);
Benchmark benchmark_bogo_sort(int **arrays, int max_runs, int size);

#endif
