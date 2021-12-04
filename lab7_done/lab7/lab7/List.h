#pragma once
#include <iostream>

struct List {
	int value;
	List* next;
};

List* form(int* mas, int sizeLine);
void out(List* p);
void Cycle(List** start, List* p, int* wgn, int *Stack);