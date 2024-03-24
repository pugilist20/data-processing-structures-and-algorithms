#include <iostream>
#include <string>

using namespace std;

const int arr_size = 4;
int value_count;
string list[arr_size];

int check() {
	int num;
	while (!(cin >> num) || (cin.peek() != '\n')) {
		cin.clear();
		while (cin.get() != '\n');
		cout << "Ошибка ввода, повторите попытку" << endl;
	}
	return num;
}

bool isEmpty() { return value_count == 0; }

bool isFullness() { return value_count == arr_size; }

void init() {
	for (int i = 0; i < arr_size; i++) { 
		list[i] = "";
	}
	value_count = 0;
}

void print() {
	if (!isEmpty()) {
		cout << "Заполнено " << value_count << " из " << arr_size << " ячеек списка:" << endl;
		for (int i = 0; i < value_count; i++) {
			cout << i + 1 << ") " << list[i] << endl;
		}
	}
	else {
		cout << "Список пуст"<<endl;
	}
}

void add(string new_value) {
	if (!isFullness()) {
		if (isEmpty()) {
			cout << "Элемент будет добавлен в начало" << endl;
			list[0] = new_value;
			value_count++;
			return;
		}
		for (int i = 0; i < value_count; i++) {
			if (new_value < list[i]) {
				for (int k = value_count; k > i; k--) { 
					list[k] = list[k - 1];
				}
				list[i] = new_value;
				cout << " Элемент добавлен под номером " << i + 1 << endl;
				value_count++;
				return;
			}
		}
		list[value_count] = new_value;
		cout << "Добавлено в конец списка" << endl;
		value_count++;
	}
	else {
		cout << "Список переполнен" << endl;
	}
}

void remove(string new_value) {
	if (!isEmpty()) {
		for (int i = 0; i < value_count; i++) {
			if (list[i] == new_value) {
				for (int k = i; k < value_count; k++) {
					list[k] = list[k + 1];
				}
				value_count--;
				cout << endl << "Элемент '" << new_value << "' удален из списка. Теперь в списке " << value_count << " элементов" << endl;
				return;
			}
		}
		cout << "В списке нет элемента с таким номером" << endl;
		return;
	}
	else {
		cout << endl << "Удалять нечего. Список пуст." << endl;
	}
}

void find(string new_value) {
	if (!isEmpty()) {
		int count = 0;
		for (int i = 0; i < value_count; i++) {
			if (list[i] == new_value) {
				cout << "Строка " << new_value << " найдена под номером " << i + 1 << endl;
				return;
			}
		}
		cout << "Строка " << new_value << " не найдена" << endl;
	}
	else {
		cout << "Искать нечего. Список пуст." << endl;
	}
}

inline void destroy() {
	for (int i = 0; i < arr_size; i++) list[i] = "";
	value_count = 0;
}

static void menu()
{
	init();
	bool stop = true;
	string str;
	while (stop)
	{
		cout << "1. Добавить элемент в список" << endl
			<< "2. Удалить элемент из списка" << endl
			<< "3. Вывести состояние списка" << endl
			<< "4. Найти элемент в списке" << endl
			<< "5. Завершить работу программы" << endl
			<< "Ваш выбор: ";
		int command = check();
		switch (command) {
		case 1:
		{
			cout << "Введите строку/число: ";
			cin >> str;
			add(str);
			break;
		}
		case 2:
		{
			if (isEmpty())
			{
				cout << "Удалять нечего. Список пуст." << endl;
				break;
			}
			print();
			cout << "Введите строку/число: ";
			cin >> str;
			remove(str);
			break;
		}
		case 3:
		{
			print();
			break;
		}
		case 4:
		{
			if (isEmpty())
			{
				cout << "Искать нечего. Список пуст." << endl;
				break;
			}
			print();
			cout << "Введите строку/число: ";
			cin >> str;
			find(str);
			break;
		}
		case 5:
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