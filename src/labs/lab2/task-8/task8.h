#ifndef _TASK8_H_
#define _TASK8_H_

#include <stdlib.h>

// Статусы выполнения программы
typedef enum {
    SUCCESS,
    INPUT_ERROR,
    MEMORY_ERROR
} status;

// Функция для суммирования чисел в заданной системе счисления
status sum_numbers_in_base(int base, int count, ...);

// Функция сложения в столбик для двух чисел в указанной системе счисления
status add_in_column(const char *num1, const char *num2, int base, char **result);

#endif
