#include "resultHandler.h"
#include <assert.h>

/**
 * @brief Сообщение по умолчанию при передаче NULL в result_err
 */
static const char DEFAULT_ERROR_MSG[] = "Unknown error occurred";

Result result_ok(void *const value)
{
    // Проверка на NULL
    assert(value != NULL && "Value cannot be NULL in result_ok");
    
    Result result = {
        .Ok_value = value,
        .is_Ok = true
    };
    // Инициализируем Err_message нулями для чистоты
    memset(result.Err_message, 0, sizeof(result.Err_message));
    
    return result;
}

Result result_err(char const *const message)
{
    Result result = {
        .Ok_value = NULL,  // Явно обнуляем указатель
        .is_Ok = false
    };
    
    // Обработка NULL указателя
    if (message == NULL) {
        strncpy(result.Err_message, DEFAULT_ERROR_MSG, sizeof(result.Err_message) - 1);
    } else {
        strncpy(result.Err_message, message, sizeof(result.Err_message) - 1);
    }
    
    // Гарантируем, что строка завершена нулём
    result.Err_message[sizeof(result.Err_message) - 1] = '\0';
    
    return result;
}