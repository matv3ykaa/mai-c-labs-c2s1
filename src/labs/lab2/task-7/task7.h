#ifndef _TASK7_H_
#define _TASK7_H_

#include <stdio.h>
#include <stdlib.h>

// Статусы программы
typedef enum {
    SUCCESS,
    INPUT_ERROR,
    PARSING_ERROR,
    ROOT_NOT_FOUND
} status;

// Прототип функции нахождения корня методом дихотомии
status find_root(double (*func)(double), double a, double b, double epsilon, double *root);

// Прототип функции парсинга и проверки уравнения
status parse_equation(const char *equation_str, double (**func)(double));

#endif
