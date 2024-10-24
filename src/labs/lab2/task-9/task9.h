#ifndef _TASK9_H_
#define _TASK9_H_

#include <stdlib.h>

// Статусы выполнения программы
typedef enum {
    SUCCESS,
    INPUT_ERROR,
    MEMORY_ERROR
} status;

// Функция проверки, имеет ли дробь конечное представление в данной системе счисления
status has_finite_representation(double number, int base);

#endif
