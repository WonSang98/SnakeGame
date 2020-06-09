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
      Start(1);
  }
  refresh();
  endwin();
}

void Stage::Start(int step){
  int now = step;
  int next = now + 1;
  WINDOW *s1 = newwin(s1_h, s1_w, sy, sx); //stage1 화면 생성.
  Board b(Goal[step][0], Goal[step][1], Goal[step][2], Goal[step][3]);

  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  attron(COLOR_PAIR(2));
  wbkgd(s1, COLOR_PAIR(2));

  keypad(s1, TRUE);
  nodelay(s1, TRUE); // 입력을 안 받아도 넘어가게 해 주는 함수.

  Snake s(10, 10, s1_h, s1_w); //20, 20위치에 뱀 생성.
  WINDOW *msg = newwin(15, 40, 15, 30);
  int k;
  if(s.Game(s1, b, now)){//stage clear
    if(now == 3){//mission all clear
      stage_msg(msg, 2);
      k = wgetch(msg);
      switch(k){
        case '1':
          delwin(msg);
          delwin(s1);
          Start(next);
          break;}
    }
    else{
      stage_msg(msg, 1);
      k = wgetch(msg);
      switch(k){
        case '1':
          delwin(msg);
          delwin(s1);
          Start(next);
          break;}
    }
  }else{//stage fail
    stage_msg(msg, 3);
    k = wgetch(msg);
    switch(k){
      case '1':
        delwin(msg);
        delwin(s1);
        Start(0);
        break;
    }

  }
}

void Stage::stage_msg(WINDOW* clear, int condition){
  init_pair(3, COLOR_BLACK, COLOR_WHITE);
  wmove(clear, 0, 0);
  wattron(clear, COLOR_PAIR(3));
  wborder(clear, '|','|','-','-','*','*','*','*');
  wbkgd(clear, COLOR_PAIR(3));
  if(condition == 1)
    mvwprintw(clear, 2, 3, " MISSION CLEAR!\n NEXT STAGE : 1, any other key is end game");
  else if(condition == 2)
    mvwprintw(clear, 2, 3, " ALL Clear Mission!\n RE-Start game : 1, any other key is end game");
  else if (condition == 3)
    mvwprintw(clear, 2, 3, "MISSION FAIL!\n RETRY : 1, any other key is end game");
  wrefresh(clear);
}
