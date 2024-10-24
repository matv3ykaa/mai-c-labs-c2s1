#include "task2.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Ошибка ввода данных\n");
        return INPUT_ERROR;
    }

    // Обработка флага
    switch (argv[1][1]) {
        case 'g': {
            // Вычисление среднего геометрического
            double result;
            status state = geometric_mean(&result, argc - 2, atof(argv[2]), atof(argv[3]), atof(argv[4]));
            if (state == SUCCESS) {
                printf("Среднее геометрическое: %lf\n", result);
            } else if (state == INPUT_ERROR) {
                printf("Ошибка: некорректные данные для среднего геометрического\n");
            } else if (state == OVERFLOW_ERROR) {
                printf("Ошибка: переполнение при вычислении\n");
            }
            break;
        }
        case 'p': {
            // Быстрое возведение в степень
            if (argc != 4) {
                printf("Ошибка ввода данных\n");
                return INPUT_ERROR;
            }
            double base = atof(argv[2]);
            int degree = atoi(argv[3]);
            double result;
            status state = fast_pow(base, degree, &result);
            if (state == SUCCESS) {
                printf("Результат возведения в степень: %lf\n", result);
            } else if (state == OVERFLOW_ERROR) {
                printf("Ошибка: переполнение при вычислении степени\n");
            }
            break;
        }
        default:
            printf("Ошибка: некорректный флаг\n");
            return INPUT_ERROR;
    }

    return SUCCESS;
}
