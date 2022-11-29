#include "Header.h"
#include <iostream>
#include "curses.h"

using namespace std;

void create(MyStruct * mas, int& number, int &b, WINDOW* values)
{
	if (number == 0) {
		mvwprintw(values, 4, 10, "enter the length of the array");
		wrefresh(values);
		mvwscanw(values, 6, 3, "%d", &number);
		wrefresh(values);
	}
	if (number > 0) {
		wclear(values);
		mvwprintw(values, 4, 10, "enter the number");
		wrefresh(values);
		int a = 0;
		wrefresh(values);
		mvwscanw(values, 6, 2, "%d", &a);
		mas->number = a;
		mas->index = b;
		number -= 1;
		b++;
	}
	if (number > 0) {
		MyStruct *next = new MyStruct;
		next->previous = mas;
		mas->next = next;
		create(mas->next, number, b, values);
	}
}

void delet(MyStruct * mas) {

	mas->number = 0;
	mas->next = nullptr;
}

void presize(MyStruct * mas, int number, WINDOW* values) {
	if (mas->index + 1 != number) {
		MyStruct *next = new MyStruct;
		next->previous = mas;
		mas->next = next;
		wclear(values);
		mvwprintw(values, 4, 10, "Enter a new number");
		wrefresh(values);
		int a =0 ;
		wrefresh(values);
		mvwscanw(values, 6, 2, "%d", &a);
		wclear(values);
		next->number = a;
		next->index = next->previous->index + 1;
		presize(next, number, values);
	}
}

void mresize(MyStruct * mas, int number) {
	if (mas->index + 1 != number) {
		mresize(mas->previous, number);
	}
	if (mas->index + 1 == number) {
		mas->next = nullptr;
	}
}

void resize(MyStruct * mas, int number, WINDOW* values, int &size) {
	if (mas->previous == nullptr) {
		mvwprintw(values, 4, 10, "enter the length of the array");
		wrefresh(values);
		mvwscanw(values, 6, 3, "%d", &number);
		wrefresh(values);
		size = number;
	}
	if (mas->next == nullptr) {
		if (mas->index + 1 < number) {
			presize(mas, number, values);
		}
		else {
			mresize(mas, number);
		}

	}
	else {
		resize(mas->next, number, values, size);
	}
}


void read(MyStruct * mas, int index, WINDOW* values) {
	if (mas->index == index - 1) {
		int a = 0;
		wclear(values);
		mvwprintw(values, 4, 10, "Enter a new number");
		wrefresh(values);
		mvwscanw(values, 6, 3, "%d", &a);
		wrefresh(values);
		mas->number = a;
	}
	else {
		read(mas->next, index, values);
	}
}

void  print(MyStruct * mas, WINDOW* values) {
	if (mas->previous == nullptr) {
		wclear(values);
		mvwprintw(values, 4, 10, "%d", mas->number);
		wprintw(values, ",");
		wrefresh(values);
	}
	else if (mas->next != nullptr) {
		wprintw(values, "%d", mas->number);
		wprintw(values, ",");
		wrefresh(values);
		
	}
	else if (mas->next == nullptr) {
		wprintw(values, "%d", mas->number);
		wrefresh(values);
	}

	if (mas->next != nullptr) {
		print(mas->next, values);
	}
}

void sort(MyStruct * mas, int b) {
	if (mas->index + 1 < b) {
		if (mas->number > mas->next->number) {
			int a = mas->number;
			mas->number = mas->next->number;
			mas->next->number = a;
			if (mas->index != 0) {
				sort(mas->previous, b);
			}
		}
		sort(mas->next, b);
	}
}

void MAX(MyStruct * mas, int &max, WINDOW* values) {
	if (mas->number > max) {
		max = mas->number;
	}
	if (mas->next != nullptr) {
		MAX(mas->next, max, values);
	}
	if (mas->next == nullptr) {
		wclear(values);
		mvwprintw(values, 4, 10, "maximum number");
		wrefresh(values);
		mvwprintw(values, 6, 3, "%d", max);
		wrefresh(values);
	}

}
