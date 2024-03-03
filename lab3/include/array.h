#pragma once

#if defined(_OPENMP)
    #include <omp.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "math_func.h"


struct array * new_array(size_t size);

void delete(struct array *restrict arr);

void print(struct array *restrict arr);

void fill(struct array *restrict arr, int maxValue, int minValue);

void map(struct array *restrict arr, float (*compute_func)(float));

void map_2(struct array *restrict arr, float (*compute_func)(float, float));

void merge(struct array *restrict arr1, struct array *restrict arr2, float (*compute_func)(float, float));

void sort(struct array *restrict arr);

float min_sort(struct array *restrict arr);

float reduce(struct array *restrict arr, float minimum);

void push(struct array *restrict arr, float value);

void parallel_sort(struct array *restrict arr);

