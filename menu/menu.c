#include "menu.h"
#include <string.h>


//функция инициализации меню
void menu_init(menu_context_t *ctx, menu_item_t *root_menu){
    if(ctx != NULL && root_menu != NULL) { //проверка на то, что контекст меню и корневое меню не нулл
        ctx->current_menu = root_menu; //устанавливаем указатель на массив корневого меню
        ctx->selected_index = 0; //сбрасываем индекс на начало списка
        ctx->stack_top = -1; //устанавливаем признак пустого стека переходов
    }
}

//функция для вычисления длины меню (подменю)
int calculate_menu_length(menu_item_t *menu){
    int length = 0;
    if(menu == NULL) {
        return 0;
    }
    while(menu[length].title != NULL) {
        length++;
    }
    return length;
}

//функция для передвижения по меню вверх, реализовано цикличное передвижение
void menu_move_up(menu_context_t *ctx) {
    if(ctx != NULL) {
        if(ctx->current_menu != NULL) {
            int menu_length = calculate_menu_length(ctx->current_menu);
            if(ctx->selected_index == 0) {                           //если достигли самого первого пункта и снова нажали вверх то переходим в конец меню
                ctx->selected_index = menu_length - 1;
            } else {
                ctx->selected_index--;
            }
        }
    }
}

//функция для передвижения по меню вниз, реализовано цикличное передвижение
void menu_move_down(menu_context_t *ctx) {
    if(ctx != NULL) {
        if(ctx->current_menu != NULL) {
            int menu_length = calculate_menu_length(ctx->current_menu);
            if(ctx->selected_index == menu_length - 1) {      //если достигли последнего пункта и снова нажали вниз то переходим в начало меню
                ctx->selected_index = 0;
            } else {
                ctx->selected_index++;
            }
        }
    }
}

//функция обработки нажатия кнопки отвечающей за Ввод
void menu_enter(menu_context_t *ctx) {
    if(ctx != NULL) {
        if(ctx->current_menu != NULL) {
            menu_item_t *selected_item = &ctx->current_menu[ctx->selected_index]; //получаем выбранный пункт меню
            if(selected_item->function_action != NULL && selected_item->submenu == NULL) { //если пункт содержит только действие, то выполняем его и выходим
                selected_item->function_action();
                return;

            } else if(selected_item->function_action == NULL && selected_item->submenu != NULL) { //если пункт содержит только подменю то проваливаемся в него
                if(ctx->stack_top < STAСK_SIZE - 1) { //проверяем не переполнен ли стек переходов
                    ctx->stack_top++; //увеличиваем счётчик переходов
                    ctx->stack[ctx->stack_top] = ctx->current_menu; //сохраняем в стек текущий пункт меню для возврата
                }
                ctx->current_menu = selected_item->submenu; //переходим в подменю
                ctx->selected_index = 0; //устанавливаем начальное положение в меню
                return;
            } else if(selected_item->function_action != NULL && selected_item->submenu != NULL) { //если пункт имеет и действие и подменю
                selected_item->function_action(); //выполняем действие
                if(ctx->stack_top < STAСK_SIZE - 1) { //переходим в подменю
                    ctx->stack_top++;
                    ctx->stack[ctx->stack_top] = ctx->current_menu;
                }
                ctx->current_menu = selected_item->submenu;
                ctx->selected_index = 0;
                return;
            }

        }
    }
}

//функция для возврата из подменю
void menu_back(menu_context_t *ctx) {
    if(ctx != NULL) {
        if(ctx->stack_top >= 0) { //если в стеке что-то есть
            ctx->current_menu = ctx->stack[ctx->stack_top]; //извлекаем предыдущее меню
            ctx->stack_top--; //уменьшаем счётчик переходов
        }

        ctx->selected_index = 0; //устанавливаем начальное положение в меню куда вернулись
    }
}

//функция для вывода меню.Принимает контекст меню и указатель на пользовательскую функцию для формирования вывода.
void menu_display(const menu_context_t *ctx, void(*display_callback)(const char* title, int index, int is_selected)) {
    if(ctx != NULL && display_callback != NULL) {
        if(ctx->current_menu != NULL) {
            int length_menu = calculate_menu_length(ctx->current_menu);

            for(int i = 0; i < length_menu; ++i) {

                display_callback(ctx->current_menu[i].title, i, (ctx->selected_index == i));
            }
        }
    }
}

//функция для обработки действий с меню, принимает контекст и номер действия от 1 до 4
void menu_handle_input(menu_context_t *ctx, int input) {
    if(ctx != NULL) {
        switch (input) {
        case KEY_UP:    menu_move_up(ctx);   break;
        case KEY_DOWN:  menu_move_down(ctx); break;
        case KEY_ENTER: menu_enter(ctx);     break;
        case KEY_BACK:  menu_back(ctx);      break;
        }
    }
}
