#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

const int arr_size = 5;
int num;

void find();
int find(string _value, int act);

int check() {
	int a;
	while (!(cin >> a) || (cin.peek() != '\n'))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << endl << "Ошибка ввода. Повторите попытку " << endl << endl;
	}
	return a;
}

struct LinkedList {
	string value;
	int next;
} list[arr_size];

inline void init() {
	list[0].value = "HEAD";
	list[0].next = 0;
	for (int i = 1; i < arr_size; i++) list[i].next = -1;
	num = 0;
}

bool isEmpty() {
	if (list[0].next == 0) return 1;
	else return 0;
}

bool isFull() {
	if (num == arr_size - 1) return 1;
	else return 0;
}

void print() {
	cout << endl << "Состояние списка: ";
	if (!isEmpty()) {
		cout << "Заполнено " << num << " из " << (arr_size - 1) << " ячеек списка:" << endl;
		int i = 1, current = list[0].next;
		while (current != 0) {
			cout << i << ") " << list[current].value << " (ячейка памяти: " << current << ")" << endl;
			current = list[current].next;
			i++;
		}
	}
	else {
		cout << "Список пустой" << endl;
	}
}

void add() {
	if (!isFull()) {
		string new_value;
		if (!isEmpty()) {
			int choice = -1, i = -1, j = 0, s = -1;
			while ((choice != 0) && (choice != 1)) {
				cout << endl << "Куда добавить элемент?\n 0 - Перед заданным элементом\n 1 - После заданного элемента\n\n Введите номер команды: ";
				choice = check();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				if (choice == 0) {
					i = -1; s = -1;
					while ((i == -1) || (s == -1)) {
						cout << endl << "Введите значение элемента, перед которым вы хотите добавить новый элемент: ";
						cin.clear();
						getline(cin, new_value);
						i = find(new_value, 1);
						s = find(new_value, 0);
						if ((i == -1) && (s == -1)) cout << endl << " Строка " << new_value << " не найдена. Повторите ввод" << endl;
					}
					j = list[0].next;
					for (j = 1; j < arr_size; j++) if (list[j].next == -1) break;
					list[j].next = i;
					list[s].next = j;
				}
				else if (choice == 1) {
					i = -1;
					while (i == -1) {
						cout << endl << "Введите значение элемента, после которого вы хотите добавить новый элемент: "; cin.clear(); getline(cin, new_value);
						i = find(new_value, 1);
						if (i == -1) cout << endl << " Строка " << new_value << " не найдена. Повторите ввод" << endl;
					}
					for (j = 1; j < arr_size; j++) if (list[j].next == -1) break;
					list[j].next = list[i].next;
					list[i].next = j;
				}
				else {
					choice = -1;
					cout << endl << "Ошибка ввода. Повторите попытку" << endl;
				}
			}
			cout << endl << "Введите добавляемую строку: "; cin.clear(); getline(cin, new_value);
			list[j].value = new_value;
			cout << endl << "Элемент успешно добавлен! " << endl;
		}
		else {
			cout << endl << "Введите добавляемую строку: ";
			cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); getline(cin, new_value);
			list[1].value = new_value;
			list[1].next = 0;
			list[0].next = 1;
			cout << endl << "Элемент успешно добавлен! " << endl;
		}
		num++;
	}
	else {
		cout << endl << "Добавление невозможно. Список переполнен" << endl;
	}
}

void remove() {
	if (!isEmpty()) {
		print();
		string _value;
		int i = -1, s = -1;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		while ((i == -1) || (s == -1)) {
			cout << endl << "Введите значение элемента, который хотите удалить: "; cin.clear(); getline(cin, _value);
			i = find(_value, 1);
			s = find(_value, 0);
			if ((i == -1) || (s == -1)) cout << endl << " Строка " << _value << " не найдена. Повторите ввод" << endl;
		}
		list[s].next = list[i].next;
		list[i].next = -1;
		num--;
		cout << endl << "Элемент '" << list[i].value << "' удален из списка. Теперь в списке " << num << " элементов" << endl;
	}
	else {
		cout << endl << "Удалять нечего. Список пуст" << endl;
	}
}

void find() {
	if (!isEmpty()) {
		print();
		string _value;
		cout << endl << " Введите строку, которую хотите найти: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, _value);
		int i = 1, current = list[0].next;
		while ((current != 0) && (list[current].value != _value)) {
			current = list[current].next;
			i++;
		}
		if (current != 0) cout << " Строка " << _value << " найдена под номером " << i << " (в ячейке памяти № " << (current++) << ")" << endl;
		else cout << " Строка " << _value << " не найдена" << endl;
	}
	else {
		cout << endl << "Искать нечего, список пуст" << endl;
	}
}

int find(string new_value, int mode) {
	int current = list[0].next;
	if (mode == 1)
		while ((current != 0) && (list[current].value != new_value)) {
			current = list[current].next;
		}
	else if (mode == 0)
	{
		int pred = 0;
		while (current != 0) {
			if (list[current].value == new_value) break;
			current = list[current].next;
			pred = list[pred].next;
		}
		return pred;
	}
	if (current != 0) return current;
	else return -1;
}

inline void clear() {
	init();
	cout << endl << "Список очищен" << endl;
}

void menu() {
	init();
	int number;
	string value;
	bool stop = true;
	while (stop) {
		cout << "___________________________________________________________" << endl;
		cout << endl << "Выберите команду из списка:" << endl;
		cout << "1. Вывод текущего состояния списка на экран" << endl;
		cout << "2. Проверка пустоты списка" << endl;
		cout << "3. Проверка полноты списка" << endl;
		cout << "4. Добавить элемент в список" << endl;
		cout << "5. Удалить элемент из списка" << endl;
		cout << "6. Поиск элемента с заданной информационной частью" << endl;
		cout << "7. Очистить список" << endl;
		cout << "8. Завершить работу программы" << endl;
		cout << "Номер команды: ";
		number = check();
		switch (number) {
		case 1: {
			print();
			break;
		}
		case 2: {
			if (isEmpty()) {
				cout << endl << "Список пустой " << endl;
			}
			else {
				cout << endl << "Список не пустой" << endl;
			}
			break;
		}
		case 3: {
			if (isFull() == 1) {
				cout << endl << "Список заполнен" << endl;
			}
			else {
				cout << endl << "Список не заполнен" << endl;
			}
			break;
		}
		case 4: {
			add();
			break;
		}
		case 5: {
			remove();
			break;
		}
		case 6: {
			find();
			break;
		}
		case 7: {
			clear();
			break;
		}
		case 8: {
			clear();
			cout << endl << "Программа завершила работу" << endl;
			stop = !stop;
			break;
		}
		default: {
			cout << endl << "Ошибка ввода. Повторите попытку" << endl;
		}
		}
	}
}

int main() {
	system("chcp 1251");
	menu();
	return 0;
}
