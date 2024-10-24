#include "task10.h"
#include <math.h>

// Функция переразложения многочлена
status polynomial_rearrange(double epsilon, double a, int degree, double *coefficients, double **result) {
    if (degree < 0 || !coefficients || !result) {
        return INPUT_ERROR;
    }

    *result = (double *)malloc((degree + 1) * sizeof(double));
    if (!(*result)) {
        return MEMORY_ERROR;
    }

    // Сначала копируем свободный коэффициент
    (*result)[0] = coefficients[0];

    // Переразложение с точностью epsilon
    for (int i = 1; i <= degree; i++) {
        (*result)[i] = coefficients[i];
        for (int j = i - 1; j >= 0; j--) {
            (*result)[i] -= (*result)[j] * pow(a, i - j);
        }

        // Если результат меньше epsilon, считаем его равным нулю
        if (fabs((*result)[i]) < epsilon) {
            (*result)[i] = 0.0;
        }
    }

    return SUCCESS;
}
