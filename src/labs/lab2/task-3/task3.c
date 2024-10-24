#include "task3.h"

// Вспомогательная функция для проверки, является ли подстрока частью строки на позиции pos
static int is_substring_at(const char *str, const char *sub, int pos) {
    int i = 0;
    while (sub[i] != '\0' && str[pos + i] != '\0') {
        if (str[pos + i] != sub[i]) {
            return 0;  // Несовпадение символов
        }
        i++;
    }
    return sub[i] == '\0';  // Убедимся, что вся подстрока совпала
}

// Функция для поиска всех вхождений подстроки в переданных файлах
status search_substring_in_files(const char *substring, int file_count, char **file_paths) {
    if (substring == NULL || file_count <= 0 || file_paths == NULL) {
        return INPUT_ERROR;  // Проверка корректности входных данных
    }

    for (int file_idx = 0; file_idx < file_count; file_idx++) {
        FILE *file = fopen(file_paths[file_idx], "r");
        if (!file) {
            printf("Ошибка: не удалось открыть файл %s\n", file_paths[file_idx]);
            return FILE_OPEN_ERROR;  // Ошибка открытия файла
        }

        char *line = NULL;  // Буфер для чтения строк
        size_t len = 0;
        ssize_t read;
        int line_num = 0;

        // Чтение файла построчно
        while ((read = getline(&line, &len, file)) != -1) {
            line_num++;
            for (int i = 0; i < read; i++) {
                if (is_substring_at(line, substring, i)) {
                    // Печатаем номер строки и позицию символа
                    printf("Файл: %s, Строка: %d, Позиция: %d\n", file_paths[file_idx], line_num, i + 1);
                }
            }
        }

        free(line);  // Освобождение динамически выделенной памяти под строку
        fclose(file);  // Закрытие файла
    }

    return SUCCESS;
}
