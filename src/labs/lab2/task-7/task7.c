#include "task7.h"

// Реализация метода бисекции для поиска корня
status find_root(double (*func)(double), double a, double b, double epsilon, double *root) {
    if (func == NULL || epsilon <= 0 || root == NULL) {
        return INPUT_ERROR;  // Проверка входных данных
    }

    double fa = func(a);
    double fb = func(b);

    // Проверка, что на концах интервала значения имеют противоположные знаки
    if (fa * fb > 0) {
        return ROOT_NOT_FOUND;  // Нет корня в интервале
    }

    while ((b - a) / 2.0 > epsilon) {
        double c = (a + b) / 2.0;  // Средняя точка
        double fc = func(c);

        if (fc == 0.0) {
            *root = c;  // Точное попадание в корень
            return SUCCESS;
        }

        // Корень находится в одной из половин
        if (fa * fc < 0) {
            b = c;
            fb = fc;
        } else {
            a = c;
            fa = fc;
        }
    }

    *root = (a + b) / 2.0;  // Приближённое значение корня
    return SUCCESS;
}
