#include "vector.h"


//инициализация вектора 1-параметр указатель на структуру vector_t, 2-размер элемента(передаётся как sizeof(тип)) 3-ёмкость вектора
void vector_init(vector_t* vector, size_t element_size, size_t capacity) {
    
    if(vector == NULL) {
        return;
    }
    if (capacity == 0 || element_size == 0) {
        vector->error = 1;
        return;
    }
    
    vector->data = calloc(capacity, element_size);
    if (vector->data == NULL)
    {   
        vector->error = 1;
        return;
    }
    vector->error = 0;
    vector->size_vector = 0;
    vector->size_element = element_size;
    vector->capacity = capacity;
}

//добавляет элемент в конец вектора
void vector_push_back(vector_t* vector, void* element) {

    if(vector == NULL) {
        return;
    }
    vector->error = 0;
    if(vector->size_vector == vector->capacity) {
        vector->capacity *= 2;
        void *temp = realloc(vector->data, vector->capacity * vector->size_element);
        if (temp == NULL)
        {
            vector->error = 1;
            return;
        }
        vector->data = temp;    
    }
    memcpy((char*)vector->data + vector->size_vector * vector->size_element, element, vector->size_element);
    vector->size_vector++;
}

//получение элемента по индексу
void* get_element_by_index(vector_t* vector, size_t index) {
    if(vector == NULL) {
        return NULL;
    }
    if(index >= vector->size_vector) {
        vector->error = 1;
        return NULL;
    }
    vector->error = 0;
    return (char*)vector->data + index * vector->size_element;
}

//возвращает последний элемент и удаляет его
void* vector_pop_back(vector_t* vector) {
    if(vector == NULL) {
        return NULL;
    }
    if(vector->size_vector == 0) {
        vector->error = 1;
        return NULL;
    }
    vector->error = 0;
    void* element_temp = (char*)vector->data + (vector->size_vector - 1) * vector->size_element;
    void* element = malloc(vector->size_element);
    if(element == NULL) {
        vector->error = 1;
        return NULL;
    }
    memcpy(element, element_temp, vector->size_element);
    vector->size_vector--;
    if(vector->capacity > vector->size_vector * 3) {
        vector->capacity /= 2;
        void *temp = realloc(vector->data, vector->capacity * vector->size_element);
        if (temp == NULL) {
            vector->error = 1;
            return element;
        }
        vector->data = temp;
    }
    
    return element;

}

//освобождает память после использования вектора
void vector_free(vector_t* vector) {
    if(vector == NULL) {
        return;
    }
    free(vector->data);
    vector->data = NULL;
    vector->size_vector = 0;
    vector->capacity = 0;
    vector->size_element = 0;
    vector->error = 0;
}

// возвращает текущий размер вектора (аналог std::vector.size())
size_t vector_size(vector_t* vector) { 
    if(vector == NULL) {
        return 0;
    }
    return vector->size_vector;
}

// возвращает текущую емкость вектора
size_t vector_capacity(vector_t* vector) {
    if(vector == NULL) {
        return 0;
    }
    return vector->capacity;
}

// проверяет, пустой ли вектор
size_t vector_is_empty(vector_t* vector) { 
    if(vector == NULL) {
        return 0;
    }
    return vector->size_vector == 0 ? 1 : 0;
}

// резервирует определенную емкость
void vector_reserve(vector_t* vector, size_t capacity) {
    if(vector == NULL) {
        return;
    }
    if (vector->capacity >= capacity)
    {
        vector->error = 0;
        return;
    }
    if(capacity == 0) {
        vector->error = 1;
        return;
    }
    vector->error = 0;
    void *temp = realloc(vector->data, capacity * vector->size_element);
    if (temp == NULL) {
        vector->error = 1;
        return;
    }
    vector->data = temp;
    memset((char*)vector->data + vector->size_vector * vector->size_element, 0, (capacity - vector->size_vector) * vector->size_element);
    vector->capacity = capacity;
}

// очищает содержимое вектора без освобождения самой структуры
void vector_clear(vector_t* vector) {
    if(vector == NULL) {
        return;
    }
    vector->size_vector = 0;
    vector->error = 0;
}

// вставка элемента в произвольную позицию
void vector_insert(vector_t* vector, size_t index, void* element) {
    if(vector == NULL || element == NULL) {
        return;
    }
    if(index > vector->size_vector) {
        vector->error = 1;
        return;
    }
    if(vector->size_vector == vector->capacity) {
        vector_reserve(vector, vector->capacity * 2);
    }
    void* temp_r = malloc((vector->size_vector - index) * vector->size_element);
    if(temp_r == NULL) {
        vector->error = 1;
        return;
    }
    memcpy(temp_r, (char *)vector->data + index * vector->size_element, (vector->size_vector - index) * vector->size_element);
    memcpy((char*)vector->data + index * vector->size_element, element, vector->size_element);
    vector->size_vector++;
    memcpy((char*)vector->data + ((index + 1) * vector->size_element), temp_r, (vector->size_vector - index) * vector->size_element);
    free(temp_r);
}

//удаляет элемент по индексу
void vector_delete(vector_t* vector, size_t index) {
    if (vector == NULL) {
        return;
    }
    if (index >= vector->size_vector) {
        vector->error = 1;
        return;
    }
    vector->error = 0;
    if(index == vector->size_vector - 1) {
        vector_pop_back(vector);
    }

    void *temp_r = malloc((vector->size_vector - (index + 1)) * vector->size_element);
    if (temp_r == NULL)
    {
        vector->error = 1;
        return;
    }
    memcpy(temp_r, (char *)vector->data + (index + 1) * vector->size_element, (vector->size_vector - (index + 1)) * vector->size_element);
    vector->size_vector--;
    memcpy((char*)vector->data + (index * vector->size_element), temp_r, (vector->size_vector - index) * vector->size_element);
    free(temp_r);
}


