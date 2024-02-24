#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "array.h"
#include "math_func.h"

#define A 392
#define ITERATIONS 100

int main(int argc, char *argv[]) {
    if (argc < 2) return -1;
    struct timeval T1, T2;
    const int N = atoi(argv[1]);
    gettimeofday(&T1, NULL);
    for (int i = 0; i < ITERATIONS; i++) {

        // 1. Create
        struct array *arr = new_array(N);
        struct array *arr2 = new_array(N / 2);

        fill(arr, A, 1);
        map(arr, to_sin);
        fill(arr2, A * 10, A);

        // 2. Map
        map(arr, htan_minus_one);

        map_2(arr2, abs_sin);

        // 3. Merge
        merge(arr, arr2);

        // 4. Sort
        sort(arr2);

        // 5. Reduce
        float min = min_sort(arr2);
        float result = reduce(arr2,min);
        printf("Result: %f\n", result);

        delete(arr);
        delete(arr2);
    }
    gettimeofday(&T2, NULL);
    printf(
            "N=%d. Milliseconds passed: %ld\n",
            N,
            1000 * (T2.tv_sec - T1.tv_sec) + (T2.tv_usec - T1.tv_usec) / 1000
    );
    return 0;
}
