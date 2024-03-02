#include "array.h"

__thread unsigned int seed = 0;

struct array {
    size_t current;
    size_t size;
    float * restrict arr;
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

void fill(struct array * arr, int maxValue, int minValue){
    if (arr != NULL) {
        if (arr->arr != NULL) {
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

void map(struct array * arr, float (*compute_func)(float)) {
    if (arr != NULL && compute_func != NULL) {
        #pragma omp parallel for default(none) shared(arr, compute_func) schedule(auto)
        for (size_t i = 0; i < arr->size; ++i) {
            arr->arr[i] = compute_func(arr->arr[i]);
        }
    }
}

void delete(struct array * arr) {
    if (arr != NULL) {
        if (arr->arr != NULL) {
            free(arr->arr);
            arr->arr = NULL;
        }
        free(arr);
        arr = NULL;
    }
}

struct array * copy(struct array * arr) {
    if (arr != NULL) {
        struct array * copy = new_array(arr->size);
        if (copy != NULL) {
            for (size_t i = 0; i < copy->size; ++i) {
                copy->arr[i] = arr->arr[i];
            }
            return copy;
        }
        delete(copy);
    }
    return NULL;
}

void map_2(struct array * arr, float (*compute_func)(float, float)){
    struct array * m2_arr = copy(arr);
    if (m2_arr != NULL) {
        for (size_t i = 0; i < arr->size; ++i) {
            float m2i_prev = i == 0 ? 0 : m2_arr->arr[i - 1];
            arr->arr[i] = compute_func(m2_arr->arr[i], m2i_prev);
        }
    }
}

void merge(struct array * arr1, struct array * arr2) {
    if (arr1 != NULL && arr2 != NULL) {
        for (size_t i = 0; i < arr2->size; ++i) {
            arr2->arr[i] = max(arr1->arr[i],arr2->arr[i]);
        }
    }
}

void sort(struct array * arr) {
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

float min_sort(struct array * arr){
    if (arr != NULL) {
        return arr->arr[0];
    }
    return -20;
}

float reduce(struct array * arr, float minimum){
    if (arr != NULL) {
        float sum = 0;
        for (size_t i = 0; i < arr->size; ++i) {
            float value = arr->arr[i];
            if (value != 0 && value != NAN) {
                if ((int)(value / minimum) == 0) {
                    sum += sin(value);
                }
            }
        }
        return sum;
    }
    return -1;
}
