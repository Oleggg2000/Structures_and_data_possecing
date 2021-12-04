#include "List.h"
using namespace std;
int d = 0, num = 0;

List * form(int * mas, int sizeLine)
{
		List* p = (List*)malloc(sizeof(List));
		p->value = mas[0];
		p->next = nullptr;
		List* start = p;
		List* pk;
		for (int i = 1; i < sizeLine; i++)
		{
			pk = p;
			p = (List*)malloc(sizeof(List));
			p->value = mas[i];
			p->next = nullptr;
			pk->next = p;
		}
		return start;
}

void out(List * p)
{
		cout << p->value << " ";
		if (p->next)
			out(p->next);
		else
			cout << endl;
}

void Cycle(List ** start, List * p, int * wgn, int * Stack)
{
		int v = p->value;//Номер вершины
		d++;
		Stack[d] = v;//Заносим в стек вершину
		num++;
		wgn[v] = num;
		while (p->next)
		{
			int u = p->next->value;//Вершина- конец ребра
			if (wgn[u] == 0)
			{
				//Проверяем другую вершину
				List* pk = start[u];
				Cycle(start, pk, wgn, Stack);
			}
			else
			{
				if (u != Stack[d - 1] && wgn[v] > wgn[u])
				{
					//Выводим цикл
					cout << "Cycle" << endl;
					int c = d;
					do
					{
						cout << Stack[c] << " ";
						c--;
					} while (Stack[c] != u);
					cout << Stack[c];
					cout << endl;
				}
			}
			p = p->next;//Сменяем вершину
		}
		d--;//Удаляем из стека вершину
}
