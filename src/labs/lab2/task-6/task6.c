#include "task6.h"
#include <stdarg.h>
#include <string.h>
#include <limits.h>  // Для UINT_MAX

// Преобразование римских цифр в число
static int roman_to_int(const char *str) {
    struct roman {
        const char *symbol;
        int value;
    } roman_numerals[] = {
            {"M", 1000}, {"CM", 900}, {"D", 500}, {"CD", 400},
            {"C", 100}, {"XC", 90}, {"L", 50}, {"XL", 40},
            {"X", 10}, {"IX", 9}, {"V", 5}, {"IV", 4}, {"I", 1}
    };

    int num = 0;
    int i = 0;

    while (*str) {
        if (strncmp(str, roman_numerals[i].symbol, strlen(roman_numerals[i].symbol)) == 0) {
            num += roman_numerals[i].value;
            str += strlen(roman_numerals[i].symbol);
        } else {
            i++;
        }
    }
    return num;
}

// Преобразование Цекендорфова представления в число
static unsigned int zr_to_int(const char *zr) {
    unsigned int fib[100];
    fib[0] = 1;
    fib[1] = 2;
    int count = 2;
    unsigned int num = 0;

    while (fib[count - 1] + fib[count - 2] <= UINT_MAX) {
        fib[count] = fib[count - 1] + fib[count - 2];
        count++;
    }

    for (int i = 0; zr[i] != '\0'; i++) {
        if (zr[i] == '1') {
            num += fib[count - i - 1];
        }
    }

    return num;
}

// Преобразование числа из строки в заданной системе счисления
static int str_to_base(const char *str, int base, int *result) {
    char *endptr;
    *result = strtol(str, &endptr, base);

    if (*endptr != '\0') {
        return INPUT_ERROR;
    }
    return SUCCESS;
}

// Функция overfscanf
status overfscanf(FILE *stream, const char *format, ...) {
    va_list args;
    va_start(args, format);

    const char *p = format;
    char buffer[1024];

    while (*p) {
        if (*p == '%') {
            p++;
            if (*p == 'R' && *(p + 1) == 'o') {
                char roman_str[100];
                if (fscanf(stream, "%s", roman_str) != 1) {
                    return FILE_READ_ERROR;
                }
                int *num_ptr = va_arg(args, int *);
                *num_ptr = roman_to_int(roman_str);
                p += 2;
            } else if (*p == 'Z' && *(p + 1) == 'r') {
                char zr_str[100];
                if (fscanf(stream, "%s", zr_str) != 1) {
                    return FILE_READ_ERROR;
                }
                unsigned int *num_ptr = va_arg(args, unsigned int *);
                *num_ptr = zr_to_int(zr_str);
                p += 2;
            } else if (*p == 'C' && (*(p + 1) == 'v' || *(p + 1) == 'V')) {
                int base = va_arg(args, int);
                int *num_ptr = va_arg(args, int *);
                if (fscanf(stream, "%s", buffer) != 1) {
                    return FILE_READ_ERROR;
                }
                if (str_to_base(buffer, base, num_ptr) != SUCCESS) {
                    return INPUT_ERROR;
                }
                p += 2;
            } else {
                // Неподдерживаемый флаг
                return INPUT_ERROR;
            }
        } else {
            fgetc(stream);  // Пропуск символа, если это не наш флаг
            p++;
        }
    }

    va_end(args);
    return SUCCESS;
}

// Функция oversscanf
status oversscanf(const char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);

    const char *p = format;
    char buffer[1024];
    const char *input_ptr = str;

    while (*p) {
        if (*p == '%') {
            p++;
            if (*p == 'R' && *(p + 1) == 'o') {
                sscanf(input_ptr, "%s", buffer);
                int *num_ptr = va_arg(args, int *);
                *num_ptr = roman_to_int(buffer);
                input_ptr += strlen(buffer);
                p += 2;
            } else if (*p == 'Z' && *(p + 1) == 'r') {
                sscanf(input_ptr, "%s", buffer);
                unsigned int *num_ptr = va_arg(args, unsigned int *);
                *num_ptr = zr_to_int(buffer);
                input_ptr += strlen(buffer);
                p += 2;
            } else if (*p == 'C' && (*(p + 1) == 'v' || *(p + 1) == 'V')) {
                int base = va_arg(args, int);
                int *num_ptr = va_arg(args, int *);
                sscanf(input_ptr, "%s", buffer);
                if (str_to_base(buffer, base, num_ptr) != SUCCESS) {
                    return INPUT_ERROR;
                }
                input_ptr += strlen(buffer);
                p += 2;
            } else {
                // Неподдерживаемый флаг
                return INPUT_ERROR;
            }
        } else {
            input_ptr++;  // Пропуск символа
            p++;
        }
    }

    va_end(args);
    return SUCCESS;
}
