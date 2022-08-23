#include <stdio.h>
#include <stdlib.h>
//#include <ncursesw/ncurses.h>
#include "gui.h"

UI *create_UI() { 
  UI *ui = (UI *) malloc(sizeof(UI));
  ui->min_y = 0;
  ui->min_x = 0;
  ui->max_y = LINES;
  ui->max_x = COLS;
  
  int main_height = ui->max_y - UI_PAD;
  int main_width  = ui->max_x;
  int main_y      = ui->min_y;
  int main_x      = ui->min_x;

  int inner_width = main_width - UI_PAD * 2;
  int inner_y     = main_y + UI_PAD;
  int inner_x     = main_x + UI_PAD;
    
  int view_height = ui->max_y / 2 - UI_PAD * 2 + 10;
  int view_width  = inner_width;
  int view_y      = main_y + UI_PAD * 2;
  int view_x      = inner_x;

  int head_height = UI_PAD;
  int head_width  = inner_width;
  int head_y      = inner_y;
  int head_x      = inner_x;

  int log_height = main_height - view_height - 4;
  int log_width  = inner_width;
  int log_y      = view_y + view_height;
  int log_x      = inner_x;

  int cmd_height = UI_PAD;
  int cmd_width  = inner_width;
  int cmd_y      = log_y + log_height;
  int cmd_x      = inner_x;

  ui->main_window = newwin(main_height, main_width, main_y, main_x);
  ui->view_window = newwin(view_height, view_width, view_y, view_x);
  ui->head_window = newwin(head_height, head_width, head_y, head_x);
  ui->log_window  = newwin(log_height,  log_width,  log_y,  log_x );
  ui->cmd_window  = newwin(cmd_height,  cmd_width,  cmd_y,  cmd_x );
  
  box(ui->main_window, 0, 0);
  box(ui->view_window, 0, 0);
  box(ui->log_window,  0, 0);

  // view_window_fill (ui, (wchar_t)(14844830));
  view_window_fill (ui, '.');

  ui_refresh(ui);
  
  return ui;
}

int  get_outer_width  ( WINDOW * win )     { return getmaxx(win) - getcurx(win); }
int  get_outer_height ( WINDOW * win )     { return getmaxy(win) - getcury(win); }
int  get_inner_width  ( WINDOW * win )     { return get_outer_width  (win) - 2;  }
int  get_inner_height ( WINDOW * win )     { return get_outer_height (win) - 2;  }
// void view_window_fill ( UI * ui, wchar_t wchar ) {
void view_window_fill ( UI * ui, char ch ) {
  int
    x = getbegx (ui->view_window),
    y = getbegy (ui->view_window),
    w  = get_inner_width (ui->view_window),
    h = get_inner_height (ui->view_window);
  mvwaddch (ui->view_window, --y, x, ch);
  for (int i=y; i<=h; i++)
    for (int j=x; j<=w; j++)
      mvwaddch (ui->view_window, i, j, ch);
}
 
void ui_refresh (UI *ui) {
  wrefresh(ui->main_window);
  wrefresh(ui->view_window);
  wrefresh(ui->head_window);
  wrefresh(ui->log_window);
  wrefresh(ui->cmd_window);
}

