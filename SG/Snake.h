//Snake.h
#include <iostream>
#include "Board.h"
using namespace std;

class Snake{
public:

  int set_x, set_y; // Snake 생성 좌표 지정.
  int min_len = 3;
  int max_len = 12; // Snake 최소 최대 길이 지정.
  vector <pair<int, int>> body; //Snake의 몸 좌표 저장. 0(head) ~ -1(tail)
  int item_pos[3][4] = {0}; //item이 생성 될 좌표를 저장할 배열.(poison or grow)
  int item_n = 0; //grow 의 개수
  int itemType = 0;
  char item_shape[2] = {'5', '6'};
  int h, w;
  int gate[2][3];

  char map[4][32][63] = {
    {
    "99999999999999999999999999999999999999999999999999999999999999",
    "92111111111111111111111111111111111111111111111111111111111129",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "92111111111111111111111111111111111111111111111111111111111129",
    "99999999999999999999999999999999999999999999999999999999999999"
    },
    {"99999999999999999999999999999999999999999999999999999999999999",
    "92111111111111111111111111111111111111111111111111111111111129",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000010000000000000000000000000000019",
    "91000000000000000000000000000010000000000000000000000000000019",
    "91000000000000000000000000000010000000000000000000000000000019",
    "91000000000000000000000000000010000000000000000000000000000019",
    "91000000000000000000000000000010000000000000000000000000000019",
    "91000000000000000000000000000010000000000000000000000000000019",
    "91000000000000000000111111111121111111111000000000000000000019",
    "91000000000000000000000000000010000000000000000000000000000019",
    "91000000000000000000000000000010000000000000000000000000000019",
    "91000000000000000000000000000010000000000000000000000000000019",
    "91000000000000000000000000000010000000000000000000000000000019",
    "91000000000000000000000000000010000000000000000000000000000019",
    "91000000000000000000000000000010000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "92111111111111111111111111111111111111111111111111111111111129",
    "99999999999999999999999999999999999999999999999999999999999999"},

    {"99999999999999999999999999999999999999999999999999999999999999",
    "92111111111111111111111111111111111111111111111111111111111129",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000211111111111110000000000000000000000001111111111111200019",
    "91000100000000000000000000000000000000000000000000000000100019",
    "91000100000000000000000000000000000000000000000000000000100019",
    "91000100000000000000000000011111100000000000000000000000100019",
    "91000100000000000000000000000000000000000000000000000000100019",
    "91000100000000000000000000000000000000000000000000000000100019",
    "91000100000000000000000000000000000000000000000000000000100019",
    "91000100000000000000000000000000000000000000000000000000100019",
    "91000000000000000000000000000010000000000000000000000000100019",
    "91000000000000000000000000000010000000000000000000000000000019",
    "91000000001000000000000000000010000000000000000000100000000019",
    "91000000001000000000000000011121110000000000000000100000000019",
    "91000000001000000000000000000010000000000000000000100000000019",
    "91000000000000000000000000000010000000000000000000000000000019",
    "91000000000000000000000000000010000000000000000000000000000019",
    "91000100000000000000000000000000000000000000000000000000100019",
    "91000100000000000000000000000000000000000000000000000000100019",
    "91000100000000000000000000000000000000000000000000000000100019",
    "91000100000000000000000000000000000000000000000000000000100019",
    "91000100000000000000000000011111100000000000000000000000100019",
    "91000100000000000000000000000000000000000000000000000000100019",
    "91000100000000000000000000000000000000000000000000000000100019",
    "91000100000000000000000000000000000000000000000000000000100019",
    "91000211111111111110000000000000000000000001111111111111200019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "92111111111111111111111111111111111111111111111111111111111129",
    "99999999999999999999999999999999999999999999999999999999999999"},

    {"99999999999999999999999999999999999999999999999999999999999999",
    "92111111111111111111111111111111111111111111111111111111111129",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000011111111110000000000000000000000001111111111000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000111111111100000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000011111111110000000000000000000000001111111111000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000111111111100000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000011111111110000000000000000000000001111111111000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000111111111100000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000011111111110000000000000000000000001111111111000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000111111111100000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000011111111110000000000000000000000001111111111000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "91000000000000000000000000000000000000000000000000000000000019",
    "92111111111111111111111111111111111111111111111111111111111129",
    "99999999999999999999999999999999999999999999999999999999999999"}
  };
  // 추후 추가 할 변수 목록
  // poison item의 좌표와 개수;
  // Score 변수
  // wall에 생성될 portal 관련 변수
  // 기타 등등

  //Snake Function
  Snake(int y, int x); //생성자.
  Snake(int y, int x, int h, int w); //생성자. // 뱀 화면에 출력.

  //Item Function 인자에 따라 Grow인지 Poison인지 구분.
  void SpawnItem(int stage_num); // item 생성.
  void DelItem(int stage_num); //  item 시간이 지났는지 체크 후 삭제.
  bool GetItem(int f, int s); // item 먹음.
  bool diffItem(int f, int s, int *gcnt, int *pcnt, int stage_num);

  //Check Function
  bool CrushBody(int stage_num); // Snake의 head가 Body에 닿았는지 체크.
  bool UnableItem(int stage_num, int p1, int p2); // 아이템이 생성 가능한 지 확인.

  //Gate Function
  int DefineGate(int stage_num, int d, int gatey, int gatex);//게이트위치 정해주기, 좌우 게이트인지 상하 게이트인지 가장자리게이트인지.
  void SpawnGate(int stage_num, int h, int w);
  void DelGate(int stage_num, int h, int w);
  int GetGate(int stage_num, int f, int s); // gate탔는지 안탔는지 체크
  int MoveGate(int stage_num, int d, int gate_idx);// 게이트에 따른 움직임.
  void UpdateSnake();// 꼬리부터 머리까지 움직이는 방향으로 좌표 최신

  void ShowWin(WINDOW* w1, int stage_num);
  void ShowSnake(int stage_num);
  bool Game(WINDOW* w1, Board b, int stage_num);// 게임 시작!
};
