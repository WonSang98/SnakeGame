#include <ncurses.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

class Board{
public:
    void ScoreBoard(WINDOW* score, int body, int grow, int poison, int gate);
};
