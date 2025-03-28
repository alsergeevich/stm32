# Инструкция по работе с библиотекой для создания меню.

## Создание меню.
Подключаем к проекту файлы [`menu.h`](../menu.h) и [`menu.c`](../menu.c)

Меню, или подменю, состоят из элементов, которые представляют собой пункт меню в виде структуры:
```c
typedef struct menu_item_t
{
    const char *title;
    void(*function_action)(void);
    struct menu_item_t *submenu;
} menu_item_t;
```

где 
- `const char *title` – название пункта, 
- `void(*function_action)(void)` – указатель на функцию которая выполнится при выборе данного пункта, если не требуется никакого действия инициализируйте данное поле `NULL`, 
- `struct menu_item_t *submenu` – указатель на массив элементов подменю, если подменю нет, инициализируйте данное поле `NULL`.

Первое:
Создаём функции для действий в каждом пункте меню, например:
```c
void action_item_1() {
    printf("\nRun action: Item 1\n");
}
void action_item_2() {
    printf("\nRun action: Item 2\n");
}
void action_item_3() {
    printf("\nRun action: Item 3\n");
}
```

Прототип указателя на функцию при необходимости можно изменить в файле [`menu.h`](../menu.h), по умолчанию он имеет вид `void(*function_action)(void)`;
 
Создаём необходимое количество подменю, например:
```c
// Создание подменю
menu_item_t submenu_items[] = {
    {"Subitem 1", action_item_3, NULL},
    {"Subitem 2", NULL, NULL},
    {NULL, NULL, NULL} // Завершающий элемент
};
```

После этого создаём массив элементов `menu_item_t`, которые будут представлять корневое меню. Например:
```c
// Создание корневого меню
menu_item_t root_menu_items[] = {
    {"Item 1", action_item_1, NULL},
    {"Item 2", action_item_2, submenu_items},
    {"Item 3", NULL, NULL},
    {NULL, NULL, NULL} // Завершающий элемент
};
```

Каждый список меню или подменю обязательно должен заканчиваться элементом у которого поля инициализированы `NULL`, например:
`{NULL, NULL, NULL}` это важно !

Следующий шаг, это создание контекста меню через который и будем работать дальше:

```c
menu_context_t ctx;
```

И вызов функции инициализации меню:

```c
menu_init(&ctx, root_menu_items);
```

В которую необходимо передать контекст и массив элементов, содержащий представление корневое меню.
По умолчанию степень вложенности меню ограничена 5, это значение можно изменить в файле menu.h изменив #define STAСK_SIZE 5

Для обработки пользовательского ввода и передвижения по меню предназначена функция:

```c
void menu_handle_input(menu_context_t *ctx, int input);
```

Которая принимает контекст и число от 1 до 4.
- 1 – вверх,
- 2 – вниз,
- 3 – ввод,
- 4 – возврат.

Всё передвижение по меню вверх или вниз, циклично.

Для вывода пунктов меню куда-либо предназначена функция:

```c
void menu_display(const menu_context_t *ctx, void(*display_callback)(const char*, int, int));
```

Которая принимает контекст и указатель на пользовательскую функцию для формирования необходимого вида пунктов меню. Прототип указателя на функцию имеет вид:

```c
void(*display_callback) (const char*, int, int);
```

Где первый аргумент — это название пункта, второй аргумент индекс пункта, третий аргумент указывает на то выбран пункт или нет.

Пример:
```c
void display_callback(const char *title, int index, int is_selected) {
    if (is_selected) {
        printf("> %s\n", title); // Выбранный пункт выделяется символом ">"
    } else {
        printf("  %s\n", title); // Остальные пункты без выделения
    }
}
```

Тут мы не задействовали `index`.

Пример реализации меню для отображения в терминале `windows`:

```c
#include <stdio.h>
#include <conio.h> // Для функции _getch() в винде
#include "menu.h"
// Пример функций действий
void action_item_1() {
    printf("\nRun action: Item 1\n");
}
void action_item_2() {
    printf("\nRun action: Item 2\n");
}
void action_item_3() {
    printf("\nRun action: Item 3\n");
}
// Пример Callback-функции для вывода в терминал
void display_callback(const char *title, int index, int is_selected) {
    if (is_selected) {
        printf("> %s\n", title); // Выбранный пункт выделяется символом ">"
    } else {
        printf("  %s\n", title); // Остальные пункты без выделения
    }
}
// Функция для получения пользовательского ввода
int get_user_input() {
    char ch = _getch(); // Считываем нажатую клавишу
    switch (ch) {
    case 'w': return KEY_UP;    // Стрелка вверх
    case 's': return KEY_DOWN;  // Стрелка вниз
    case '\r': return KEY_ENTER; // Enter
    case 'b': return KEY_BACK;  // Back
    default: return -1;         // Некорректный ввод, в мк это можно не добавлять
    }
}

int main() {
    // Создание подменю
    menu_item_t submenu_items[] = {
        {"Subitem 1", action_item_3, NULL},
        {"Subitem 2", NULL, NULL},
        {NULL, NULL, NULL} // Завершающий элемент
    };

    // Создание корневого меню
    menu_item_t root_menu_items[] = {
        {"Item 1", action_item_1, NULL},
        {"Item 2", action_item_2, submenu_items},
        {"Item 3", NULL, NULL},
        {NULL, NULL, NULL} // Завершающий элемент
    };

    // Инициализация контекста меню
    menu_context_t ctx;
    menu_init(&ctx, root_menu_items);

    printf("=== Menu is run ===\n");
    printf("Use:\n");
    printf("'w' - Up, 's' - Down, Enter - Set, 'b' - Back\n");

    while (1) {
        // Отображение текущего меню
        menu_display(&ctx, display_callback);
        // Получение пользовательского ввода
        int input = get_user_input();
        if (input == -1) {    //в мк это не нужно, так для примера
            printf("\nIncorrect input. Try again.\n");
            continue;
        }

        // Обработка ввода
        menu_handle_input(&ctx, input)
        printf("\n");
    }
  return 0;
}
```
