
all:
	clang-18 -O3 -Wall -Werror -pedantic -Wextra -mllvm -polly -mllvm -polly-parallel -mllvm -polly-omp-backend=LLVM -mllvm -polly-num-threads=6 -o lab1 lab1.c src/array.c src/math_func.c -Iinclude -lm


lab11:
	clang-18 -O3 -Wall -Werror -o lab1 lab1.c src/array.c src/math_func.c -Iinclude -lm
