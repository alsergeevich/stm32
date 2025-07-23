#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct vector
{
    size_t size_element;
    void *data;
    size_t size_vector;
    size_t capacity;
    size_t error; // устанавливается в 1 при ошибке и 0 если всё ок

} vector_t;

// инициализация вектора 1-параметр указатель на структуру vector_t, 2-размер элемента(передаётся как sizeof(тип)) 3-ёмкость вектора
void vector_init(vector_t *vector, size_t element_size, size_t capacity);

// добавляет элемент в конец вектора
void vector_push_back(vector_t *vector, void *element);

// получение элемента по индексу
void *get_element_by_index(vector_t *vector, size_t index);

// возвращает последний элемент и удаляет его
void *vector_pop_back(vector_t *vector);

// освобождает память после использования вектора
void vector_free(vector_t *vector);

// возвращает текущий размер вектора (аналог std::vector.size())
size_t vector_size(vector_t *vector);

// возвращает текущую емкость вектора
size_t vector_capacity(vector_t *vector);

// проверяет, пустой ли вектор
size_t vector_is_empty(vector_t *vector);

// резервирует определенную емкость
void vector_reserve(vector_t *vector, size_t capacity);

// очищает содержимое вектора без освобождения самой структуры
void vector_clear(vector_t *vector);

// вставка элемента в произвольную позицию
void vector_insert(vector_t *vector, size_t index, void *element);

// удаляет элемент по индексу
void vector_delete(vector_t *vector, size_t index);

/*########################################################################################################*/
/*

gcc -o main main.c vector.c

int main () {
    vector_t vector;                                                                                    создаём вектор
    int num;                                                                                            создаём переменную через которую будем заполнять вектор
    vector_init(&vector, sizeof(int), 12);                                                              инициализируем вектор, вектор будет содержать элементы типа int, начальная ёмкость вектора 12 элементов
    for(int i = 0; i < 10; i++) {                                                                       заполняем вектор элементами
        num = i;
        vector_push_back(&vector, &num);                                                                 добавляем элементы в конец вектора
    }
    printf("size vector %d\n", vector_size(&vector));                                                   выводим размер вектора
    printf("capacity vector %d\n", vector_capacity(&vector));                                           выводим емкость вектора
    printf("Print vector elements:\n");
    for(int i = 0; i < vector_size(&vector); i++) {
        printf("%d ", *(int *)get_element_by_index(&vector, i));                                        выводим элементы вектора
    }
    puts("\n");
    printf("Element index 5 :%d\n", *(int*)get_element_by_index(&vector, 5));                           выводим элемент по индексу 5
    printf("Element index 2 :%d\n", *(int*)get_element_by_index(&vector, 2));                           выводим элемент по индексу 2
    printf("pop_back : %d\n", *(int*)vector_pop_back(&vector));                                         выводим последний элемент вектора и удаляем его
    printf("size vector %d\n", vector_size(&vector));                                                   выводим размер вектора
    printf("Print vector elements:\n");
    for (int i = 0; i < vector_size(&vector); i++)
    {
        printf("%d ", *(int *)get_element_by_index(&vector, i));                                        выводим элементы вектора после удаления последнего элемента
    }
    puts("\n");
    if (vector_is_empty(&vector)) {                                                                     проверяем пустой вектор или нет
        printf("empty\n");
    } else {
        printf("not empty\n");
    }
    printf("Before reserve %d\n", vector_capacity(&vector));                                            выводим емкость вектора до увеличения емкости
    vector_reserve(&vector, 20); увеличиваем ёмкость вектора
    printf("After reserve %d\n", vector_capacity(&vector));                                             выводим емкость вектора после увеличения емкости
    printf("before deletion element index 5 %d\n", vector_size(&vector));                               выводим размер вектора до удаления элемента
    vector_delete(&vector, 5); удаляем элемент по индексу 5
    printf("after deletion element index 5 %d\n", vector_size(&vector));                                выводим размер вектора после удаления элемента
    printf("Print vector elements:\n");
    for (int i = 0; i < vector_size(&vector); i++)
    {
        printf("%d ", *(int *)get_element_by_index(&vector, i));                                        выводим элементы вектора
    }
    puts("\n");
    vector_clear(&vector);                                                                              очищаем вектор
    puts("After clear\n");
    if (vector_is_empty(&vector))                                                                       проверяем пустой вектор или нет
    {
        printf("empty\n");
    }
    else
    {
        printf("not empty\n");
    }
    //очищаем память от для элементов
    for(int i = 0; i < vector_size(&vector); i++) {
        free(get_element_by_index(&vector, i));
    }
    //очищаем сам вектор
    vector_free(&vector);
}
*/
/*##############################################################################################################*/
/*
size vector 10
capacity vector 12
Print vector elements:
0 1 2 3 4 5 6 7 8 9

Element index 5 :5
Element index 2 :2
pop_back : 9
size vector 9
Print vector elements:
0 1 2 3 4 5 6 7 8

not empty
Before reserve 12
After reserve 20
before deletion element index 5 9
after deletion element index 5 8
Print vector elements:
0 1 2 3 4 6 7 8

After clear

empty
*/