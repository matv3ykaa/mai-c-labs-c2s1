#include "task9.h"
#include <math.h>

// Нахождение НОД (наибольшего общего делителя)
static int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Разложение числа на простые множители
static void factorize(int n, int *factors) {
    for (int i = 2; n > 1; i++) {
        while (n % i == 0) {
            factors[i]++;
            n /= i;
        }
    }
}

// Функция проверки, имеет ли дробь конечное представление
status has_finite_representation(double number, int base) {
    if (base < 2) {
        return INPUT_ERROR;  // Основание должно быть больше 1
    }

    int numerator, denominator;
    double int_part, frac_part;

    frac_part = modf(number, &int_part);

    // Преобразуем дробную часть в несократимую дробь
    denominator = 1;
    while (frac_part != 0.0 && denominator < 1000000) {
        frac_part *= 10;
        denominator *= 10;
        frac_part = modf(frac_part, &int_part);
    }
    numerator = (int)(number * denominator);

    // Упрощаем дробь
    int gcd_val = gcd(numerator, denominator);
    numerator /= gcd_val;
    denominator /= gcd_val;

    // Разложим основание на простые множители
    int base_factors[100] = {0};
    factorize(base, base_factors);

    // Разложим знаменатель на простые множители
    int denom_factors[100] = {0};
    factorize(denominator, denom_factors);

    // Проверяем, делится ли знаменатель только на простые множители основания
    for (int i = 2; i < 100; i++) {
        if (denom_factors[i] > 0 && base_factors[i] == 0) {
            return SUCCESS;  // Дробь имеет конечное представление
        }
    }

    return SUCCESS;
}
