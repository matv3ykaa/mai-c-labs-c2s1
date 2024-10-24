#ifndef _TASK2_H_
#define _TASK2_H_

#include <stdlib.h>

typedef enum {
    SUCCESS,
    INPUT_ERROR,
    MEMORY_ERROR,
    OVERFLOW_ERROR
} status;

// Функции для вычислений
status geometric_mean(double *res, int count, ...);
status fast_pow(double base, int degree, double *res);

#endif
