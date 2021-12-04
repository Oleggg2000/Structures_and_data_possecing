/*ЗАДАНИЕ №7. Создать файл из 15 целых чисел. Написать программу, которая реализует метод открытого хеширования с хеш-функцией,
основанной на методе деления с остатком. Занести данные, хранящиеся в файле в хеш-таблицу. Вывести построенную хеш-таблицу на экран.
Организовать поиск данных в хеш-таблице. Результаты поиска данных вывести на экран. Также вывести количество проб, которые были
затрачены при поиске.*/
#include <iostream>
#include <fstream>
#include <cstdio>
#include <iomanip>
#define ELEM_NUM 15 //Количество элементов хэш-таблицы (задано индивидуально)
using namespace std;

struct list { //Структура списка
	int data;
	struct list *ptr;
};

struct list * addelem(list *lst, int number); //Функция добавления элемента в список lst с определенной data = number
int hashf(int num); //Хэш-функция (по карточке)
void hesh_search(struct list *hash_table); //Функция поиска числа в хэш-таблице

int main() {
	setlocale(LC_ALL, "Rus");
	list hash_table[ELEM_NUM];
	for (int i = 0; i < ELEM_NUM; i++) {
		hash_table[i].data = 0;
		hash_table[i].ptr = NULL;
	}
		
	int num; //Считываемое число
	int hash; //Хэш значение


	ifstream input("input.txt"); 
	if (!input.is_open()) {
		cout << "Ошибка открытия файла";
	}
	else
	{
		while (input.eof() != true) 
		{
			input >> num;
			hash = hashf(num);
			if (hash_table[hash].data == 0)	{ //Если список пуст, то пишем data
				hash_table[hash].data = num;
			}
			else { //Иначе добавляем элемент в конец списка
				addelem(&hash_table[hash], num);
			}			
		}
		input.close();
	}


	cout << "#hash  " << setw(6) << left << "#_1" //Аккуратный вывод хэш-таблицы
				   << setw(6) << "#_2"
				   << setw(6) << "#_3"
				   << endl;
	list *lptr;
	for (int i = 0; i < ELEM_NUM; i++) 
	{
		lptr = &hash_table[i];
		cout << setw(2) << i << "->   ";
		if (lptr->ptr == NULL) cout << setw(6) << lptr->data << endl;
		else {
			while (lptr->ptr != NULL) {
				cout << setw(6) << lptr->data;
				lptr = lptr->ptr;
			}
			cout << setw(6) << lptr->data << endl;
		}
	}

	hesh_search(hash_table); //Вызов функции поиска элемента


	return 0;
}


struct list * addelem(list *lst, int number)
{
	struct list *temp, *p = lst;
	temp = (struct list*)malloc(sizeof(list));
	while (p->ptr != NULL) {
		p = p->ptr;
	}
	p->ptr = temp;

	temp->data = number;
	temp->ptr = NULL;
	return(temp);
}


int hashf(int num) {
	return (num % ELEM_NUM);
}


void hesh_search(struct list *hash_table) {
	int key, hash, count=0;
	struct list *lptr= hash_table;
	cout << "Введите число, которое котите найти: ";
	cin >> key;
	hash = hashf(key);
	while (lptr[hash].data != key)
	{
		if (lptr[hash].ptr != NULL) lptr[hash] = *lptr[hash].ptr;
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