#include "resultHandler.h"
#include <stdio.h>  // для printf

/**
 * @brief Тестовая функция деления двух чисел.
 * 
 * Демонстрирует использование Result для обработки ошибок.
 * 
 * @param a Делимое
 * @param b Делитель
 * @return Result Успешный результат с частным или ошибка при делении на ноль
 */
Result divide(int a, int b) {
    // Проверяем, что делитель не равен нулю
    if (b != 0) {
        // Выполняем деление
        double res = ((double)a / b);
        // Возвращаем успешный результат (макрос OK автоматически выделит память)
        return OK(res);
    }
    else {
        // Возвращаем ошибку при делении на ноль
        return ERR("Division by zero");
    }
}

/**
 * @brief Главная функция для демонстрации работы с Result.
 */
int main() {
    // Тест 1: Успешное деление
    Result res_divide1 = divide(10, 2);
    double *r1 = UNWRAP(&res_divide1, double);
    if (r1 != NULL) {
        printf("Result: %f\n", *r1);
    }
    else {
        printf("Error: %s\n", res_divide1.Err_message);
    }
    result_free(&res_divide1);

    // Тест 2: Деление на ноль (ошибка)
    Result res_divide2 = divide(10, 0);
    double *r2 = UNWRAP(&res_divide2, double);
    if (r2 != NULL) {
        printf("Result: %f\n", *r2);
    }
    else {
        printf("Error: %s\n", res_divide2.Err_message);
    }
    result_free(&res_divide2);
    
    return 0;
}