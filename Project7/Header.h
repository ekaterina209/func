#pragma once
#include "curses.h"

struct MyStruct
{
	int number;
	int index;
	MyStruct *next = nullptr;
	MyStruct *previous = nullptr;
};

void create(MyStruct* mas, int& number, int& b, WINDOW* values);

void delet(MyStruct * mas);

void resize(MyStruct * mas, int number, WINDOW* values, int& size);

void read(MyStruct * mas, int index, WINDOW* values);

void  print(MyStruct * mas, WINDOW* values);

void sort(MyStruct * mas, int b);

void MAX(MyStruct * mas, int &max, WINDOW* values);