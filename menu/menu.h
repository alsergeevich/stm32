#ifndef MENU_H
#define MENU_H

#define STAСK_SIZE 5
#define KEY_UP 1
#define KEY_DOWN 2
#define KEY_ENTER 3
#define KEY_BACK 4


typedef struct menu_item_t
{
    const char *title;
    void(*function_action)(void);
    struct menu_item_t *submenu;
} menu_item_t;


typedef struct menu_context_t {
    menu_item_t *current_menu;
    int selected_index;
    menu_item_t*  stack[STAСK_SIZE];
    int stack_top;
} menu_context_t;


void menu_init(menu_context_t *ctx, menu_item_t *root_menu);

//void menu_move_up(menu_context_t *ctx);
//void menu_move_down(menu_context_t *ctx);
//void menu_enter(menu_context_t *ctx);
//void menu_back(menu_context_t *ctx);

void menu_display(const menu_context_t *ctx, void(*display_callback)(const char*, int, int));
void menu_handle_input(menu_context_t *ctx, int input);

int calculate_menu_length(menu_item_t *menu);


#endif //MENU_H
