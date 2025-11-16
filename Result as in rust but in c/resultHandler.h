#pragma once
#include <stdbool.h>  // для типа bool
#include <string.h>   // для memset, strncpy
#include <stdlib.h>   // для malloc, free


/**
 * @brief Структура для обработки результата функции в стиле Rust Result.
 * 
 * Позволяет возвращать либо успешный результат (Ok), либо сообщение об ошибке (Err).
 * Поле is_Ok указывает, содержит ли структура валидный результат.
 * 
 * @note Память, на которую указывает Ok_value, автоматически выделяется макросами.
 *       Необходимо вызывать result_free() для освобождения памяти.
 */
typedef struct Result
{
    void *Ok_value;      ///< Указатель на успешный результат (если is_Ok == true)
    char Err_message[50]; ///< Сообщение об ошибке (если is_Ok == false)
    bool is_Ok;          ///< Флаг, указывающий на успешность операции
} Result;

/**
 * @brief Освобождает память, выделенную для Result.
 * 
 * @param result Указатель на структуру Result для освобождения.
 *               После вызова Ok_value будет установлен в NULL.
 */
void result_free(Result *result);

// Внутренние функции - объявлены только для использования макросами OK() и ERR()
// НЕ ИСПОЛЬЗУЙТЕ ИХ НАПРЯМУЮ! Используйте макросы вместо них.
Result _result_ok_alloc(size_t size, const void *value);
Result result_err(char const *const message);

/**
 * @brief Макрос для создания успешного результата с автоматическим выделением памяти.
 * 
 * Автоматически выделяет память для значения и копирует его туда.
 * 
 * @param value Значение любого типа, которое будет скопировано в выделенную память.
 * @return Result Структура с установленным флагом is_Ok = true.
 * 
 * @example
 *   double res = 5.0;
 *   return OK(res);  // Автоматически выделит память и скопирует значение
 */
#define OK(value) _result_ok_alloc(sizeof(value), &(value))

/**
 * @brief Макрос для результата с ошибкой.
 * 
 * @param message Строковый литерал с сообщением об ошибке.
 * @return Result Структура с установленным флагом is_Ok = false.
 * 
 * @example
 *   return ERR("Division by zero");
 */
#define ERR(message) result_err(message)

/**
 * @brief Макрос для безопасного извлечения значения из Result.
 * 
 * Проверяет, что результат успешен, и возвращает указатель на значение.
 * Если результат содержит ошибку, возвращает NULL.
 * 
 * @param result Указатель на структуру Result.
 * @param type Тип значения, которое нужно извлечь.
 * @return Указатель на значение или NULL, если результат содержит ошибку.
 * 
 * @example
 *   Result res = divide(10, 2);
 *   double *value = UNWRAP(&res, double);
 *   if (value != NULL) {
 *       printf("Result: %f\n", *value);
 *   }
 */
#define UNWRAP(result, type) \
    ((result)->is_Ok ? ((type *)(result)->Ok_value) : NULL)

