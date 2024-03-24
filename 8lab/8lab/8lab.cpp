#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

int amount;

struct SubList {
	string value;
	SubList* next;
};

struct MainList {
	string id;
	MainList* nextMain;
	SubList* firstSub;
} *headMain;

int check() {
	int a;
	while (!(cin >> a) || (cin.peek() != '\n'))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << endl << "Ошибка ввода. Повторите попытку" << endl << endl;
	}
	return a;
}

inline void initList() {
	headMain = new MainList();
	headMain->nextMain = NULL;
	headMain->firstSub = NULL;
	amount = 0;
}

bool isMainListEmpty() {
	if (headMain->nextMain == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

bool isSubListEmpty(MainList* currentMain) {
	if (currentMain->firstSub->next == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

void printList() {
	cout << endl << "Состояние списка: ";
	if (!isMainListEmpty()) {
		cout << "в списке " << amount << " списков списков" << endl;
		MainList* mainCurrent = headMain->nextMain;
		while (mainCurrent != NULL) {
			cout << "Содержимое элемента " << mainCurrent->id << " основного списка:" << endl;
			int i = 1;
			if (!isSubListEmpty(mainCurrent)) {
				SubList* subCurrent = mainCurrent->firstSub->next;
				while (subCurrent != NULL) {
					cout << "   " << i << ") " << subCurrent->value << endl << "";
					subCurrent = subCurrent->next;
					i++;
				}
			}
			else cout << "   " << "<Пусто>" << endl;
			mainCurrent = mainCurrent->nextMain;
		}
	}
	else {
		cout << "Главный список пуст" << endl;
	}
}

void pushInMain() {
	string str;
	MainList* current = NULL;
	MainList* temp = new MainList;
	temp->firstSub = new SubList;
	int choice = -1;
	if (isMainListEmpty()) {
		temp->nextMain = NULL;
		temp->firstSub->next = NULL;
		headMain->nextMain = temp;
		cout << endl << "Введите название элемента главного списка: "; cin.clear(); cin >> str;
		temp->id = str; amount++;
		cout << temp->id << endl;
		cout << endl << "Элемент успешно добавлен в базовый список! " << endl;
		return;
	}
	while ((choice != 0) && (choice != 1)) {
		cout << endl << "Куда добавить элемент-список?\n 0 - Перед заданным элементом\n 1 - После заданного элемента\n\n Введите номер команды: ";
		choice = check();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		int i = -1;
		if (choice == 0) {
			MainList* pred = headMain;
			while (i == -1) {
				current = headMain->nextMain;
				cout << endl << "Введите значение элемента, перед которым вы хотите добавить новый элемент: "; cin.clear(); getline(cin, str);
				while (current != NULL) {
					if (current->id == str) break;
					current = current->nextMain;
					pred = pred->nextMain;
				}
				if (current != NULL) i++;
				else { cout << "Строка " << str << " не найдена.Попробуйте ввести другое значение" << endl; }
			}
			temp->nextMain = current;
			temp->firstSub->next = NULL;
			pred->nextMain = temp;
		}
		else if (choice == 1) {
			while (i == -1) {
				current = headMain->nextMain;
				cout << endl << " Введите значение элемента, ПОСЛЕ КОТОРОГО вы хотите добавить новый элемент: ";
				cin.clear(); getline(cin, str);
				while ((current != NULL) && (current->id != str))
					current = current->nextMain;
				if (current != NULL) i++;
				else { cout << " Строка " << str << " не найдена. Попробуйте ввести другое значение" << endl; }
			}
			temp->nextMain = current->nextMain;
			temp->firstSub->next = NULL;
			current->nextMain = temp;
			temp->id = str; amount++;

		}
		else {
			cout << endl << "Ошибка ввода. Повторите попытку" << endl;
		}
	}
	cout << endl << " Введите название элемента главного списка : "; cin.clear(); getline(cin, str);

	temp->id = str; amount++;

	cout << endl << " Элемент успешно добавлен в базовый список! \n";
}

void pushInSub() {
	if (!isMainListEmpty()) {
		string str;
		MainList* currentMain = NULL;
		int i = -1;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		while (i == -1) {
			currentMain = headMain->nextMain;
			cout << endl << "Введите название заголовка связанного списка, в который хотите добавить новый элемент: ";
			cin.clear(); cin >> str;
			while ((currentMain != NULL) && (currentMain->id != str))
				currentMain = currentMain->nextMain;
			if (currentMain != NULL) i++;
			else { cout << "Строка " << str << " не найдена. Попробуйте ввести другое значение" << endl; }
		}
		SubList* head = currentMain->firstSub;
		SubList* currentSub = NULL;
		SubList* temp = new SubList;
		int choice = -1;
		if (isSubListEmpty(currentMain)) {
			temp->next = NULL;
			head->next = temp;
			cout << endl << "Введите добавляемую строку: "; cin.clear(); cin >> str;
			cout << endl << "Элемент успешно добавлен! " << endl; temp->value = str;
			return;
		}
		while ((choice != 0) && (choice != 1)) {
			cout << endl << "Куда добавить элемент ? \n0 - Перед заданным элементом\n1 - После заданного элемента\n\nВведите номер команды : ";
			choice = check();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (choice == 0) {
				SubList* pred = head;
				i = -1;
				while (i == -1) {
					currentSub = head->next;
					cout << endl << "Введите значение элемента, ПЕРЕД КОТОРЫМ вы хотите добавить новый элемент: "; cin.clear(); cin >> str;
					while (currentSub != NULL) {
						if (currentSub->value == str) break;
						currentSub = currentSub->next;
						pred = pred->next;
					}
					if (currentSub != NULL) i++;
					else { cout << "Строка " << str << " не найдена. Попробуйте ввести другое значение" << endl; }
				}
				temp->next = currentSub;
				pred->next = temp;
			}
			else if (choice == 1) {
				i = -1;
				while (i == -1) {
					currentSub = head->next;
					cout << endl << "Введите значение элемента, ПОСЛЕ КОТОРОГО вы хотите добавить новый элемент: "; cin.clear(); cin >> str;
					while ((currentSub != NULL) && (currentSub->value != str))
						currentSub = currentSub->next;
					if (currentSub != NULL) i++;
					else { cout << "Строка " << str << " не найдена. Попробуйте ввести другое значение" << endl; }
				}
				temp->next = currentSub->next;
				currentSub->next = temp;
			}
			else {
				cout << endl << "Ошибка ввода. Повторите попытку" << endl; choice = -1;
			}
		}
		cout << endl << "Введите добавляемую строку: "; cin.clear(); cin >> str;
		cout << endl << "Элемент успешно добавлен! " << endl; temp->value = str;
	}
	else {
		cout << endl << "Чтобы добавить элемент в связанный список сначала нужно создать хотя бы один связанный список" << endl;
	}
}

void popFromMain() {
	if (!isMainListEmpty()) {
		string str;
		MainList* mainCurrent = NULL;
		MainList* mainPred = NULL;
		SubList* subCurrent;
		int i = -1;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		while (i == -1) {
			mainCurrent = headMain->nextMain;
			mainPred = headMain;
			cout << endl << "Введите название заголовка связанного списка, чтобы удалить его: ";
			cin.clear(); cin >> str;
			while (mainCurrent != NULL) {
				if (mainCurrent->id == str) break;
				mainCurrent = mainCurrent->nextMain;
				mainPred = mainPred->nextMain;
			}
			if (mainCurrent != NULL) { i++; cout << "Строка " << str << " удалена" << endl; }
			else { cout << "Строка " << str << " не найдена. Введите другое значение" << endl; }
		}
		while (mainCurrent->firstSub->next != NULL) {
			subCurrent = mainCurrent->firstSub;
			mainCurrent->firstSub = mainCurrent->firstSub->next;
			delete subCurrent;
		}

		delete mainCurrent->firstSub;

		mainPred->nextMain = mainCurrent->nextMain;
		delete mainCurrent;
	}
	else {
		cout << "Удалять нечего. Список пуст" << endl;
	}
}

void popFromSub() {
	if (!isMainListEmpty()) {
		printList();
		string str;
		MainList* currentMain = NULL;
		int i = -1;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		while (i == -1) {
			currentMain = headMain->nextMain;
			cout << endl << "Введите значение заголовка связного списка, в котором хотите удалить элемент: ";
			cin.clear(); cin >> str;
			while ((currentMain != NULL) && (currentMain->id != str))
				currentMain = currentMain->nextMain;
			if (currentMain != NULL) i++;
			else { cout << "Строка " << str << " не найдена. Попробуйте ввести другое значение" << endl; }
		}
		if (!isSubListEmpty(currentMain)) {
			SubList* head = currentMain->firstSub;
			SubList* current = NULL;
			SubList* pred = NULL;
			i = -1;
			while (i == -1) {
				current = head->next;
				pred = head;
				cout << endl << "Введите значение элемента, который хотите удалить: "; cin.clear(); cin >> str;
				while (current != NULL) {
					if (current->value == str) break;
					current = current->next;
					pred = pred->next;
				}
				if (current != NULL) { i++; cout << "Строка " << str << " найдена под номером " << i << ")" << endl; }
				else { cout << "Строка " << str << " не найдена" << endl; }
			}
			pred->next = current->next;
			cout << endl << "Элемент '" << current->value << "' удален из связанного списка '" << currentMain->id << "' " << endl;
			delete current;
		}
		else {
			cout << endl << "Удалять нечего. Список пуст" << endl;
		}
	}
	else {
		cout << endl << "Удалять нечего. Список пуст" << endl;
	}
}

void find() {
	if (!isMainListEmpty()) {
		printList();
		string str;
		cout << endl << "Введите строку, которую хотите найти: ";
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cin >> str;
		int j = 0;
		MainList* currentMain = headMain->nextMain;
		while (currentMain != NULL) {
			if (!isSubListEmpty(currentMain)) {
				int i = 1;
				SubList* subCurrent = currentMain->firstSub->next;
				while ((subCurrent != NULL) && (subCurrent->value != str)) {
					subCurrent = subCurrent->next;
					i++;
				}
				if (subCurrent != NULL) { cout << "Строка " << str << " найдена в списке " << currentMain->id << endl; j++; }
				else cout << "Строка не найдена" << endl;
			}
			else {
				cout << "Связанный список " << currentMain->id << " пуст" << endl;
			}
			currentMain = currentMain->nextMain;
		}
		if (j == 0) cout << endl << "Строка " << str << " не найдена" << endl;
		else cout << endl << "Найдено " << j << " элементов" << endl;
	}
	else {
		cout << endl << "Искать нечего. Список пуст" << endl;
	}
}

inline void ClearList() {
	MainList* mainCurrent;
	SubList* subCurrent;
	mainCurrent = headMain;
	while (headMain != NULL) {
		mainCurrent = headMain;
		while (mainCurrent->firstSub != NULL) {
			subCurrent = mainCurrent->firstSub;
			mainCurrent->firstSub = mainCurrent->firstSub->next;
			delete subCurrent;
		}
		headMain = mainCurrent->nextMain;
		delete mainCurrent;
	}
	cout << endl << "Список очищен" << endl;
}

void menu() {
	int command;
	while (true) {
		cout << "___________________________________________________________" << endl;
		cout << endl << "Выберите команду из списка:" << endl;
		cout << "1. Вывод текущего состояния списка на экран" << endl;
		cout << "2. Проверка пустоты главного списка" << endl;
		cout << "3. Добавить элемент в список с пустым связанным списком" << endl;
		cout << "4. Добавить элемент в связанный список" << endl;
		cout << "5. Удалить элемент из базового списка" << endl;
		cout << "6. Удалить элемент из связанного списка" << endl;
		cout << "7. Поиск заданного элемента" << endl;
		cout << "8. Очистить список списков" << endl;
		cout << "9. Завершить работу программы" << endl;
		cout << "Номер команды: ";
		command = check();
		switch (command) {
		case 1: {
			printList();
			break;
		}
		case 2: {
			if (isMainListEmpty() == 1) cout << endl << "Главный список пуст" << endl;
			else cout << endl << "Главный список не пустой" << endl;
			break;
		}
		case 3: {
			pushInMain();
			break;
		}
		case 4: {
			pushInSub();
			break;
		}
		case 5: {
			popFromMain();
			break;
		}
		case 6: {
			popFromSub();
			break;
		}
		case 7: {
			find();
			break;
		}
		case 8: {
			ClearList();
			initList();
			break;
		}
		case 9: {
			ClearList();
			cout << endl << "Программма завершила работу" << endl;
			break;
		}
		default: {
			cout << endl << "ОШИБКА ВВОДА. ПОВТОРИТЕ ВВОД КОМАНДЫ" << endl;
			break;
		}
		}
	}
}

int main() {
	setlocale(LC_ALL, "RU");
	initList();
	menu();
	return 0;
}
