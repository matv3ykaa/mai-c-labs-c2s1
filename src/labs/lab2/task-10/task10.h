#ifndef _TASK10_H_
#define _TASK10_H_

#include <stdlib.h>

// Статусы выполнения программы
typedef enum {
    SUCCESS,
    INPUT_ERROR,
    MEMORY_ERROR
} status;

// Функция переразложения многочлена
status polynomial_rearrange(double epsilon, double a, int degree, double *coefficients, double **result);

#endif
