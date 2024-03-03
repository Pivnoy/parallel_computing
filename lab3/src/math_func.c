#include "math_func.h"

float to_sin(float x){
    return x / 1000 * -1;
}

float max(float value1, float value2){
    return value1 > value2 ? value1 : value2;
}

float htan_minus_one(float value) {
    return tanh(value) + 1;
}

float abs_sin(float value1, float value2){
    return fabs(sin(value1 + value2));
}
