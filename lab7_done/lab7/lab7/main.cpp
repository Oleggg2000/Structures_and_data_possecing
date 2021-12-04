/*ЗАДАНИЕ №15. Напишите программу, которая с помощью алгоритма поиска в глубину находит множество фундаментальных циклов связного неориентированного графа, заданного списками смежности.         
После завершения работы с динамическими структурами данных необходимо освободить занимаемую ими память.*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "List.h"
using namespace std;

int main()
{
	system("chcp 1251");
	ifstream file;
	file.open("input.txt");
	int* Size_of_vertex= nullptr, **arr=nullptr;
	int Size_of_graph, R_max = 10;
	

	if (file.is_open())
	{
		file >> Size_of_graph;
		arr = (int**)malloc(sizeof(int*)*Size_of_graph);
		Size_of_vertex = (int*)malloc(sizeof(int)*Size_of_graph);
		char *str= new char[R_max];
		file.getline(str, R_max * 2);
		for (int i = 0, strSize = R_max * 2; i < Size_of_graph; i++)
		{
		Size_of_vertex[i] = 1;
		file.getline(str, strSize);
		string str2 = str;
		Size_of_vertex[i] += (str2.size() / 2);
		arr[i] = (int*)malloc(sizeof(int)*Size_of_vertex[i]);
		for (int j = 0, k = 0; k < Size_of_vertex[i]; k++, j += 2)
		{
			arr[i][k] = atoi(&(str2[j]));

		}
		}
		cout << endl;

	}
	else
		cout << "Нельзя открыть файл!" << endl;
	List** start = new List*[Size_of_graph];//Фоимирование графа в структурy
	for (int i = 0; i < Size_of_graph; i++)
	{
		start[i] = form(arr[i], Size_of_vertex[i]);
	}
	free(Size_of_vertex);
	cout << "Graph" << endl;//Cout граф
	for (int i = 0; i < Size_of_graph; i++)
	{
		List* p = start[i];
		out(p);
	}
	free(arr);
	int i = Size_of_graph;//Init
	int *WGN= new int[Size_of_graph - 1];
	fill(WGN, WGN + Size_of_graph, 0);
	int *Stack= new int[Size_of_graph];
	Stack[0] = 0;
	for (int i = 0; i < Size_of_graph; i++)
	{
		List* p = start[i];
		if (WGN[i] == 0)
			Cycle(start, p, WGN, Stack);
	}
	system("pause");
	return 0;
}
