#include "task5.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Использование: %s <flag> <number> [<base>]\n", argv[0]);
        return INPUT_ERROR;  // Проверка на минимальное количество аргументов
    }

    char *flag = argv[1];   // Флаг, определяющий формат вывода
    int number = atoi(argv[2]);  // Число для форматирования
    int base = 10;  // Базовая система счисления, если нужно

    if (argc > 3) {
        base = atoi(argv[3]);  // Если передано основание, используем его
    }

    switch (flag[1]) {
        case 'R':  // %Ro - Римские цифры
            if (flag[2] == 'o') {
                overfprintf(stdout, "%Ro\n", number);
            } else {
                printf("Неизвестный флаг\n");
                return INPUT_ERROR;
            }
            break;

        case 'Z':  // %Zr - Цекендорфово представление
            if (flag[2] == 'r') {
                overfprintf(stdout, "%Zr\n", number);
            } else {
                printf("Неизвестный флаг\n");
                return INPUT_ERROR;
            }
            break;

        case 'C':  // %Cv или %CV - Система счисления
            if (flag[2] == 'v') {
                overfprintf(stdout, "%Cv\n", number, base);
            } else if (flag[2] == 'V') {
                overfprintf(stdout, "%CV\n", number, base);
            } else {
                printf("Неизвестный флаг\n");
                return INPUT_ERROR;
            }
            break;

        default:
            printf("Неверный флаг\n");
            return INPUT_ERROR;
    }

    return SUCCESS;
}
