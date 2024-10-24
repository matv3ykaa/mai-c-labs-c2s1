#include "task8.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

status validate_input(int argc, char *argv[]) {
    if (argc < 4) {  // Необходимо минимум 3 аргумента: флаг, основание и хотя бы одно число
        return INPUT_ERROR;
    }

    int base = atoi(argv[2]);
    if (base < 2 || base > 36) {
        return INPUT_ERROR;  // Основание должно быть в диапазоне [2..36]
    }

    for (int i = 3; i < argc; i++) {
        for (int j = 0; argv[i][j] != '\0'; j++) {
            if (!isalnum(argv[i][j])) {
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

    // Обработка флага
    switch (argv[1][1]) {
        case 's': {  // -s для суммирования чисел в системе счисления
            int base = atoi(argv[2]);  // Считываем основание системы счисления

            // Суммируем переданные числа
            if (sum_numbers_in_base(base, argc - 3, argv[3], argv[4], argv[5], argv[6]) != SUCCESS) {
                printf("Ошибка при суммировании чисел\n");
                return MEMORY_ERROR;
            }
            break;
        }

        default:
            printf("Ошибка: некорректный флаг\n");
            return INPUT_ERROR;
    }

    return SUCCESS;
}
