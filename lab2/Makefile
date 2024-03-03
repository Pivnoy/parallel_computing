CHUNK_SIZE=1
SCHED_ALG=guided

all:
	clang  -Wall -Werror -o lab2 lab2.c src/array.c src/math_func.c -Iinclude -I/opt/homebrew/opt/libomp/include  -lm -L/opt/homebrew/opt/libomp/lib

no-omp:
	clang-19 -Wall -Werror -pedantic -o lab2-no-omp lab2.c src/array.c src/math_func.c -Iinclude -lm

omp:
	clang-19 -O3 -Ofast -Wall -Werror -pedantic -o lab2-omp lab2.c src/array.c src/math_func.c -Iinclude -lm -fopenmp -lomp

omp-with-params:
	clang-19 -O3 -Wall -Werror -pedantic -DCHUNK_SIZE=$(CHUNK_SIZE) -DSCHED_ALG=$(SCHED_ALG) -o lab2-omp-params lab2.c src/array.c src/math_func.c -Iinclude -lm -fopenmp -lomp

clear:
	rm -rf lab2-no-omp
	rm -rf lab2-omp
	rm -rf lab2-omp-params