#ifndef BENCHMARK_SORTS_H
#define BENCHMARK_SORTS_H

#include "benchmark.h"

void heap_sort(int *array, int size, Benchmark *benchmark);
void counting_sort(int *array, int size, Benchmark *benchmark);
void quick_sort(int *array, int size, Benchmark *benchmark);
void merge_sort(int *array, int size, Benchmark *benchmark);
void bubble_sort(int *array, int size, Benchmark *benchmark);
void insertion_sort(int *array, int size, Benchmark *benchmark);
void selection_sort(int *array, int size, Benchmark *benchmark);
void slow_sort(int *array, int size, Benchmark *benchmark);
void bogo_sort(int *array, int size, Benchmark *benchmark);

#endif
