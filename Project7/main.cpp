#include "curses.h"
#include <iostream>
#include <string>
#include "Header.h"

using namespace std;

int main() {
	MyStruct *mas = new MyStruct;
	int size = 0;
	int b = 0;
	initscr();
	cbreak();
	int xMax;
	xMax = getmaxx(stdscr);
	WINDOW * menu = newwin(7, 48, 2, 16);
	WINDOW * menuwin = newwin(9, 13, 1, 1);
	WINDOW * values = newwin(9, 50, 1, 15);

	box(menuwin, 0, 0);
	box(values, 0, 0);
	refresh();
	wrefresh(menuwin);
	wrefresh(values);

	keypad(menuwin, true);

	string choices[7] = { "1. create", "2. print", "3. resize", "4. read", "5. delete", "6. sort", "7. MAX" };
	int choice;
	int highlight = 0;

	while (1) {
		while (1) {
			for (int i = 0; i < 7; i++) {
				if (i == highlight) {
					wattron(menuwin, A_REVERSE);
				}
				mvwprintw(menuwin, i + 1, 1, choices[i].c_str());
				wattroff(menuwin, A_REVERSE);
			}
			choice = wgetch(menuwin);
			switch (choice) {
			case KEY_UP:
				highlight--;
				if (highlight == -1) {
					highlight = 6;
				}
				break;
			case KEY_DOWN:
				highlight++;
				if (highlight == 7) {
					highlight = 0;
				}
				break;
			default:
				break;
			}
			if (choice == 10) {
				break;
			}
		}
		if(highlight==0){
			int b = 0;
			int numbers = 0; 
			create(mas, numbers, b, menu);
			size = b;
			wclear(menu);
			wrefresh(menu);
		}
		if (highlight == 1) {
			print(mas, menu);
		}
		if (highlight == 2) {
			resize(mas, b, menu, size);
			wclear(menu);
			wrefresh(menu);
		}
		if (highlight == 3) {
			wclear(menu);
			wrefresh(menu);
			int index=0;
			mvwprintw(menu, 4, 10, "enter index");
			wrefresh(menu);
			mvwscanw(menu, 6, 3, "%d", &index);
			wclear(menu);
			wrefresh(menu);
			read(mas, index, menu);
			wclear(menu);
			wrefresh(menu);
		}
		if (highlight == 4) {
			wclear(menu);
			wrefresh(menu);
			mvwprintw(menu, 4, 10, "Delete list");
			wrefresh(menu);
			delet(mas);
		}
		if (highlight == 5) {
			wclear(menu);
			wrefresh(menu);
			mvwprintw(menu, 4, 10, "array sorted");
			wrefresh(menu);
			sort(mas, size);
		}
		if (highlight == 6) {
			int max = -10000;
			MAX(mas, max, menu);
		}
	}
	
	getch();
	

	endwin();
}