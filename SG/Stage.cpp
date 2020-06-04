#include <iostream>
#include "Stage.h"

Stage::Stage(){ // 생성자.
  sx = 5; sy = 5;
  s1_h = 32; s1_w = 62;
}
void Stage::InitHome(){
  int key;

  initscr(); // 처음 Main 화면 생성.

  keypad(stdscr, TRUE); // 특수키 입력 가능.
  curs_set(0); // cursor 안 보이게.
  noecho(); // 입력 값 출력 안 되게 하기.

  start_color();
  init_pair(1, COLOR_GREEN, COLOR_WHITE); // 배경이 white, 글씨가 green

  bkgd(COLOR_PAIR(1)); // pair 1의 색으로 배경 색칠

  mvprintw(3, 4, "Test Game -> prees enter key");

  border('|','|','-','-','0','0','0','0');
  refresh();

  key = getch();
  switch(key){ // ENTER입력 시 sTAGE1 실행
    case 10:
      Stage_1();
  }
  mvprintw(3, 4, "EndGame , press anykey -> shutdown");
  refresh();
  getch();
  endwin();
}

void Stage::Stage_1(){

  WINDOW *s1 = newwin(s1_h, s1_w, sy, sx); //stage1 화면 생성.
  WINDOW *score = newwin(15, 40, 5, 80);
  WINDOW *mission = newwin(15, 40, 21, 80);
  Mission(mission);

  init_pair(2, COLOR_RED, COLOR_BLACK);
  attron(COLOR_PAIR(2));
  wbkgd(s1, COLOR_PAIR(2));

  keypad(s1, TRUE);
  nodelay(s1, TRUE); // 입력을 안 받아도 넘어가게 해 주는 함수.

  Snake s(10, 10, s1_h, s1_w); //20, 20위치에 뱀 생성.
  s.Game(s1, score, mission, 0);
  getch();
  delwin(s1);
}
void Stage::Mission(WINDOW *mission){
  init_pair(3, COLOR_BLACK, COLOR_WHITE);
  wmove(mission, 0, 0);
  wattron(mission, COLOR_PAIR(3));
  wborder(mission, '|','|','-','-','*','*','*','*');
  wbkgd(mission, COLOR_PAIR(3));
  mvwprintw(mission, 3, 3, " B : " );
  mvwprintw(mission, 4, 3, " + : " );
  mvwprintw(mission, 5, 3, " - : " );
  mvwprintw(mission, 6, 3, " G : ");
  wrefresh(mission);
}
