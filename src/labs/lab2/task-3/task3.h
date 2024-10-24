#ifndef _TASK3_H_
#define _TASK3_H_

#include <stdio.h>
#include <stdlib.h>

// Определение статуса выполнения программы
typedef enum {
    SUCCESS,
    FILE_OPEN_ERROR,
    MEMORY_ERROR,
    INPUT_ERROR
} status;

// Функция поиска подстроки в файлах
status search_substring_in_files(const char *substring, int file_count, char **file_paths);

#endif
