#include <stdio.h>
#include <conio.h>

#include "kernel.h"
#include "sem.h"

static class _semafor onlyOne(1);

void Intrare::operator>>(char *str)
{
  int tmp_x, tmp_y, tmp_x_len, tmp_y_len, tmp_color, tmp_cx, tmp_cy;
  if (_executor::tabela_procese[_executor::proces_curent].active == ACTIVE)
  {
    onlyOne.P();
    tmp_x = _executor::tabela_procese[_executor::proces_curent].x_pos;
    tmp_y = _executor::tabela_procese[_executor::proces_curent].y_pos;
    tmp_x_len = _executor::tabela_procese[_executor::proces_curent].x_len;
    tmp_y_len = _executor::tabela_procese[_executor::proces_curent].y_len;
    tmp_color = _executor::tabela_procese[_executor::proces_curent].color;
    tmp_cx = _executor::tabela_procese[_executor::proces_curent].x_cursor;
    tmp_cy = _executor::tabela_procese[_executor::proces_curent].y_cursor;

    window(tmp_x, tmp_y, tmp_x + tmp_x_len, tmp_y + tmp_y_len);
    textbackground(BLACK);
    //clrscr();

    if (tmp_cy == 1) tmp_cy++;
    gotoxy(tmp_cx, tmp_cy);
    cscanf("%s", str);

    _executor::tabela_procese[_executor::proces_curent].x_cursor = wherex();
    _executor::tabela_procese[_executor::proces_curent].y_cursor = wherey();

    // scrie antetul
    char* temp = new char[tmp_x_len + 2];
    for(int i = 0; i < tmp_x_len + 1; i++) temp[i] = ' ';
    temp[tmp_x_len + 1] = '\0';

    textbackground(tmp_color);
    gotoxy(1,1);
    cprintf("%s\n", temp);
    gotoxy(1,1);
    cprintf("%s\n", _executor::tabela_procese[_executor::proces_curent].nume);

    onlyOne.V();
  }
}

void Intrare::operator>>(int *i)
{
  int tmp_x, tmp_y, tmp_x_len, tmp_y_len, tmp_color, tmp_cx, tmp_cy;
  if (_executor::tabela_procese[_executor::proces_curent].active == ACTIVE)
  {
    onlyOne.P();
    tmp_x = _executor::tabela_procese[_executor::proces_curent].x_pos;
    tmp_y = _executor::tabela_procese[_executor::proces_curent].y_pos;
    tmp_x_len = _executor::tabela_procese[_executor::proces_curent].x_len;
    tmp_y_len = _executor::tabela_procese[_executor::proces_curent].y_len;
    tmp_color = _executor::tabela_procese[_executor::proces_curent].color;
    tmp_cx = _executor::tabela_procese[_executor::proces_curent].x_cursor;
    tmp_cy = _executor::tabela_procese[_executor::proces_curent].y_cursor;

    window(tmp_x, tmp_y, tmp_x + tmp_x_len, tmp_y + tmp_y_len);
    textbackground(BLACK);
    //clrscr();

    if (tmp_cy == 1) tmp_cy++;
    gotoxy(tmp_cx, tmp_cy);
    cscanf("%d", i);

    _executor::tabela_procese[_executor::proces_curent].x_cursor = wherex();
    _executor::tabela_procese[_executor::proces_curent].y_cursor = wherey();

    // scrie antetul
    char* temp = new char[tmp_x_len + 2];
    for(int i = 0; i < tmp_x_len + 1; i++) temp[i] = ' ';
    temp[tmp_x_len + 1] = '\0';

    textbackground(tmp_color);
    gotoxy(1,1);
    cprintf("%s\n", temp);
    gotoxy(1,1);
    cprintf("%s\n", _executor::tabela_procese[_executor::proces_curent].nume);

    onlyOne.V();
  }
}

void Iesire::operator<<(int *i)
{
  int tmp_x, tmp_y, tmp_x_len, tmp_y_len, tmp_color, tmp_cx, tmp_cy;
  if (_executor::tabela_procese[_executor::proces_curent].active == ACTIVE)
  {
    onlyOne.P();
    tmp_x = _executor::tabela_procese[_executor::proces_curent].x_pos;
    tmp_y = _executor::tabela_procese[_executor::proces_curent].y_pos;
    tmp_x_len = _executor::tabela_procese[_executor::proces_curent].x_len;
    tmp_y_len = _executor::tabela_procese[_executor::proces_curent].y_len;
    tmp_color = _executor::tabela_procese[_executor::proces_curent].color;
    tmp_cx = _executor::tabela_procese[_executor::proces_curent].x_cursor;
    tmp_cy = _executor::tabela_procese[_executor::proces_curent].y_cursor;

    window(tmp_x, tmp_y, tmp_x + tmp_x_len, tmp_y + tmp_y_len);
    textbackground(BLACK);
    //clrscr();

    if (tmp_cy == 1) tmp_cy++;
    gotoxy(tmp_cx, tmp_cy);
    cprintf("%d", *i);

    _executor::tabela_procese[_executor::proces_curent].x_cursor = wherex();
    _executor::tabela_procese[_executor::proces_curent].y_cursor = wherey();

    // scrie antetul
    char* temp = new char[tmp_x_len + 2];
    for(int i = 0; i < tmp_x_len + 1; i++) temp[i] = ' ';
    temp[tmp_x_len + 1] = '\0';

    textbackground(tmp_color);
    gotoxy(1,1);
    cprintf("%s\n", temp);
    gotoxy(1,1);
    cprintf("%s\n", _executor::tabela_procese[_executor::proces_curent].nume);

    onlyOne.V();
  }
}

void Iesire::operator<<(char *str)
{
  int tmp_x, tmp_y, tmp_x_len, tmp_y_len, tmp_color, tmp_cx, tmp_cy;

  if (_executor::tabela_procese[_executor::proces_curent].active == ACTIVE)
  {
    onlyOne.P();
    tmp_x = _executor::tabela_procese[_executor::proces_curent].x_pos;
    tmp_y = _executor::tabela_procese[_executor::proces_curent].y_pos;
    tmp_x_len = _executor::tabela_procese[_executor::proces_curent].x_len;
    tmp_y_len = _executor::tabela_procese[_executor::proces_curent].y_len;
    tmp_color = _executor::tabela_procese[_executor::proces_curent].color;
    tmp_cx = _executor::tabela_procese[_executor::proces_curent].x_cursor;
    tmp_cy = _executor::tabela_procese[_executor::proces_curent].y_cursor;

    window(tmp_x, tmp_y, tmp_x + tmp_x_len, tmp_y + tmp_y_len);
    textbackground(BLACK);
    //clrscr();

    if (tmp_cy == 1) tmp_cy++;
    gotoxy(tmp_cx, tmp_cy);
    cprintf("%s", str);

    _executor::tabela_procese[_executor::proces_curent].x_cursor = wherex();
    _executor::tabela_procese[_executor::proces_curent].y_cursor = wherey();

    // scrie antetul
    char* temp = new char[tmp_x_len + 2];
    for(int i = 0; i < tmp_x_len + 1; i++) temp[i] = ' ';
    temp[tmp_x_len + 1] = '\0';

    textbackground(tmp_color);
    gotoxy(1,1);
    cprintf("%s\n", temp);
    gotoxy(1,1);
    cprintf("%s\n", _executor::tabela_procese[_executor::proces_curent].nume);

    onlyOne.V();
  }
}
