#include "task9.h"
#include <stdio.h>
#include <stdlib.h>

status validate_input(int argc, char *argv[]) {
    if (argc != 4) {  // Необходимо три аргумента: флаг, дробь и основание системы счисления
        return INPUT_ERROR;
    }

    for (int i = 2; i < argc; i++) {
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

    // Обработка флага
    switch (argv[1][1]) {
        case 'f': {  // -f для проверки конечного представления дроби
            double number = atof(argv[2]);  // Число в виде дроби
            int base = atoi(argv[3]);  // Основание системы счисления

            // Проверяем, имеет ли дробь конечное представление
            status result = has_finite_representation(number, base);
            if (result == SUCCESS) {
                printf("Дробь %lf имеет конечное представление в системе счисления с основанием %d\n", number, base);
            } else {
                printf("Дробь %lf не имеет конечного представления в системе счисления с основанием %d\n", number, base);
            }
            break;
        }

        default:
            printf("Ошибка: некорректный флаг\n");
            return INPUT_ERROR;
    }

    return SUCCESS;
}
