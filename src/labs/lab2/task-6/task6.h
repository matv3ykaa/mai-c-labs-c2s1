#ifndef _TASK6_H_
#define _TASK6_H_

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    SUCCESS,
    INPUT_ERROR,
    FILE_READ_ERROR
} status;

// Функции для работы с файлами и строками
status overfscanf(FILE *stream, const char *format, ...);
status oversscanf(const char *str, const char *format, ...);

#endif
