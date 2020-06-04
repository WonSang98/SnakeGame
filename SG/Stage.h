#include <iostream>
#include "Snake.h"

class Stage{ //main 화면 부터 stage까지 생성.
public:
  int sx, sy; //stage window 생성 위치
  int s1_h, s1_w; //stage1의 가로 세로 길이
  //Window Function
  Stage();
  void InitHome();// 처음 시작화면(윈도우 생성)
  void Stage_1(); // First Stage
  void Mission(WINDOW* mission);
};
