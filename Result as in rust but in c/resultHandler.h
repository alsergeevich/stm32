#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//структура для обработки результата функции
typedef struct Result
{
    void *Ok_value;
    char Err_message[50];
    bool is_Ok;
} Result;

//функция для обработки результата Ok
Result result_ok(void *value);

//функция для обработки результата Err
Result result_err(const char *message);