#include "task6.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Использование: %s <флаг> <значение>...\n", argv[0]);
        return INPUT_ERROR;
    }

    switch (argv[1][1]) {
        case 'R': {
            if (argc != 3) {
                printf("Ошибка: требуется один аргумент для римских цифр\n");
                return INPUT_ERROR;
            }
            int roman_num;
            oversscanf(argv[2], "%Ro", &roman_num);
            printf("Римские цифры: %d\n", roman_num);
            break;
        }
        case 'Z': {
            if (argc != 3) {
                printf("Ошибка: требуется одно Цекендорфово представление\n");
                return INPUT_ERROR;
            }
            unsigned int zr_num;
            oversscanf(argv[2], "%Zr", &zr_num);
            printf("Цекендорфово представление: %u\n", zr_num);
            break;
        }
        case 'C': {
            if (argc != 4) {
                printf("Ошибка: требуется основание системы счисления и число\n");
                return INPUT_ERROR;
            }
            int base = atoi(argv[2]);
            int base_num;
            oversscanf(argv[3], "%Cv", base, &base_num);
            printf("Число в системе счисления %d: %d\n", base, base_num);
            break;
        }
        default:
            printf("Ошибка: неподдерживаемый флаг\n");
            return INPUT_ERROR;
    }

    return SUCCESS;
}
