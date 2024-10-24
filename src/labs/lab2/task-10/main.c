#include "task10.h"
#include <stdio.h>
#include <stdlib.h>

status validate_input(int argc, char *argv[]) {
    if (argc < 5) {  // Необходимо минимум 4 аргумента: ε, a, степень и коэффициенты
        return INPUT_ERROR;
    }

    for (int i = 1; i < argc; i++) {
        for (int j = 0; argv[i][j] != '\0'; j++) {
            if ((argv[i][j] < '0' || argv[i][j] > '9') && argv[i][j] != '.' && argv[i][j] != '-') {
                return INPUT_ERROR;
            }
        }
    }

    return SUCCESS;
}

int main(int argc, char *argv[]) {
    // Проверка ввода
    if (validate_input(argc, argv) == INPUT_ERROR) {
        printf("Ошибка ввода данных\n");
        return INPUT_ERROR;
    }

    // Считываем epsilon, a и степень многочлена
    double epsilon = atof(argv[1]);
    double a = atof(argv[2]);
    int degree = atoi(argv[3]);

    // Проверяем, что коэффициенты заданы корректно
    if (argc != 4 + degree + 1) {
        printf("Ошибка: неверное количество коэффициентов\n");
        return INPUT_ERROR;
    }

    // Считываем коэффициенты
    double *coefficients = (double *)malloc((degree + 1) * sizeof(double));
    if (!coefficients) {
        printf("Ошибка выделения памяти\n");
        return MEMORY_ERROR;
    }

    for (int i = 0; i <= degree; i++) {
        coefficients[i] = atof(argv[4 + i]);
    }

    // Массив для хранения результата переразложения
    double *result = NULL;

    // Выполняем переразложение
    if (polynomial_rearrange(epsilon, a, degree, coefficients, &result) == MEMORY_ERROR) {
        printf("Ошибка выделения памяти для результата\n");
        free(coefficients);
        return MEMORY_ERROR;
    }

    // Выводим результат
    printf("Результат переразложения многочлена:\n");
    for (int i = 0; i <= degree; i++) {
        printf("Коэффициент при (x - a)^%d: %lf\n", i, result[i]);
    }

    // Освобождаем память
    free(coefficients);
    free(result);

    return SUCCESS;
}
