#ifndef _TASK1_H_
#define _TASK1_H_

#include <stdlib.h>

typedef enum {
    SUCCESS,
    INPUT_ERROR,
    MEMORY_ERROR
} status;

// Функция для проверки валидности ввода
status validate_input(int argc, char *argv[]);

// Строковые операции
int my_strlen(const char *str);
status my_strrev(const char *src, char **dest);
status up_odd_str(const char *src, char **dest);
status transform_str(const char *src, char **dest);

#endif
