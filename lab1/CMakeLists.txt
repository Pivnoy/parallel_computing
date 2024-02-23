cmake_minimum_required(VERSION 3.16)
project(lab1 C)

set(CMAKE_C_COMPILER gcc)

option(TASK1 "Первое задание" OFF)
option(TASK2 "Первое задание" OFF)

if (TASK1)
    set(CMAKE_C_FLAGS "-O3 -Wall -Werror")
    message("-- Current compiler flags CMAKE_C_FLAGS are: ${CMAKE_C_FLAGS}")
endif ()
unset(TASK1 CACHE)

set(K "0" CACHE STRING "Кол-во циклов")
message("current ${K}")

if (TASK2)
    set(CMAKE_C_FLAGS "-O3 -Wall -Werror -floop-parallelize-all -ftree-parallelize-loops=${K}")
    message("-- Current compiler flags CMAKE_C_FLAGS are: ${CMAKE_C_FLAGS}")
endif()
unset(TASK2 CACHE)


include_directories(lab1 include)

add_compile_options(-Wall -Wextra -Wpedantic)
add_executable(lab1 main.c src/array.c src/math_func.c)
target_link_libraries(lab1 m)