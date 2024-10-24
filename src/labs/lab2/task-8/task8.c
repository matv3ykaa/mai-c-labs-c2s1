#include "task8.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

// Преобразование символа в число для системы счисления
static int char_to_digit(char c, int base) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'a' && c <= 'z') {
        return c - 'a' + 10;
    } else if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 10;
    }
    return -1;  // Недопустимый символ
}

// Преобразование числа в строку в указанной системе счисления
static char digit_to_char(int digit, int base) {
    if (digit < 10) {
        return '0' + digit;
    } else {
        return 'a' + (digit - 10);
    }
}

// Сложение двух чисел в столбик в заданной системе счисления
status add_in_column(const char *num1, const char *num2, int base, char **result) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int max_len = (len1 > len2) ? len1 : len2;
    int carry = 0;

    char *sum = (char *)malloc((max_len + 2) * sizeof(char));  // +2 для возможного переноса и '\0'
    if (!sum) {
        return MEMORY_ERROR;
    }

    sum[max_len + 1] = '\0';

    for (int i = 0; i < max_len; i++) {
        int digit1 = (i < len1) ? char_to_digit(num1[len1 - 1 - i], base) : 0;
        int digit2 = (i < len2) ? char_to_digit(num2[len2 - 1 - i], base) : 0;
        if (digit1 == -1 || digit2 == -1) {
            free(sum);
            return INPUT_ERROR;  // Недопустимый символ
        }

        int temp_sum = digit1 + digit2 + carry;
        carry = temp_sum / base;
        sum[max_len - i] = digit_to_char(temp_sum % base, base);
    }

    if (carry > 0) {
        sum[0] = digit_to_char(carry, base);
        *result = sum;
    } else {
        *result = sum + 1;  // Пропускаем ведущий ноль
    }

    return SUCCESS;
}

// Основная функция для суммирования чисел в системе счисления
status sum_numbers_in_base(int base, int count, ...) {
    if (base < 2 || base > 36 || count < 1) {
        return INPUT_ERROR;
    }

    va_list args;
    va_start(args, count);

    char *total = NULL;
    char *current_num = NULL;

    // Считываем первое число
    const char *first = va_arg(args, const char *);
    total = strdup(first);

    // Суммируем остальные числа
    for (int i = 1; i < count; i++) {
        const char *next = va_arg(args, const char *);
        char *temp_sum = NULL;
        if (add_in_column(total, next, base, &temp_sum) != SUCCESS) {
            free(total);
            return MEMORY_ERROR;
        }

        free(total);
        total = temp_sum;
    }

    // Убираем ведущие нули
    while (*total == '0' && *(total + 1)) {
        total++;
    }

    // Вывод результата
    printf("Сумма в системе счисления с основанием %d: %s\n", base, total);

    va_end(args);
    return SUCCESS;
}
