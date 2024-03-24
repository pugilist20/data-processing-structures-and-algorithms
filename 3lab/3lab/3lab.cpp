#include <iostream>
#include <windows.h>
using namespace std;

int getRandomNumber(int min, int max) {
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

int checking() {
	int num;
	while (!(cin >> num) || (cin.peek() != '\n')) {
		cin.clear();
		while (cin.get() != '\n');
		cout << "Ошибка ввода, повторите попытку" << endl;
	}
	return num;
}

struct Queue {
	char value;
	Queue* next;
} *first, *last;

void initQueue() {
	first = NULL;
	last = NULL;
}

bool isEmpty() {
	return first == NULL;
}

void add(char new_value) {
	Queue* temp = new Queue;
	temp->value = new_value;
	temp->next = NULL;
	if (isEmpty()) {
		first = temp;
		last = temp;
		return;
	}
	last->next = temp;
	last = temp;
}

bool remove() {
	if (!isEmpty()) {
		Queue* temp = first;
		first = first->next;
		delete(temp);
		return true;
	}
	else {
		return false;
	}
}

void printQueue() {
	cout << "Состояние очереди: ";
	if (isEmpty()) {
		cout << "Очередь пуста\n";
		return;
	}
	Queue* current = first;
	while (current != nullptr) {
		cout << current->value << " ";
		current = current->next;
	}
	cout << endl;
}

void destroy() {
	Queue* current = first;
	while (current != nullptr) {
		current = first->next;
		delete(first);
		first = current;
	}
	first = nullptr;
	last = nullptr;
}

int main() {
	setlocale(0, "");
	initQueue();
	cout << "Очередь инициализирована\n";

	int check, sec = 0;
	srand(time(0));

	while (true) {
		Sleep(1000);
		check = getRandomNumber(0, 100);
		if (check % 2 == 0) {
			check = getRandomNumber(1, 3);
			cout << "Будет добавлено " << check
				<< " элементов\n";
			for (size_t i = 0; i < check; i++) {
				add(getRandomNumber(65, 90));
			}
		}
		else {
			check = getRandomNumber(1, 3);
			cout << "Будет удалено " << check << " элементов\n";
			for (size_t i = 0; i < check; i++) {
				if (i == 0) {
					if (isEmpty()) {
						cout << "Удаление невозможно, очередь пуста\n";
						break;
					}
				}
				remove();
			}
		}
		printQueue();
		sec++;
		cout << endl;

		if (sec == 10) {
			while (true) {
				cout << "0. Завершить\n";
				cout << "1. Продолжить\n";
				int num = checking();
				if (num == 0) {
					destroy();
					return 0;
				}
				else if (num == 1) {
					sec = 0;
					break;
				}
				else {
					cout << "Выберите из предложенных вариантов\n";
				}
			}
		}
	}
	return 0;
}
