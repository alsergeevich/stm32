#include "resultHandler.h"

//тестовая функция деления двух чисел
Result divide(int a, int b) {
    if (b != 0) { // проверяем, что делитель не равен нулю
        double res = ((double)a / b); // выполняем деление
        return result_ok(&res); // возвращаем результат в структуре Result
    }
    else {
        return result_err("Division by zero"); // иначе возвращаем ошибку в структуре Result
    }
}


int main() {
    Result res_divide1 = divide(10, 2);
    if (res_divide1.is_Ok) {
        double *r = (double *) res_divide1.Ok_value;
        printf("Result: %f\n", *r);
    }
    else {
        printf("Error: %s\n", res_divide1.Err_message);
    }


    Result res_divide2 = divide(10, 0);
    if (res_divide2.is_Ok) {
        double *r = (double *) res_divide2.Ok_value;
        printf("Result: %f\n", *r);
    }
    else {
        printf("Error: %s\n", res_divide2.Err_message);
    }
}
