#include "task4.h"

// Функция для вычисления знака векторного произведения двух векторов
static double cross_product(double x1, double y1, double x2, double y2) {
    return x1 * y2 - y1 * x2;
}

// Функция для проверки выпуклости многоугольника
status check_convex_polygon(int vertex_count, const double *x, const double *y) {
    if (vertex_count < 3) {
        return INPUT_ERROR;  // Многоугольник должен иметь минимум 3 вершины
    }

    int sign = 0;
    for (int i = 0; i < vertex_count; i++) {
        // Вычисляем векторное произведение для тройки соседних вершин
        double x1 = x[(i + 1) % vertex_count] - x[i];
        double y1 = y[(i + 1) % vertex_count] - y[i];
        double x2 = x[(i + 2) % vertex_count] - x[(i + 1) % vertex_count];
        double y2 = y[(i + 2) % vertex_count] - y[(i + 1) % vertex_count];

        double cross = cross_product(x1, y1, x2, y2);
        if (cross != 0) {
            if (sign == 0) {
                sign = (cross > 0) ? 1 : -1;  // Определяем направление поворота
            } else if ((cross > 0 && sign < 0) || (cross < 0 && sign > 0)) {
                return NOT_CONVEX;  // Если направления меняются, многоугольник не выпуклый
            }
        }
    }
    return SUCCESS;  // Многоугольник выпуклый
}

// Функция для вычисления значения многочлена с помощью схемы Горнера
status evaluate_polynomial(double x_value, int degree, const double *coefficients, double *result) {
    if (degree < 0 || coefficients == NULL || result == NULL) {
        return INPUT_ERROR;
    }

    *result = coefficients[0];  // Начинаем с коэффициента при старшей степени
    for (int i = 1; i <= degree; i++) {
        *result = *result * x_value + coefficients[i];  // Схема Горнера
    }

    return SUCCESS;
}
