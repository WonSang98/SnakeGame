#include <iostream>
#include "Board.h"

void Board::ScoreBoard(WINDOW *score, int body, int grow, int poison, int gate){
  init_pair(3, COLOR_BLACK, COLOR_WHITE);
  wmove(score, 0, 0);
	wattron(score, COLOR_PAIR(3));
  wborder(score, '|','|','-','-','*','*','*','*');
	wbkgd(score, COLOR_PAIR(3));
  mvwprintw(score, 3, 3, " B : %d",body );
  mvwprintw(score, 4, 3, " + : %d",grow );
  mvwprintw(score, 5, 3, " - : %d",poison );
  mvwprintw(score, 6, 3, " G : %d ",gate);
	wrefresh(score);
}
