#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

int amount;

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
	DynamicList* right, * left;
} *Head;

void initList() {
	Head = new DynamicList();
	Head->left = Head;
	Head->right = Head;
	Head->value = "HEAD";
	amount = 0;
}

bool isListEmpty() {
	if (Head->right == Head)
		return 1;
	else return 0;
}

void printList() {
	cout << endl << "Состояние списка: ";
	if (!isListEmpty()) {
		cout << "в списке " << amount << " элементов" << endl;
		int choice = -1;
		while ((choice != 0) && (choice != 1)) {
			cout << endl << "В каком направлении вывести элементы списка?" << endl << "0 - В прямом" << endl << "1 - В обратном\n\n Введите номер команды : ";
			choice = check();
			DynamicList* current;
			int i;
			string leftlink, rightlink;
			if (choice == 0) {
				i = 1;
				current = Head->right;
				while (current != Head) {
					rightlink = (current->right)->value;
					leftlink = (current->left)->value;
					cout << i << ") " << current->value << ", левый сосед: " << leftlink << ", правый сосед: " << rightlink << endl << "";
					current = current->right;
					i++;
				}
			}
			else if (choice == 1) {
				i = amount;
				current = Head->left;
				while (current != Head) {
					rightlink = (current->right)->value;
					leftlink = (current->left)->value;
					cout << i << ") " << current->value << ", левый сосед: " << leftlink << ", правый сосед: " << rightlink << endl << "";
					current = current->left;
					i--;
				}
			}
			else { cout << endl << "Ошибка ввода. Повторите попытку" << endl; choice = -1; }
		}
	}
	else cout << "Список пуст" << endl;
}

void push() {
	string str;
	DynamicList* current = NULL;
	DynamicList* temp = new DynamicList;
	int choice = -1;
	if (isListEmpty()) {
		temp->right = Head; temp->left = Head;
		Head->right = temp; Head->left = temp;
		cout << endl << "Введите добавляемую строку: ";
		cin.clear();
		cin >> str;
		temp->value = str;
		amount++;
		cout << endl << "Элемент успешно добавлен! " << endl;
		return;
	}
	while ((choice != 0) && (choice != 1)) {
		cout << endl << "Куда добавить элемент?\n0 - Перед заданным элементом\n1 - После заданного элемента\n\n Введите номер команды: ";
		choice = check();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		int i = -1;
		if (choice == 0) {
			while (i==-1) {
				current = Head->right;
				cout << endl << "Введите значение элемента, перед которым вы хотите добавить новый элемент: "; cin.clear(); getline(cin, str);
				while ((current != Head) && (current->value != str))
					current = current->right;
				if (current != Head) {
					temp->right = current;
					temp->left = current->left;
					(current->left)->right = temp;
					current->left = temp;
					i++;
				}
				else cout << "Строка " << str << " не найдена. Попробуйте ввести другое значение" << endl;
			}
		}
		else if (choice == 1) {
			while (i==-1) {
				current = Head->right;
				cout << endl << "Введите значение элемента, после которого вы хотите добавить новый элемент: "; cin.clear(); getline(cin, str);
				while ((current != Head) && (current->value != str))
					current = current->right;
				if (current != Head) {
					temp->right = current->right;
					temp->left = current;
					(current->right)->left = temp;
					current->right = temp;
					i++;
				}
				else cout << "Строка " << str << " не найдена. Попробуйте ввести другое значение" << endl;
			}
		}
		else { cout << endl << "Ошибка ввода.Повторите попытку" << endl; choice = -1; }
	}
	cout << endl << "Введите добавляемую строку: ";
	cin.clear();
	cin >> str;
	temp->value = str;
	amount++;
	cout << endl << "Элемент успешно добавлен! " << endl;
}

void pop() {
	if (!isListEmpty()) {
		string str;
		DynamicList* current;
		current = Head->right;
		printList();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		while (true) {
			cout << endl << "Введите значение элемента, который хотите удалить: "; cin.clear(); getline(cin, str);
			while ((current != Head) && (current->value != str))
				current = current->right;
			if (current != Head) {
				cout << "Строка " << str << " удалена" << endl;
				(current->left)->right = current->right;
				(current->right)->left = current->left;
				delete current;
				amount--;
				cout << endl << "Теперь в списке " << amount << " элементов" << endl;
				return;
			}
			else cout << "Строка " << str << " не найдена" << endl;
		}
	}
	else cout << endl << "Удалять нечего. Список пуст" << endl;
}

void find() {
	if (!isListEmpty()) {
		string str;
		cout << endl << "Введите строку, которую хотите найти: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, str);
		int choice = -1, i;
		DynamicList* current;
		while ((choice != 0) && (choice != 1)) {
			cout << endl << "В каком направлении произвести поиск элемента?\n0 - В прямом\n1 - В обратном\n\nВведите номер команды: ";
			choice = check();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (choice == 0) {
				i = 1;
				current = Head->right;
				while ((current != Head) && (current->value != str)) {
					current = current->right;
					i++;
				}
				if (current != Head) cout << "Строка " << str << " найдена под номером " << i << endl << "";
				else cout << "Строка " << str << " не найдена" << endl;
			}
			else if (choice == 1) {
				i = amount;
				current = Head->left;
				while ((current != Head) && (current->value != str)) {
					current = current->left;
					i--;
				}
				if (current != Head) cout << "Строка " << str << " найдена под номером " << i << endl << "";
				else cout << "Строка " << str << " не найдена" << endl;
			}
			else {
				cout << endl << "Ошибка ввода. Повторите попытку" << endl; choice = -1;
			}
		}
	}
	else {
		cout << endl << "Искать нечего. Список пуст." << endl;
	}
}

void clearList() {
	DynamicList* current;
	(Head->left)->right = NULL;
	while (Head != NULL) {
		current = Head;
		Head = Head->right;
		delete current;
	}
	cout << endl << "Список очищен" << endl;
}

void menu() {
	initList();
	int command;
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
		cout << "6. Очистить список" << endl;
		cout << "7. Завершить работу программы" << endl;
		cout << "Номер команды: ";
		command = check();
		switch (command) {
		case 1: {
			printList();
			break;
		}
		case 2: {
			if (isListEmpty() == 1) cout << endl << "Список пуст" << endl;
			else cout << endl << "Список не пустой" << endl;
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
			clearList();
			initList();
			break;
		}
		case 7: {
			clearList();
			cout << endl << "Программа завершила работу" << endl;
			stop = false;
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

