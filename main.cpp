#include <ncurses.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <unistd.h>
using namespace std;

vector <pair<int, int>> snake;
void game1();
void open();
void make_snake(){for(int i=0; i<13; i++)snake.push_back(make_pair(20, 20-i));}
void show_snake(WINDOW* w1){
  for(int i=0; i<snake.size(); i++){
    mvwaddch(w1, snake[i].first, snake[i].second, '0');}
  wrefresh(w1);
}//인자로 입력받은 w1윈도우에 snake 모습 출력.
int check_crush_body(){
  for(int i=1; i<snake.size(); i++){
    if(snake[0].first == snake[i].first && snake[0].second == snake[i].second)
      return 1;
  }
  return 0;
}
void draw_snake(WINDOW* wsnake){

  noecho();//입력 값 출력하지 않음.
  curs_set(0);// 커서 위치 초기화
  keypad(wsnake, TRUE);// 키 입력 받기 위한 준비
  nodelay(wsnake, TRUE);//입력을 안 받아도 넘어가게 해 주는 함수.

  int d; // snake의 진행 방향

  make_snake();// 처음 뱀 위치 및 길이 초기화 헤드는 20, 20에 길이는 3이다.

  show_snake(wsnake); // 인자로 들어가는 윈도우에 snake 모습 출력.
  d = KEY_RIGHT;
  int old_d = 3;
  int q = 0;
  while(1){

    d = wgetch(wsnake);
    flushinp();
    usleep(100000);
    mvwaddch(wsnake, snake.back().first, snake.back().second, ' ');
    //꼬리 지우기

    for(int i=snake.size() - 1; i>0; i--){
      snake[i].first = snake[i-1].first;
      snake[i].second = snake[i-1].second;}

    switch(d)
    {
    case KEY_UP:
      if(old_d == 2){q = 1;}
      old_d = 1;
      break;
    case KEY_DOWN :
      if(old_d == 1){q = 1;}
      old_d = 2;
      break;
    case KEY_RIGHT :
      if(old_d == 4){q = 1;}
      old_d = 3;
      break;
    case KEY_LEFT :
      if(old_d == 3){q = 1;}
      old_d = 4;
    }

    switch(old_d){
      case 1:
        snake[0].first -= 1;
        q = check_crush_body();
        break;
      case 2:
        snake[0].first += 1;
        q = check_crush_body();
        break;
      case 3:
        snake[0].second += 1;
        q = check_crush_body();
        break;
      case 4:
        snake[0].second -= 1;
        q = check_crush_body();
    }

    if(q == 1){// 반대 키 입력되었을때 종료.
      break;}
    show_snake(wsnake);
  }
}

void open(){
  int key;

  keypad(stdscr, TRUE);
  curs_set(0);
  noecho();

  initscr();
  nodelay(stdscr, TRUE);

  start_color();
  init_pair(1, COLOR_GREEN, COLOR_WHITE);

  bkgd(COLOR_PAIR(1));
  attron(COLOR_PAIR(1));
  mvprintw(3, 4, "If you want to play a game, plz prees enter key");
  attroff(COLOR_PAIR(1));

  border('|','|','-','-','0','0','0','0');

  refresh();

  key = getch();
  if(key != KEY_ENTER){
    game1();
  }
  getch();
  endwin();
}

void game1(){

  WINDOW *g1 = newwin(40, 100, 5, 5);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  wbkgd(g1, COLOR_PAIR(2));
  wborder(g1, '@','@','@','@','@','@','@','@');
  wrefresh(g1);

  draw_snake(g1);

  getch();
  delwin(g1);

}
int main()
{
  open();
}
