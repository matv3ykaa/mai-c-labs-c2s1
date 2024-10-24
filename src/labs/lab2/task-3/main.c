#include "task3.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Использование: %s <подстрока> <файл1> <файл2> ...\n", argv[0]);
        return INPUT_ERROR;  // Проверка на минимальное количество аргументов
    }

    const char *substring = argv[1];  // Первая строка — это подстрока
    int file_count = argc - 2;  // Количество файлов — все аргументы, кроме подстроки
    char **file_paths = &argv[2];  // Пути к файлам начинаются с argv[2]

    // Вызов функции поиска подстроки в файлах
    status result = search_substring_in_files(substring, file_count, file_paths);
    if (result != SUCCESS) {
        // В случае ошибки выводим сообщение
        switch (result) {
            case INPUT_ERROR:
                printf("Ошибка ввода данных\n");
                break;
            case FILE_OPEN_ERROR:
                printf("Ошибка открытия файла\n");
                break;
            case MEMORY_ERROR:
                printf("Ошибка выделения памяти\n");
                break;
            default:
                printf("Неизвестная ошибка\n");
        }
        return result;
    }

    return SUCCESS;
}
