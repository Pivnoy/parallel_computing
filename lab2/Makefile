CHUNK_SIZE=16
SCHED=dynamic

all:
	clang  -Wall -Werror -o lab2 lab2.c src/array.c src/math_func.c -Iinclude -I/opt/homebrew/opt/libomp/include  -lm -L/opt/homebrew/opt/libomp/lib

omp:
	clang  -Wall -Werror -pedantic -DCHUNK_SIZE=$(CHUNK_SIZE) -DSCHED=$(SCHED) -o lab2-mp lab2.c src/array.c src/math_func.c -Iinclude -lm -fopenmp -lomp

clear:
	rm -rf lab2
	rm -rf lab2-mp