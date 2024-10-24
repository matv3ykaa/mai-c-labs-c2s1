#ifndef _TASK5_H_
#define _TASK5_H_

#include <stdio.h>
#include <stdlib.h>

// Определение статусов программы
typedef enum {
    SUCCESS,
    INPUT_ERROR,
    MEMORY_ERROR,
    FILE_WRITE_ERROR
} status;

// Функция для работы с fprintf
status overfprintf(FILE *stream, const char *format, ...);

// Функция для работы с sprintf
status oversprintf(char *str, const char *format, ...);

#endif
