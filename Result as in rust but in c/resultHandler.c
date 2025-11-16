#include "resultHandler.h"

// Сообщение по умолчанию при передаче NULL в result_err
static const char DEFAULT_ERROR_MSG[] = "Unknown error occurred";

/**
 * @brief Создаёт результат с ошибкой (внутренняя функция).
 * 
 * Используется макросом ERR() и при ошибках выделения памяти.
 * Не предназначена для прямого использования - используйте макрос ERR().
 * 
 */
Result result_err(char const *const message)
{
    // Инициализация структуры Result с ошибкой
    Result result = {
        .Ok_value = NULL,  // Обнуляем указатель на значение
        .is_Ok = false      // Устанавливаем флаг ошибки
    };
    
    // Копируем сообщение об ошибке (с обработкой NULL)
    if (message == NULL) {
        // Если передан NULL, используем сообщение по умолчанию
        strncpy(result.Err_message, DEFAULT_ERROR_MSG, sizeof(result.Err_message) - 1);
    } else {
        // Копируем переданное сообщение
        strncpy(result.Err_message, message, sizeof(result.Err_message) - 1);
    }
    
    // Гарантируем завершение строки нулём (защита от переполнения)
    result.Err_message[sizeof(result.Err_message) - 1] = '\0';
    
    return result;
}

/**
 * @brief Освобождает память, выделенную для Result.
 * 
 * Безопасно вызывать даже для результатов с ошибкой (ничего не произойдёт).
 * После вызова Ok_value будет установлен в NULL.
 */
void result_free(Result *result)
{
    // Проверка на NULL указатель
    if (result == NULL) {
        return;
    }
    
    // Освобождаем память только если результат успешен и память была выделена
    if (result->is_Ok && result->Ok_value != NULL) {
        free(result->Ok_value);
        result->Ok_value = NULL;  // Обнуляем указатель для безопасности
    }
}

/**
 * @brief Вспомогательная функция для автоматического выделения памяти (внутренняя).
 * 
 * Выделяет память, копирует значение и создаёт успешный результат.
 * Используется макросом OK().
 * Не предназначена для прямого использования - используйте макрос OK().
 * 
 */
Result _result_ok_alloc(size_t size, const void *value)
{
    // Выделяем память для значения
    void *ptr = malloc(size);
    
    // Проверяем успешность выделения памяти
    if (ptr == NULL) {
        // Если память не выделена, возвращаем ошибку
        return result_err("Memory allocation failed");
    }
    
    // Копируем значение в выделенную память
    memcpy(ptr, value, size);
    
    // Создаём структуру Result с успешным результатом
    Result result = {
        .Ok_value = ptr,  // Сохраняем указатель на выделенную память
        .is_Ok = true       // Устанавливаем флаг успеха
    };
    
    // Очищаем поле сообщения об ошибке
    memset(result.Err_message, 0, sizeof(result.Err_message));
    
    return result;
}