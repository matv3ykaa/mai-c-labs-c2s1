#include "task7.h"

// Пример функции для поиска корня
double example_function(double x) {
    return x * x - 2;  // Уравнение x^2 - 2 = 0 (корень √2)
}

int main(void) {
    double root;
    double epsilon = 1e-6;  // Заданная точность
    double a = 0, b = 2;  // Интервал [0, 2]

    status result = find_root(example_function, a, b, epsilon, &root);
    if (result == SUCCESS) {
        printf("Найден корень: %lf\n", root);
    } else if (result == ROOT_NOT_FOUND) {
        printf("Корень не найден в заданном интервале.\n");
    } else if (result == INPUT_ERROR) {
        printf("Ошибка ввода данных.\n");
    }

    return 0;
}
