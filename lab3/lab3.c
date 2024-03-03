#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "array.h"
#include "math_func.h"

#define A 392
#define ITERATIONS 1

int main(int argc, char *argv[]) {
    if (argc < 2) return -1;

#ifdef _OPENMP
    omp_set_num_threads(16);
#endif


    const int N = atoi(argv[1]);
#ifdef _OPENMP
    double start_time, end_time;
    start_time = omp_get_wtime();
#else
    struct timeval T1, T2;
    gettimeofday(&T1, NULL);
#endif
    for (int i = 0; i < ITERATIONS; i++) {

        srand(time(NULL));

        // 1. Create
        struct array * arr = new_array(N);
        struct array * arr2 = new_array(N / 2);

        fill(arr, A, 1);
        map(arr, to_sin);
        fill(arr2, A * 10, A);

        // 2. Map
        map(arr, htan_minus_one);

        map_2(arr2, abs_sin);

        // 3. Merge
        merge(arr, arr2, max);

        // 4. Sort
#ifdef _OPENMP
        parallel_sort(arr2);
#else
        sort(arr2);
#endif

        // 5. Reduce
        float min = min_sort(arr2);
        // float result = reduce(arr2,min);
        reduce(arr2,min);
        // printf("Result: %f\n", result);

        delete(arr);
        delete(arr2);
    }

#ifdef _OPENMP
    end_time = omp_get_wtime();
    printf(
            "N=%d. Milliseconds passed: %f\n",
            N,
            (end_time - start_time) * 1000
    );
#else
    gettimeofday(&T2, NULL);
    printf(
            "N=%d. Milliseconds passed: %ld\n",
            N,
            1000 * (T2.tv_sec - T1.tv_sec) + (T2.tv_usec - T1.tv_usec) / 1000
    );
#endif
    return 0;
}
