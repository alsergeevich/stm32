#include <string.h>
#include "menu.h"

#include <stdio.h>

/// Функция инициализации меню
void menu_init(menu_context_t *ctx, menu_item_t *root_menu) {
    if (ctx == NULL || root_menu == NULL) return;

    ctx->current_menu = root_menu; //устанавливаем указатель на массив корневого меню
    ctx->selected_index = 0; //сбрасываем индекс на начало списка
    ctx->stack_top = -1; //устанавливаем признак пустого стека переходов
}

/// Функция для вычисления длины меню (подменю)
int calculate_menu_length(const menu_item_t * menu) {
    int length = 0;

    if (menu == NULL) {
        return 0;
    }

    while (menu[length].title != NULL) {
        length++;
    }

    return length;
}

/// Функция для передвижения по меню вверх, реализовано цикличное передвижение
void menu_move_up (menu_context_t *ctx) {
    if (ctx == NULL) return;
    if (ctx->current_menu == NULL) return;

    if (ctx->selected_index == 0) { //если достигли самого первого пункта и снова нажали вверх, то переходим в конец меню
        ctx->selected_index = calculate_menu_length(ctx->current_menu) - 1;
    } else {
        ctx->selected_index--;
    }
}

/// Функция для передвижения по меню вниз, реализовано цикличное передвижение
void menu_move_down(menu_context_t *ctx) {
    if (ctx == NULL) return;
    if (ctx->current_menu == NULL) return;

    if (ctx->selected_index == calculate_menu_length(ctx->current_menu) - 1) { //если достигли последнего пункта и снова нажали вниз, то переходим в начало меню
        ctx->selected_index = 0;
    } else {
        ctx->selected_index++;
    }
}

/// Функция обработки нажатия кнопки отвечающей за Ввод
void menu_enter(menu_context_t *ctx) {
    if (ctx == NULL) return;
    if (ctx->current_menu == NULL) return;

    const menu_item_t * selected_item = &ctx->current_menu[ctx->selected_index]; //получаем выбранный пункт меню

    if (selected_item->function_action != NULL && selected_item->submenu == NULL) { //если пункт содержит только действие, то выполняем его и выходим
        selected_item->function_action();
        return;
    }
    if (selected_item->function_action == NULL && selected_item->submenu != NULL) { //если пункт содержит только подменю, то проваливаемся в него
        if (ctx->stack_top < STAСK_SIZE - 1) { //проверяем не переполнен ли стек переходов
            ctx->stack_top++; //увеличиваем счётчик переходов
            ctx->stack[ctx->stack_top] = ctx->current_menu; //сохраняем в стек текущий пункт меню для возврата

            ctx->current_menu = selected_item->submenu; //переходим в подменю
            ctx->selected_index = 0; //устанавливаем начальное положение в меню
        }
    } else if (selected_item->function_action != NULL && selected_item->submenu != NULL) { //если пункт имеет и действие и подменю
        selected_item->function_action(); //выполняем действие

        if (ctx->stack_top < STAСK_SIZE - 1) { //переходим в подменю
            ctx->stack_top++;
            ctx->stack[ctx->stack_top] = ctx->current_menu;

            ctx->current_menu = selected_item->submenu;
            ctx->selected_index = 0;
        }
    }
}

/// Функция для возврата из подменю
void menu_back(menu_context_t *ctx) {
    if (ctx == NULL) return;

    if(ctx->stack_top >= 0) { //если в стеке что-то есть
        ctx->current_menu = ctx->stack[ctx->stack_top]; //извлекаем предыдущее меню
        ctx->stack_top--; //уменьшаем счётчик переходов
    }

    ctx->selected_index = 0; //устанавливаем начальное положение в меню куда вернулись
}

/// Функция для вывода меню.
/// Принимает контекст меню и указатель на пользовательскую функцию для формирования вывода.
void menu_display(const menu_context_t *ctx, void(*display_callback)(const char* title, int index, int is_selected)) {
    if (ctx == NULL || display_callback == NULL) return;
    if (ctx->current_menu == NULL) return;

    int length_menu = calculate_menu_length(ctx->current_menu);

    for(int i = 0; i < length_menu; ++i) {
        display_callback(ctx->current_menu[i].title, i, (ctx->selected_index == i));
    }
}

/// Функция для обработки действий с меню, принимает контекст и номер действия от 1 до 4
void menu_handle_input(menu_context_t *ctx, int input) {
    if (ctx == NULL) return;

    switch (input) {
        case KEY_UP:    menu_move_up(ctx);   break;
        case KEY_DOWN:  menu_move_down(ctx); break;
        case KEY_ENTER: menu_enter(ctx);     break;
        case KEY_BACK:  menu_back(ctx);      break;
    }
    getchar();
}
