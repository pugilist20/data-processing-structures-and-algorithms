#include <iostream>

using namespace std;

int check() {
	int num;
	while (!(cin >> num) || (cin.peek() != '\n')) {
		cin.clear();
		while (cin.get() != '\n');
		cout << "Ошибка ввода, повторите попытку" << endl;
	}
	return num;
}

int first;
int last;
int qSize;
int values[4];

void initQueue() {
	first = 0;
	last = 0;
	qSize = 0;
}

bool isEmpty() {
	if (qSize == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool isFulness() {
	if (qSize == 4) {
		return true;
	}
	else {
		return false;
	}
}

void add(int value) {
	if (!isFulness()) {
		values[last] = value;
		last++;
		qSize++;
		if (last == 5)
		{
			last = 0;
		}
	}
	else {
		cout << "Очередь переполнена " << endl;
	}
}

void remove() {
	if (!isEmpty()) {
		values[first] = 0;
		qSize--;
		last--;
		for (int i = 0; i < qSize; i++) {
			values[i] = values[i + 1];
		}
		values[qSize] = 0;
		if (first == 4)
		{
			first = 0;
		}
	}
	else
	{
		cout << "Очередь пуста\n";
	}
}

void destroy()
{
	memset(values, 0, sizeof(values));
	first = 0;
	last = 0;
}

void printQueue() {
	if (!isEmpty()) {
		cout << "Текущее состояние очереди: ";
		for (int i = 0; i < last; i++) {
			cout << values[i]<<" ";
		}
		cout << endl;

	}
	else {
		cout << "Очередь пуста" << endl;
	}
}

void menu() {
	initQueue();
	bool stop = true;
	while (stop)
	{
		cout << "1. Добавить элемент в очередь" << endl
			<< "2. Удалить элемент из очереди" << endl
			<< "3. Вывести состояние очереди" << endl
			<< "4. Завершить работу программы" << endl
			<< "Ваш выбор: ";
		int command = check();
		switch (command) {
		case 1:
		{
			cout << "Введите число: ";
			add(check());
			break;
		}
		case 2:
		{
			remove();
			break;
		}
		case 3:
		{
			printQueue();
			break;
		}
		case 4:
		{
			stop = !stop;
			destroy();
			cout << "Работа программы завершена" << endl;
			break;
		}
		default: 
		{
			cout << "Ошибка ввода, повторите попытку" << endl;
		}
		}
	}
}

int main() {
	setlocale(LC_ALL, "RU");
	menu();
}