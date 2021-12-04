#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
using namespace std;
void read(char *s);
void Push(char *s);
char *Pop(char *s);
bool IsEmpty();
char *Top(char *s);
void Reverse(char *s);

int main() {
	char q, s[100] = {'\0'};
	do {
		int i;
		cout << "\n1- Push\n2- Pop\n3- IsEmpty\n4- Top\n5- Reverse\nChoose right case: ";
		cin >> i;
		switch (i)
		{
		case 1: {
			read(s);
			Push(s);
			break;
		}
		case 2: {
			read(s);
			Pop(s);
			break;
		}
		case 3: {
			IsEmpty();
			break;
		}
		case 4: {
			read(s);
			Top(s);
			break;
		}
		case 5: {
			read(s);
			Reverse(s);
			break;
		}
		}
		cout << "Do u want to continue? y/n: ";
		cin >> q;
	} while (q != 'n');
	
	system("pause");
	return 0;
}

void read(char *s) {
	ifstream file("T.txt");
	if (!file)
	{
		cout << "Can't open file";
		return;
	}
	file.getline(s, 100);
	//cout << s << endl;
	file.close();
	return;
}

void Push(char *s)
{
	char word[50] = {'\0'}, *str= new char [sizeof(s)+sizeof(word)];

	cout << "\nPrint word: ";
	cin >> word;
	word[strlen(word)] = ' ';
	word[strlen(word)+1] = '\0';
	strcpy(str, word);
	strcat(str, s);
	ofstream file("T.txt");
	file << str;
	file.close();
	cout << "\nChanged string: " << str << endl;
//	delete[] str;
	return;
}

char *Pop(char *s) {
	char word[50] = {'\0'};
	for (int i = 0; i != strlen(s); i++) 
	{
		if ((s[i] != '.') && (s[i] != ',') && (s[i] != ' '))
		{
			word[i] = s[i];
		}
		else
		{
			int j;
			i++;
			for (j = 0; j <= (strlen(s) - i); j++)
				s[j] = s[j + i];
			remove("T.txt");
			ofstream file("T.txt");
			file << s;
			file.close();
			break;
		}
	}
	cout <<"\nWord: "<< word << endl;
	cout << "\nChanged string: " << s << endl;
	return word;
}

bool IsEmpty() {
	char s[100] = {'\0'};
	ifstream file("T.txt");
	if ((!file.is_open()) || (file.peek() == EOF)) {
		cout << "File is empty" << endl;
		return true;
	}
	else {
		cout << "File isn't empty" << endl;
		false;
	}
	file.close();
}

char *Top(char *s) {
	char word[50] = {'\0'};
	for (int i = 0; i != strlen(s); i++)
	{
		if ((s[i] != '.') && (s[i] != ',') && (s[i] != ' '))
		{
			word[i] = s[i];
		}
		else break;
	}
	cout << "Word: " << word << endl;
	return word;
}

void Reverse(char *s) {
	int j=0;
	char word[50] = { '\0' }, *str = new char[sizeof(s)], *temp = new char[sizeof(s)];
	for (int i = 0; str[i] != '\0'; i++)
	{
		str[i] = { '\0' };
		if (temp[i]!='\0')
		temp[i] = { '\0' };
	}
	
	for (int i = 0; i<=strlen(s); i++)
	{
		if ((s[i] != '.') && (s[i] != ',') && (s[i] != ' ') && (s[i]!='\0'))
		{
			word[j] = s[i];
			j++;
		}
		else
		{
			word[j] = ' ';
			word[j+1] = '\0';
			j = 0;
			strcat(temp, str);
			for (int k = 0; str[k] != '\0'; k++)
				str[k] = '\0';
			strcat(str, word);
			strcat(str, temp);
			for (int k = 0; str[k] != '\0'; k++)
				temp[k] = '\0';
		}
	}
	cout << str << endl;
	return;
}