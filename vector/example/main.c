#include "vector.h"

int main()
{
    vector_t vector;
    int num;
    vector_init(&vector, sizeof(int), 12);
    for (int i = 0; i < 10; i++)
    {
        num = i * 2;
        vector_push_back(&vector, &num);
    }
    printf("size vector %d\n", vector_size(&vector));
    printf("capacity vector %d\n", vector_capacity(&vector));
    printf("Print vector elements:\n");
    for (int i = 0; i < vector_size(&vector); i++)
    {
        printf("%d ", *(int *)get_element_by_index(&vector, i));
    }
    puts("\n");
    printf("Element index 5 :%d\n", *(int *)get_element_by_index(&vector, 5));
    printf("Element index 2 :%d\n", *(int *)get_element_by_index(&vector, 2));
    printf("pop_back : %d\n", *(int *)vector_pop_back(&vector));
    printf("size vector %d\n", vector_size(&vector));
    printf("Print vector elements:\n");
    for (int i = 0; i < vector_size(&vector); i++)
    {
        printf("%d ", *(int *)get_element_by_index(&vector, i));
    }
    puts("\n");
    if (vector_is_empty(&vector))
    {
        printf("empty\n");
    }
    else
    {
        printf("not empty\n");
    }
    int el = 4555;
    vector_insert(&vector, 3, &el);
    el = 1230;
    vector_insert(&vector, 5, &el);
    printf("Print vector elements:\n");
    for (int i = 0; i < vector_size(&vector); i++)
    {
        printf("%d ", *(int *)get_element_by_index(&vector, i));
    }
    puts("\n");
    printf("Before reserve %d\n", vector_capacity(&vector));
    vector_reserve(&vector, 20);
    printf("After reserve %d\n", vector_capacity(&vector));
    printf("before deletion element index 5 %d\n", vector_size(&vector));
    vector_delete(&vector, 5);
    printf("after deletion element index 5 %d\n", vector_size(&vector));
    printf("Print vector elements:\n");
    for (int i = 0; i < vector_size(&vector); i++)
    {
        printf("%d ", *(int *)get_element_by_index(&vector, i));
    }
    puts("\n");
    vector_clear(&vector);
    puts("After clear\n");
    if (vector_is_empty(&vector))
    {
        printf("empty\n");
    }
    else
    {
        printf("not empty\n");
    }

    // очищаем сам вектор
    vector_free(&vector);
}