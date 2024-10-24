#include "task4.h"

int main(void) {
    // Пример вызова функции проверки выпуклости многоугольника
    int vertex_count = 4;
    double x_coords[] = {0.0, 2.0, 2.0, 0.0};
    double y_coords[] = {0.0, 0.0, 2.0, 2.0};

    status result = check_convex_polygon(vertex_count, x_coords, y_coords);
    if (result == SUCCESS) {
        printf("Многоугольник выпуклый\n");
    } else if (result == NOT_CONVEX) {
        printf("Многоугольник не выпуклый\n");
    } else {
        printf("Ошибка ввода данных\n");
    }

    // Пример вызова функции вычисления значения многочлена
    double coefficients[] = {2.0, -3.0, 4.0};  // 2x^2 - 3x + 4
    double x_value = 1.0;
    double poly_result;

    result = evaluate_polynomial(x_value, 2, coefficients, &poly_result);
    if (result == SUCCESS) {
        printf("Значение многочлена: %lf\n", poly_result);
    } else {
        printf("Ошибка при вычислении многочлена\n");
    }

    return 0;
}
