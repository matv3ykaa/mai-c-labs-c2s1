#include "task2.h"
#include <stdarg.h>
#include <math.h>

// Проверка переполнения для вещественных чисел
static status check_overflow(double x) {
    if (isinf(x) || isnan(x)) {
        return OVERFLOW_ERROR;
    }
    return SUCCESS;
}

// Функция для вычисления среднего геометрического
status geometric_mean(double *res, int count, ...) {
    if (count < 1) {
        return INPUT_ERROR;  // Должно быть как минимум одно число
    }

    va_list args;
    va_start(args, count);
    *res = 1.0;
    double cur;
    for (int i = 0; i < count; ++i) {
        cur = va_arg(args, double);
        if (cur < 0) {
            va_end(args);
            return INPUT_ERROR;  // Среднее геометрическое не вычисляется для отрицательных чисел
        }
        *res *= cur;
        if (check_overflow(*res) == OVERFLOW_ERROR) {
            va_end(args);
            return OVERFLOW_ERROR;
        }
    }
    *res = pow(*res, 1.0 / count);  // Возведение в степень (1/count)
    va_end(args);
    return SUCCESS;
}

// Рекурсивная функция для быстрого возведения в степень
status fast_pow(double base, int degree, double *res) {
    if (degree < 0) {
        return fast_pow(1.0 / base, -degree, res);
    }
    if (degree == 0) {
        *res = 1.0;
        return SUCCESS;
    }

    if (degree % 2 == 1) {
        status state = fast_pow(base, degree - 1, res);
        if (state != SUCCESS) return state;  // Проверка ошибки после рекурсивного вызова
        *res *= base;
    } else {
        status state = fast_pow(base, degree / 2, res);
        if (state != SUCCESS) return state;  // Проверка ошибки после рекурсивного вызова
        *res *= *res;
    }

    if (check_overflow(*res) == OVERFLOW_ERROR) {
        return OVERFLOW_ERROR;
    }

    return SUCCESS;
}
