#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

int num1, num2;


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

struct DynamicList {
	string value;
	DynamicList* next;
} *head, * top;

inline void initList() {
	head = new DynamicList();
	head->next = NULL;
	num1 = 0;
}

inline void initStack() {
	top = new DynamicList();
	top->next = NULL;
	num2 = 0;
}

bool isListEmpty() {
	if (head->next == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}
bool isStackEmpty() {
	if (top->next == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

void printList() {
	cout << endl << "Состояние списка: ";
	if (!isListEmpty()) {
		cout << "в списке " << num1 << " элементов" << endl;
		DynamicList* current;
		current = head->next;
		int i = 1;
		string linkon;
		while (current != NULL) {
			if ((current->next) != NULL) linkon = (current->next)->value;
			else linkon = "NULL";
			cout << i << ") " << current->value << ", ссылается на: " << linkon << "" << endl;
			current = current->next;
			i++;
		}
	}
	else {
		cout << "Список пустой" << endl;
	}
}

void printStack() {
	if (!isStackEmpty()) {
		cout << endl << "Состояние стека удаленных элементов: ";
		cout << "в стеке " << num2 << " элементов" << endl;
		DynamicList* current;
		current = top->next;
		int i = 1;
		string linkon;
		while (current != NULL) {
			if ((current->next) != NULL) linkon = (current->next)->value;
			else linkon = "NULL";
			cout << i << ") " << current->value << ", ссылается на: " << linkon << "" << endl;
			current = current->next;
			i++;
		}
	}
	else {
		cout << "Вспомогательный стек пустой" << endl;
	}
}

void push() {
	string _value;
	DynamicList* current = nullptr;
	DynamicList* temp = new DynamicList;
	int choice = -1;
	if (isListEmpty()) {
		temp->next = NULL;
		head->next = temp;
		cout << endl << " Введите добавляемую строку: ";
		cin.clear();
		cin >> _value;
		cout << endl << " Элемент успешно добавлен! " << endl; temp->value = _value; num1++;
		return;
	}
	while ((choice != 0) && (choice != 1)) {
		cout << endl << " Куда добавить элемент?\n 0 - Перед заданным элементом\n 1 - После заданного элемента\n\n Введите номер команды: ";
		choice = check();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		int i = -1;
		if (choice == 0) {
				DynamicList* pred;
				pred = head;
				while (i == -1) {
					current = head->next;
					cout << endl << " Введите значение элемента, перед которым вы хотите добавить новый элемент: "; cin.clear(); getline(cin, _value);
					while (current != NULL) {
						if (current->value == _value) break;
						current = current->next;
						pred = pred->next;
					}
					if (current != NULL) i++;
					else { cout << " Строка " << _value << " не найдена. Попробуйте ввести другое значение" << endl; }
				}
				temp->next = current;
				pred->next = temp;
		}
		else if (choice == 1) {
			while (i == -1) {
				current = head->next;
				cout << endl << " Введите значение элемента, после которого вы хотите добавить новый элемент: "; cin.clear(); getline(cin, _value);
				while ((current != NULL) && (current->value != _value))
					current = current->next;
				if (current != NULL) i++;
				else { cout << " Строка " << _value << " не найдена. Попробуйте ввести другое значение" << endl; }
			}
			temp->next = current->next;
			current->next = temp;
		}
		else {
			cout << endl << "Ошибка ввода. Повторите попытку" << endl; choice = -1;
		}
	}
	cout << endl << " Введите добавляемую строку: ";
	cin.clear();
	cin >> _value;
	cout << endl << " Элемент успешно добавлен! " << endl; temp->value = _value; num1++;
}

void pop() {
	if (!isListEmpty()) {
		string cur_value;
		DynamicList* current;
		DynamicList* pred;
		current = head->next;
		pred = head;
		int choice = -1;
		int i = -1;
		while ((choice != 0) && (choice != 1)) {
			cout << endl << " Действительно удалить элемент или добавить во вспомогательный стек?\n 0 - Удалить с освобождением памяти\n 1 - Добавить во вспомогательный стек\n\n Введите номер команды: ";
			choice = check();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			printList();

			while (i == -1) {
				cout << endl << " Введите значение элемента, который хотите удалить: "; cin.clear(); getline(cin, cur_value);
				while (current != NULL) {
					if (current->value == cur_value) break;
					current = current->next;
					pred = pred->next;
					i++;
				}
				if (current != NULL) { i += 2; cout << " Строка " << cur_value << " найдена под номером " << i << ")" << endl; }
				else { cout << " Строка " << cur_value << " не найдена" << endl; }
			}
			if (choice == 0) {
				pred->next = current->next;
				delete current;
				num1--;
				cout << endl << "Теперь в списке " << num1 << " элементов" << endl;
			}
			else if (choice == 1) {
				pred->next = current->next;
				DynamicList* temp = current;
				temp->next = top->next;
				top->next = temp;
				num1--; num2++;
				cout << endl << "Теперь в основном списке " << num1 << " элементов, а во вспомогательном - " << num2 << " " << endl;
			}
			else {
				cout << endl << "Ошибка ввода. Повторите попытку" << endl; choice = -1;
			}
		}
	}
	else {
		cout << endl << "Удалять нечего. Список пуст" << endl;
	}
}

void find() {
	if (!isListEmpty()) {
		printList();
		string cur_value;
		cout << endl << " Введите строку, которую хотите найти: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, cur_value);
		int i = 1;
		DynamicList* current;
		current = head->next;
		while ((current != NULL) && (current->value != cur_value)) {
			current = current->next;
			i++;
		}
		if (current != NULL) cout << " Строка " << cur_value << " найдена под номером " << i << "" << endl;
		else cout << " Строка " << cur_value << " не найдена" << endl;
	}
	else {
		cout << endl << "Искать нечего. Список пуст" << endl;
	}
}

inline void сlearList() {
	DynamicList* current;
	while (head != NULL) {
		current = head;
		head = head->next;
		delete current;
	}
	initList();
	cout << endl << "Список очищен" << endl;
}

inline void сlearStack() {
	DynamicList* current;
	while (top != NULL) {
		current = top;
		top = top->next;
		delete current;
	}
	initStack();
	cout << endl << "Стек очищен" << endl;
}

void menu() {
	initList();
	initStack();
	int number;
	string value;
	bool stop = true;
	while (stop) {
		cout << "___________________________________________________________" << endl;
		cout << endl << "Выберите команду из списка:" << endl;
		cout << "1. Вывод текущего состояния списка на экран" << endl;
		cout << "2. Проверка пустоты списка" << endl;
		cout << "3. Добавить элемент в список" << endl;
		cout << "4. Удалить элемент из списка" << endl;
		cout << "5. Поиск элемента с заданной информационной частью" << endl;
		cout << "6. Вывод текущего состояния вспомогательного стека на экран" << endl;
		cout << "7. Очистить список" << endl;
		cout << "8. Очистить вспомогательный стек" << endl;
		cout << "9. Завершить работу программы" << endl;
		cout << "Номер команды: ";
		number = check();
		switch (number) {
		case 1: {
			printList();
			break;
		}
		case 2: {
			if (isListEmpty() == 1) {
				cout << endl << "Список пустой" << endl;
			}
			else {
				cout << endl << "Список не пустой" << endl;
			}
			break;
		}
		case 3: {
			push();
			break;
		}
		case 4: {
			pop();
			break;
		}
		case 5: {
			find();
			break;
		}
		case 6: {
			printStack();
			break;
		}
		case 7: {
			сlearList();
			break;
		}
		case 8: {
			сlearStack();
			break;
		}
		case 9: {
			сlearList();
			сlearStack();
			cout << endl << "Программа завершила работу" << endl;
			stop = !stop;
			break;
		}
		default: {
			cout << endl << "Ошибка ввода. Повторите попытку" << endl;
			break;
		}
		}
	}
}

int main() {
	setlocale(LC_ALL, "RU");
	menu();
	return 0;
}
