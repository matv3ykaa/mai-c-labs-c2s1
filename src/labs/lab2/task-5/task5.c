#include "task5.h"
#include <stdarg.h>
#include <string.h>

// Вспомогательные функции

// Преобразование числа в римские цифры (максимум до 3999)
static void int_to_roman(int num, char *buffer) {
    struct roman {
        int value;
        const char *symbol;
    } roman_numerals[] = {
            {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
            {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
            {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
    };

    buffer[0] = '\0';  // Очистка буфера
    for (int i = 0; num > 0; i++) {
        while (num >= roman_numerals[i].value) {
            strcat(buffer, roman_numerals[i].symbol);
            num -= roman_numerals[i].value;
        }
    }
}

// Преобразование числа в Цекендорфово представление (сумма чисел Фибоначчи)
static void int_to_zr(unsigned int num, char *buffer) {
    unsigned int fib[100];  // Массив чисел Фибоначчи
    fib[0] = 1;
    fib[1] = 2;
    int count = 2;

    // Генерация чисел Фибоначчи, пока они меньше num
    while (fib[count - 1] + fib[count - 2] <= num) {
        fib[count] = fib[count - 1] + fib[count - 2];
        count++;
    }

    buffer[0] = '\0';  // Очистка буфера
    for (int i = count - 1; i >= 0; i--) {
        if (num >= fib[i]) {
            strcat(buffer, "1");
            num -= fib[i];
        } else {
            strcat(buffer, "0");
        }
    }
    strcat(buffer, "1");  // Завершающий символ
}

// Преобразование числа в заданную систему счисления (буквы в нижнем регистре)
static void int_to_base(int num, int base, char *buffer, int uppercase) {
    char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    char digits_upper[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char temp[100];
    int index = 0;

    if (num == 0) {
        strcpy(buffer, "0");
        return;
    }

    while (num > 0) {
        int remainder = num % base;
        temp[index++] = uppercase ? digits_upper[remainder] : digits[remainder];
        num /= base;
    }

    temp[index] = '\0';

    // Реверс строки
    for (int i = 0; i < index; i++) {
        buffer[i] = temp[index - i - 1];
    }
    buffer[index] = '\0';
}

// Функция overfprintf
status overfprintf(FILE *stream, const char *format, ...) {
    va_list args;
    va_start(args, format);

    const char *p = format;

    while (*p) {
        if (*p == '%') {
            p++;
            if (*p == 'R' && *(p + 1) == 'o') {
                int num = va_arg(args, int);
                char roman[50];
                int_to_roman(num, roman);
                if (fprintf(stream, "%s", roman) < 0) {
                    return FILE_WRITE_ERROR;
                }
                p += 2;
            } else if (*p == 'Z' && *(p + 1) == 'r') {
                unsigned int num = va_arg(args, unsigned int);
                char zr[50];
                int_to_zr(num, zr);
                if (fprintf(stream, "%s", zr) < 0) {
                    return FILE_WRITE_ERROR;
                }
                p += 2;
            } else if (*p == 'C' && *(p + 1) == 'v') {
                int num = va_arg(args, int);
                int base = va_arg(args, int);
                char base_str[50];
                int_to_base(num, base, base_str, 0);  // Строка в нижнем регистре
                if (fprintf(stream, "%s", base_str) < 0) {
                    return FILE_WRITE_ERROR;
                }
                p += 2;
            } else if (*p == 'C' && *(p + 1) == 'V') {
                int num = va_arg(args, int);
                int base = va_arg(args, int);
                char base_str[50];
                int_to_base(num, base, base_str, 1);  // Строка в верхнем регистре
                if (fprintf(stream, "%s", base_str) < 0) {
                    return FILE_WRITE_ERROR;
                }
                p += 2;
            } else {
                // Если это не наш пользовательский флаг, просто выводим как обычно
                if (fputc('%', stream) == EOF || fputc(*p, stream) == EOF) {
                    return FILE_WRITE_ERROR;
                }
                p++;
            }
        } else {
            if (fputc(*p, stream) == EOF) {
                return FILE_WRITE_ERROR;
            }
            p++;
        }
    }

    va_end(args);
    return SUCCESS;
}

// Функция oversprintf
status oversprintf(char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);

    char *p = str;  // Указатель для записи в строку
    const char *f = format;

    while (*f) {
        if (*f == '%') {
            f++;
            if (*f == 'R' && *(f + 1) == 'o') {
                int num = va_arg(args, int);
                char roman[50];
                int_to_roman(num, roman);
                strcpy(p, roman);
                p += strlen(roman);
                f += 2;
            } else if (*f == 'Z' && *(f + 1) == 'r') {
                unsigned int num = va_arg(args, unsigned int);
                char zr[50];
                int_to_zr(num, zr);
                strcpy(p, zr);
                p += strlen(zr);
                f += 2;
            } else if (*f == 'C' && *(f + 1) == 'v') {
                int num = va_arg(args, int);
                int base = va_arg(args, int);
                char base_str[50];
                int_to_base(num, base, base_str, 0);
                strcpy(p, base_str);
                p += strlen(base_str);
                f += 2;
            } else if (*f == 'C' && *(f + 1) == 'V') {
                int num = va_arg(args, int);
                int base = va_arg(args, int);
                char base_str[50];
                int_to_base(num, base, base_str, 1);
                strcpy(p, base_str);
                p += strlen(base_str);
                f += 2;
            } else {
                // Неизвестный флаг, просто копируем
                *p++ = '%';
                *p++ = *f++;
            }
        } else {
            *p++ = *f++;
        }
    }

    *p = '\0';  // Завершаем строку
    va_end(args);
    return SUCCESS;
}
