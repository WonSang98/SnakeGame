#include <ncurses.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>




class Board{
public:
    int body_mission;
    int grow_mission;
    int poison_mission;
    int gate_mission;
    WINDOW *score = newwin(15, 40, 5, 80);
    WINDOW *mission = newwin(15, 40, 21, 80);
    Board(int b, int g, int p, int d);
    void ScoreBoard(int body, int body_max, int grow, int poison, int gate);
    bool MissionBoard(int body, int grow, int poison, int gate);
    void gameover();
};
