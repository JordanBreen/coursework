//#include <ncursesw/ncurses.h>
#include <ncurses.h>
#include <stdarg.h>
#include <wchar.h>

#define UI_PAD 1

typedef struct UI {
  WINDOW
    *main_window,
    *view_window,
    *head_window,
    *log_window,
    *cmd_window;
  int
    min_x, min_y,
    max_x, max_y;
} UI;

UI * create_UI        (              );
void ui_refresh       ( UI     * ui  );
int  get_outer_width  ( WINDOW * win );
int  get_outer_height ( WINDOW * win );
int  get_inner_width  ( WINDOW * win );
int  get_inner_height ( WINDOW * win );
// void view_window_fill ( UI * ui, wchar_t wchar );
void view_window_fill ( UI * ui, char ch );



