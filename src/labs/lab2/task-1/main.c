#include "task1.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    // Проверка ввода
    if (validate_input(argc, argv) == INPUT_ERROR) {
        printf("Ошибка ввода данных\n");
        return INPUT_ERROR;
    }

    // Обработка флага
    switch (argv[1][1]) {
        case 'l': {
            if (argc != 3) {
                printf("Ошибка ввода данных\n");
                return INPUT_ERROR;
            }
            printf("Длина строки: %d\n", my_strlen(argv[2]));
            break;
        }
        case 'r': {
            if (argc != 3) {
                printf("Ошибка ввода данных\n");
                return INPUT_ERROR;
            }
            char *reverse_string = NULL;
            if (my_strrev(argv[2], &reverse_string) == MEMORY_ERROR) {
                printf("Ошибка выделения памяти\n");
                return MEMORY_ERROR;
            }
            printf("Перевёрнутая строка: \"%s\"\n", reverse_string);
            free(reverse_string);
            break;
        }
        case 'u': {
            char *new_string = NULL;
            if (up_odd_str(argv[2], &new_string) == MEMORY_ERROR) {
                printf("Ошибка выделения памяти\n");
                return MEMORY_ERROR;
            }
            printf("Преобразованная строка: \"%s\"\n", new_string);
            free(new_string);
            break;
        }
        case 'n': {
            char *transformed_string = NULL;
            if (transform_str(argv[2], &transformed_string) == MEMORY_ERROR) {
                printf("Ошибка выделения памяти\n");
                return MEMORY_ERROR;
            }
            printf("Новая строка: \"%s\"\n", transformed_string);
            free(transformed_string);
            break;
        }
        default:
            printf("Ошибка: некорректный флаг\n");
            return INPUT_ERROR;
    }

    return SUCCESS;
}
