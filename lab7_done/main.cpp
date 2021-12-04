/*ЗАДАНИЕ №15. Напишите программу, которая с помощью алгоритма поиска в глубину находит множество фундаментальных циклов связного неориентированного графа, заданного списками смежности.         
После завершения работы с динамическими структурами данных необходимо освободить занимаемую ими память.*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <iomanip>
using namespace std;


struct list { //Структура списка
	int data;
	struct list *r_ptr;
	struct list *l_ptr;
};

struct list * addelem(list *lst, int number); //Функция добавления элемента в список lst с определенной data = number
int hashf(int num); //Хэш-функция (по карточке)
void hesh_search(struct list *hash_table); //Функция поиска числа в хэш-таблице

int main() {
	setlocale(LC_ALL, "Rus");
	char buf[50];
	int count_tops = 0;

	ifstream input("input.txt");
	if (!input.is_open()) {
		cout << "Ошибка открытия файла";
	}
	else
	{
		while (input.eof() != true)
		{
			input.getline(buf, 100);
			count_tops++;
		}
		input.close();
	}

	list *adjacency_list = new list[count_tops];
	for (int i = 0; i < count_tops; i++) {
		adjacency_list[i].data = 0;
		adjacency_list[i].r_ptr = NULL;
		adjacency_list[i].l_ptr = NULL;
	}

	ifstream fin("input.txt");
	if (!fin.is_open()) {
		cout << "Ошибка открытия файла";
	}
	int i=-1;
	while (fin.eof() != true) {
		fin >> buf;
		if (buf[strlen(buf) - 1] == '-') i++;
		else addelem(&adjacency_list[i], atoi(buf));
	}
		

	cout << "#tops  " << setw(10) << left << "branch_1" //Аккуратный вывод таблицы
		<< setw(10) << "branch_2"
		<< setw(10) << "branch_3"
		<< setw(10) << "branch_4"
		<< endl;
	list *lptr;
	for (int i = 0; i < count_tops; i++)
	{
		lptr = &adjacency_list[i];
		cout << setw(2) << i << "->   ";
		if (lptr->r_ptr == NULL) cout << setw(10) << lptr->data << endl;
		else {
			while (lptr->r_ptr != NULL) {
				cout << setw(10) << lptr->data;
				lptr = lptr->r_ptr;
			}
			cout << setw(10) << lptr->data << endl;
		}
	}

	hesh_search(adjacency_list); //Вызов функции поиска элемента


	return 0;
}


struct list * addelem(list *lst, int number)
{
	if (lst->data == NULL) {
		lst->data = number;
		lst->r_ptr = NULL;
		lst->l_ptr = NULL;
		return lst;
	}
	else {
		struct list *temp, *p = lst;
		temp = (struct list*)malloc(sizeof(list));
		while (p->r_ptr != NULL) {
			p = p->r_ptr;
		}
		p->r_ptr = temp;

		temp->data = number;
		temp->r_ptr = NULL;
		temp->l_ptr = p;
		return temp;
	}
}


int hashf(int num) {
	return (num % 3);
}


void hesh_search(struct list *hash_table) {
	int key, hash, count = 0;
	struct list *lptr = hash_table;
	cout << "Введите число, которое котите найти: ";
	cin >> key;
	hash = hashf(key);
	while (lptr[hash].data != key)
	{
		if (lptr[hash].r_ptr != NULL) lptr[hash] = *lptr[hash].r_ptr;
		else {
			cout << "Введенного числа не существует!\n";
			return;
		}
		count++;
	}
	count++;
	cout << "\nХэш-значение: " << hash << "   Количество проб: " << count << "   Найденное число: " << lptr[hash].data << endl;
	return;
}