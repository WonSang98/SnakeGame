#include <ncurses.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <unistd.h>
using namespace std;

char map[40][101] = {
		{"2111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111112"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"2111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111112"}
};

void draw_map();

void draw_map(){
	init_pair(2, COLOR_GREEN, COLOR_WHITE);
	// String has '\0' at edge
	WINDOW *game = newwin(40, 101, 5, 5);
	attron(COLOR_PAIR(2));
	wbkgd(game, COLOR_PAIR(2));
	wmove(game, 0, 0);
	for(int i = 0; i < 40; i++){
		for(int j = 0; j < 100; j++){
			if(map[i][j] == '0'){
				waddch(game, ' ');
			}
			if(map[i][j] == '1'){
				waddch(game, 'o');
			}
			if(map[i][j] == '2'){
				waddch(game, '#');
			}
		}
		wprintw(game, "\n");
	}
	attroff(COLOR_PAIR(2));
	wrefresh(game);
	getch();
	delwin(game);
	endwin();
	}
int main(){
  initscr();
  start_color();
  refresh();
  draw_map();

}
