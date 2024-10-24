#include "task1.h"

// Функция для проверки валидности ввода
status validate_input(int argc, char *argv[]) {
    if (argc < 3 || argv[1][0] != '-' || argv[1][2] != '\0') {
        return INPUT_ERROR;
    }
    return SUCCESS;
}

// Подсчёт длины строки (без использования <string.h>)
int my_strlen(const char *str) {
    int len = 0;
    while (*str++) len++;
    return len;
}

// Реверс строки
status my_strrev(const char *src, char **dest) {
    int len = my_strlen(src);
    *dest = (char *)malloc((len + 1) * sizeof(char));
    if (!(*dest)) {
        return MEMORY_ERROR;
    }

    for (int i = 0; i < len; i++) {
        (*dest)[i] = src[len - i - 1];
    }
    (*dest)[len] = '\0';
    return SUCCESS;
}

// Преобразование нечётных символов строки в верхний регистр
status up_odd_str(const char *src, char **dest) {
    int len = my_strlen(src);
    *dest = (char *)malloc((len + 1) * sizeof(char));
    if (!(*dest)) {
        return MEMORY_ERROR;
    }

    for (int i = 0; i < len; i++) {
        (*dest)[i] = (i % 2 == 1 && src[i] >= 'a' && src[i] <= 'z') ? src[i] - 32 : src[i];  // Преобразование в верхний регистр
    }
    (*dest)[len] = '\0';
    return SUCCESS;
}

// Формирование новой строки: сначала цифры, потом буквы, потом остальные символы
status transform_str(const char *src, char **dest) {
    int len = my_strlen(src);
    *dest = (char *)malloc((len + 1) * sizeof(char));
    if (!(*dest)) {
        return MEMORY_ERROR;
    }
    int pos = 0;

    // Сначала цифры
    for (int i = 0; i < len; i++) {
        if (src[i] >= '0' && src[i] <= '9') {
            (*dest)[pos++] = src[i];
        }
    }

    // Затем буквы
    for (int i = 0; i < len; i++) {
        if ((src[i] >= 'a' && src[i] <= 'z') || (src[i] >= 'A' && src[i] <= 'Z')) {
            (*dest)[pos++] = src[i];
        }
    }

    // Наконец, остальные символы
    for (int i = 0; i < len; i++) {
        if (!((src[i] >= '0' && src[i] <= '9') || (src[i] >= 'a' && src[i] <= 'z') || (src[i] >= 'A' && src[i] <= 'Z'))) {
            (*dest)[pos++] = src[i];
        }
    }
    (*dest)[pos] = '\0';
    return SUCCESS;
}
