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

// Пример функции для получения пользовательского ввода
int get_user_input() {
#ifdef _WIN32
    char ch = _getch();
#else
    char ch = (char) getchar();
#endif
    switch (ch) {
    case 'w': return KEY_UP;    // Стрелка вверх
    case 's': return KEY_DOWN;  // Стрелка вниз
    case '\n': return KEY_ENTER; // Enter
    case 'b': return KEY_BACK;  // Back
    default: return -1;         // Некорректный ввод
    }
}

[[noreturn]] void main() {
    // Создание подменю
    menu_item_t submenu_items[] = {
        {"Subitem 1", action_item_3, nullptr},
        {"Subitem 2", nullptr, nullptr},
        {nullptr, nullptr, nullptr} // Завершающий элемент
    };

    // Создание корневого меню
    menu_item_t root_menu_items[] = {
        {"Item 1", action_item_1, nullptr},
        {"Item 2", action_item_2, submenu_items},
        {"Item 3", nullptr, nullptr},
        {nullptr, nullptr, nullptr} // Завершающий элемент
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
        if (input == -1) {
            printf("\nIncorrect input. Try again.\n");
            continue;
        }

        // Обработка ввода
        menu_handle_input(&ctx, input);
        printf("\n");
    }
}
