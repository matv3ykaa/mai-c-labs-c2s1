#ifndef _TASK4_H_
#define _TASK4_H_

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    SUCCESS,
    MEMORY_ERROR,
    INPUT_ERROR,
    NOT_CONVEX
} status;

// Проверка выпуклости многоугольника
status check_convex_polygon(int vertex_count, const double *x, const double *y);

// Вычисление значения многочлена в точке
status evaluate_polynomial(double x_value, int degree, const double *coefficients, double *result);

#endif
