#include "resultHandler.h"
/*тут мы реализовали функции для обработки результата функции
обе функции возвращают структуру Result записав в неё результат и выставив флаг
is_Ok в true или false в зависимости от результата. Обработав возвращённую структуру в коде принимаем решение что из неё взять Ok_value или Err_message
Короче, это жалкое подобие Result из Rust, но всё же лучше чем тупо возвращать NULL и проверять его в коде или возвращать код ошибки
за счёт того, что применили указатель на void функция result_ok и поле Ok_value в структуре Result принимают любой тип данных
просто в коде надо привести результат к нужному типу*/

Result result_ok(void *value)
{
    Result result; // создаем переменную result типа Result
    result.Ok_value = value; // записываем в Ok_value значение value
    result.is_Ok = true; // устанавливаем is_Ok в true
    return result;
}

Result result_err(const char *message)
{
    Result result;
    strncpy(result.Err_message, message, sizeof(result.Err_message)-1); // копируем сообщение в result.Err_message
    result.Err_message[sizeof(result.Err_message)-1] = '\0'; // добавляем завершающий символ
    result.is_Ok = false; // устанавливаем is_Ok в false
    return result;
}


