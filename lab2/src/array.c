#include "array.h"

__thread unsigned int seed = 0;

struct array {
    size_t current;
    size_t size;
    float * arr;
};

struct array * new_array(size_t size) {
    struct array * arr = (struct array *) malloc(sizeof(struct array));
    if (arr != NULL) {
        arr->size = size;
        arr->current = 0;
        arr->arr = (float *) malloc(sizeof(float) * size);
        if (arr->arr == NULL) {
            return NULL;
        }
        return arr;
    }
    return NULL;
}

void print(struct array * arr){
    if (arr != NULL) {
        for (size_t i = 0; i < arr->size; ++i) {
            printf("%f ", arr->arr[i]);
        }
        printf("\n");
    }
}

void fill(struct array * restrict arr, int maxValue, int minValue){
    if (arr != NULL) {
        if (arr->arr != NULL) {
            #ifdef _OPENMP
                #if defined(CHUNK_SIZE) && defined(SCHED_ALG)
                    #pragma omp parallel for default(none) shared(arr, maxValue, minValue) schedule(SCHED_ALG, CHUNK_SIZE)
                #else
                    #pragma omp parallel for default(none) shared(arr, maxValue, minValue) schedule(auto)
                #endif
            #endif
            for (unsigned long i = 0; i < arr->size; ++i) {
                seed = i;
                arr->arr[i] = (maxValue <= minValue || abs(maxValue) == abs(minValue)) ? 0 : minValue + rand_r(&seed) %
                                                                                                        ((maxValue +
                                                                                                          1) -
                                                                                                         minValue);
            }
        }
    }
}

void map(struct array * restrict arr, float (*compute_func)(float)) {
    if (arr != NULL && compute_func != NULL) {
        #ifdef _OPENMP
        #if defined(CHUNK_SIZE) && defined(SCHED_ALG)
            #pragma omp parallel for default(none) shared(arr, compute_func) schedule(SCHED_ALG, CHUNK_SIZE)
        #else
            #pragma omp parallel for default(none) shared(arr, compute_func) schedule(auto)
        #endif
        #endif
        for (size_t i = 0; i < arr->size; ++i) {
            arr->arr[i] = compute_func(arr->arr[i]);
        }
    }
}

void delete(struct array * restrict arr) {
    if (arr != NULL) {
        if (arr->arr != NULL) {
            free(arr->arr);
            arr->arr = NULL;
        }
        free(arr);
        arr = NULL;
    }
}

struct array * copy(struct array * restrict arr) {
    if (arr != NULL) {
        struct array * copy = new_array(arr->size);
        if (copy != NULL) {
            #ifdef _OPENMP
            #if defined(CHUNK_SIZE) && defined(SCHED_ALG)
                #pragma omp parallel for default(none) shared(arr, copy) schedule(SCHED_ALG, CHUNK_SIZE)
            #else
                #pragma omp parallel for default(none) shared(arr, copy) schedule(auto)
            #endif
            #endif
            for (size_t i = 0; i < copy->size; ++i) {
                copy->arr[i] = arr->arr[i];
            }
            return copy;
        }
        delete(copy);
    }
    return NULL;
}

void map_2(struct array * restrict arr, float (*compute_func)(float, float)){
    struct array * m2_arr = copy(arr);
    if (m2_arr != NULL) {
        #ifdef _OPENMP
        #if defined(CHUNK_SIZE) && defined(SCHED_ALG)
            #pragma omp parallel for default(none) shared(arr, m2_arr, compute_func) schedule(SCHED_ALG, CHUNK_SIZE)
        #else
            #pragma omp parallel for default(none) shared(arr, m2_arr, compute_func) schedule(auto)
        #endif
        #endif
        for (size_t i = 0; i < arr->size; ++i) {
            float m2i_prev = i == 0 ? 0 : m2_arr->arr[i - 1];
            arr->arr[i] = compute_func(m2_arr->arr[i], m2i_prev);
        }
        delete(m2_arr);
    }
}

void merge(struct array * restrict arr1, struct array * restrict arr2, float (*compute_func)(float, float)) {
    if (arr1 != NULL && arr2 != NULL) {
        #ifdef _OPENMP
        #if defined(CHUNK_SIZE) && defined(SCHED_ALG)
            #pragma omp parallel for default(none) shared(arr1, arr2, compute_func) schedule(SCHED_ALG, CHUNK_SIZE)
        #else
            #pragma omp parallel for default(none) shared(arr1, arr2, compute_func) schedule(auto)
        #endif
        #endif
        for (size_t i = 0; i < arr2->size; ++i) {
            arr2->arr[i] = compute_func(arr1->arr[i],arr2->arr[i]);
        }
    }
}

void sort(struct array * restrict arr) {
    if (arr != NULL) {
        while (arr->current < arr->size) {
            if (arr->current == 0 || arr->arr[arr->current] >= arr->arr[arr->current - 1]) {
                arr->current++;
            } else {
                float temp = arr->arr[arr->current];
                arr->arr[arr->current] = arr->arr[arr->current - 1];
                arr->arr[arr->current - 1] = temp;
                arr->current--;
            }
        }
    }
}

float min_sort(struct array * restrict arr){
    if (arr != NULL) {
        return arr->arr[0];
    }
    return -20;
}

float reduce(struct array * restrict arr, float minimum){
    if (arr != NULL) {
        float sum = 0;
        #ifdef _OPENMP
        #if defined(CHUNK_SIZE) && defined(SCHED_ALG)
            #pragma omp parallel for default(none) shared(arr, minimum) schedule(SCHED_ALG, CHUNK_SIZE) reduction(+:sum)
        #else
            #pragma omp parallel for default(none) shared(arr, minimum) schedule(auto) reduction(+:sum)
        #endif
        #endif
        for (size_t i = 0; i < arr->size; ++i) {
            float value = arr->arr[i];
            if (value != 0) {
                if ((int)(value / minimum) == 0) {
                    sum += sin(value);
                }
            }
        }
        return sum;
    }
    return -1;
}
