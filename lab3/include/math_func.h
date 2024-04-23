#pragma once

#include <math.h>

#include "math.h"

/*
 *  X = 1 + ((A mod 47) mod B),
 * Вариант
 * 1) X = 1 + ((392 mod 47) mod 7) = 1 + (16 mod 7) = 3 -> Гиперболический тангенс с последующим уменьшением на 1
 * 2) X = 1 + ((392 mod 47) mod 8) = 1 + (16 mod 8) = 1 -> Модуль синуса (т.е. M2[i] = |sin(M2[i] + M2[i-1])|)
 * 3) X = 1 + ((392 mod 47) mod 6) = 1 + (16 mod 6) = 4 -> Выбор большего (т.е. M2[i] = max(M1[i],M2[i])))
 * 4) X = 1 + ((392 mod 47) mod 6) = 1 + (16 mod 6) = 4 -> Гномья сортировка (Gnome sort)
 * */

float to_sin(float x);

float max(float value1, float value2);

float htan_minus_one(float value);

float abs_sin(float value1, float value2);
