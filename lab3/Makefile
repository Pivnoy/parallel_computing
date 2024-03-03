PERF = -O3 -Ofast
MATH = -ffinite-math-only -freciprocal-math -frounding-math

no-omp:
	clang-19 $(PERF) $(MATH) -Wall -Werror -pedantic -o lab3-no-omp lab3.c src/array.c src/math_func.c -Iinclude -lm

omp:
	clang-19 $(PERF) $(MATH) -Wall -Werror -pedantic -o lab3-omp lab3.c src/array.c src/math_func.c -Iinclude -lm -fopenmp -lomp

clear:
	rm -rf lab3-no-omp
	rm -rf lab3-omp
	rm -rf lab3-omp-params