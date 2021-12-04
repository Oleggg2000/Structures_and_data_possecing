#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdio>
#define MAX_Elem 5
using namespace std;

bool IsEmpty(int &count);
bool StackOverflow(int &count);
void Push(string &word, int &count, int &start, string *stack);
string Pop(int &start, int &count, string *stack);
void Top(int &start, int&count, string* stack);
void Reverse(int &start, int&count, string* stack);

int main() {
	string stack[MAX_Elem];
	int count = -1, start=MAX_Elem;

	Reverse(start, count, stack);
	string a= "hello", c="programm";
	Push(a, count, start, stack);
	Push(c, count, start, stack);
	//cout << Pop(start, count, stack) << endl;
	Top(start, count, stack);
	
	system("pause");
	return 0;
}

bool IsEmpty(int &count) {
	if ((count > -1) && (count<=MAX_Elem)) return false;
	else return true;
}

bool StackOverflow(int &count) {
	if (count >= MAX_Elem)
	{
		cout << "Stack overflow!" << endl;
		return true;
	}
	else return false;
}

void Push(string &word, int &count, int &start, string *stack) {
	if (count==-1)count++;
	if (StackOverflow(count)==true) return;
	stack[MAX_Elem-count-1] = word;
	start--;
	if (count > -1) count++;
	return;
}

string Pop(int &start, int &count, string *stack) {
	string word;
	if (IsEmpty(count) == true) return word;
	word=stack[start];
	stack[start] = "\0";
	start++;
	count--;
	return word;
}

void Top(int &start, int&count, string* stack) {
	cout << stack[start] << endl;
	return;
}

void Reverse(int &start, int&count, string* stack)
{
	int size=0, size_const=size;
	char word[50], sbl;
	FILE *file = fopen("T.txt", "r+");
	if (!file) return;
	if (count == -1) count++;
	while (!feof(file))
	{
		sbl = fgetc(file);
		if ((sbl != ' ') && (sbl != '.') && (sbl != ',') && (!feof(file)))
		{
			fseek(file, 1 / 2, SEEK_CUR);
		}
		else if (!feof(file)) {
			fseek(file, -1 / 2, SEEK_CUR);
			size = ftell(file)-size_const;
			size_const += size;
			fseek(file, -size, SEEK_CUR);
			fgets(word, size, file);
			rewind(file);
			fseek(file, size_const, SEEK_CUR);
			stack[MAX_Elem - count - 1] = string(word);
			start--;
			count++;
		}
		else {
			fseek(file, -1 / 2, SEEK_CUR);
			size = ftell(file) - size_const;
			size_const += size;
			fseek(file, -size, SEEK_CUR);
			fgets(word, size+1, file);
			rewind(file);
			fseek(file, size_const, SEEK_CUR);
			stack[MAX_Elem - count - 1] = string(word);
			start--;
			count++;
			break;
		}
	}
	for (int i = start; i < MAX_Elem; i++)
	{
		for (int j = stack[i].length() - 1; j >= 0; j--)
		{
			cout << stack[i].at(j);
		}
		stack[i] = "\0";
		cout << " ";
	}
	cout << "\n";
}