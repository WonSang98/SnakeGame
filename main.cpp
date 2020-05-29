#include <ncurses.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
using namespace std;

class Snake{
private:
  vector <pair<int, int>> body; //Snake의 몸 좌표 저장. 0(head) ~ -1(tail)
  int grow_pos[3][3] = {0}; //grow item이 생성 될 좌표를 저장할 배열.(poison or grow)
  int grow_n; //grow 의 개수

  // 추후 추가 할 변수 목록
  // poison item의 좌표와 개수;
  // Score 변수
  // wall에 생성될 portal 관련 변수
  // 기타 등등

  //Window Function
  void InitHome();// 처음 시작화면(윈도우 생성)
  void Stage_1(); // First Stage

  //Snake Function
  void MakeSnake(); // 처음 뱀 상태 초기화 (길이 3 생성 좌표는 인자로 줘서 맵 마다 다르게 할 예정, 추후 업데이트))
  void ShowSnake(); // 뱀 화면에 출력.

  //Item Function 인자에 따라 Grow인지 Poison인지 구분.
  void SpawnItem(); // item 생성.
  void DelItem(); //  item 시간이 지났는지 체크 후 삭제.
  void GetItem(); // item 먹음.

  //Check Function
  void CrushBody(); // Snake의 head가 Body에 닿았는지 체크.
  void UnableItem(); // 아이템이 생성 가능한 지 확인.
};

void InitHome(){
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
  switch(key){
    case 10:
      Stage_1();
  }
  if(key == 10){ // 10 is ENTER_KEY

  }

}
vector <pair<int, int>> snake;
int item_pos[3][3] = {0}; //item이 생성될 좌표를 저장할 배열, 0으로 초기화. 최대 3개의 아이템 생성
int n;// number of item;


void game1();
void open();
bool get_item();

void make_snake(){for(int i=0; i<5; i++)snake.push_back(make_pair(20, 20-i));}

//인자로 입력받은 w1윈도우에 snake 모습 출력.
void show_snake(WINDOW* w1){
  for(int i=0; i<snake.size(); i++){
    mvwaddch(w1, snake[i].first, snake[i].second, '0');}
  wrefresh(w1);
}
void get_item(int d){
  int l = snake.size();
  for(int i=0; i<=n; i++){
    if(snake[0].first == item_pos[i][0] && snake[0].second == item_pos[i][1]){
      snake.push_back(make_pair(snake[l-1].first, snake[l-1].second));
      switch(d){
        case 1:
          snake[l].first -= 1;
          break;
        case 2:
          snake[l].first += 1;
          break;
        case 3:
          snake[l].second += 1;
          break;
        case 4:
          snake[l].second -= 1;
      }
    }
  }
}
int check_crush_body(){
  for(int i=1; i<snake.size(); i++){
    if(snake[0].first == snake[i].first && snake[0].second == snake[i].second)
      return 1; }
  return 0;
}

bool check_pos_item(int p1, int p2){
  for(int i=0; i<snake.size(); i++){
    if(snake[i].first == p1 && snake[i].second == p2) return false;
  }
  return true;
}
void grow_item(WINDOW* w1){

  //임시로 시작점이 (5,5) 이고 가로 40p 세로 100p의 크기의 window에 random item생성하는 함수
  //추후 map 생성시 반영하여 수정

  int start_pos[2] = {5, 5};
  int h = 100, w = 40;
  srand((unsigned int)time(0)); // 시드값으로 현재의 시간 초 입력.
  n = rand()%3;
  mvwaddch(w1,0, 0, 48+n);
  for(int i = 0; i <= n; i++){
    do{
    item_pos[i][0] = (rand()%(w - 1)) + 1;
    item_pos[i][1] = (rand()%(h - 1)) + 1;
  }while(!(check_pos_item(item_pos[i][0], item_pos[i][1]))) ;// 만일 임의의 좌표에 아이템 생성 불가시.
    item_pos[i][2] = time(0);
  }

  for(int i=0; i<=n; i++){
    mvwaddch(w1, item_pos[i][0], item_pos[i][1], 'g');
  }
  wrefresh(w1);
}

bool del_item(WINDOW* w1){
  if(time(0) - item_pos[0][2] > 4){
    for(int i=0; i<=n; i++){
      mvwaddch(w1, item_pos[i][0], item_pos[i][1], ' ');
    }
    wrefresh(w1);
    return true;
  }
  else{
    return false;
  }
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
  grow_item(wsnake);
  while(1){
    if(del_item(wsnake)){
      grow_item(wsnake);}
    d = wgetch(wsnake);
    flushinp();
    usleep(50000);


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
        break;
      case 2:
        snake[0].first += 1;
        break;
      case 3:
        snake[0].second += 1;
        break;
      case 4:
        snake[0].second -= 1;
    }
    q = check_crush_body();
    get_item(old_d);

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
