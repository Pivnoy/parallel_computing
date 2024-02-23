#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "math_func.h"


struct array * new_array(size_t size);

void delete(struct array * arr);

void print(struct array * arr);

void fill(struct array * arr, int maxValue, int minValue);

void push(struct array * arr, float value);

void map(struct array * arr, float (*compute_func)(float));

void map_2(struct array * arr, float (*compute_func)(float, float));

void merge(struct array * arr1, struct array * arr2);

void sort(struct array * arr);

float min_sort(struct array * arr);

float reduce(struct array * arr, float minimum);