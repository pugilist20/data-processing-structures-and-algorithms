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

struct Stack {
	int value;
	Stack* next;
}*stack, *stackSup;

void init() {
	stack = NULL;
	stackSup = NULL;
}

bool isEmpty() {
	if (stack == NULL) {
		return true;
	}
	else {
		return false;
	}
}

bool isEmptySup() {
	if (stackSup == NULL) {
		return true;
	}
	else {
		return false;
	}
}

Stack* add(Stack* temp, int val) {
	Stack* element = new Stack;
	element->value = val;
	element->next = temp;
	temp = element;
	return temp;
}

void addRand() {
	cout << "Введите желаемое количество элементов: " << endl;
	int count = check();
	for (int i = 0; i < count; i++) {
		stack = add(stack, rand());
	}
}

Stack* remove(Stack* temp) {
	if (!isEmpty()) {
		int value = stack->value;
		Stack* element;
		element = temp;
		temp = temp->next;
		delete element;
		return temp;
	}
	else {
		return temp;
	}
}

void moveToSup() {
	if (!isEmpty()) {
		Stack* temp = stack;
		stack = stack->next;
		temp->next = stackSup;
		stackSup = temp;
	}
	else {
		cout << "Главный стек пуст" << endl;
	}
}


void addFromSup() {
	if (!isEmptySup()) {
		Stack* element = stackSup;
		stackSup = stackSup->next;
		element->next = stack;
		stack = element;
	}
	else {
		cout << "Вспомогательный стек пуст" << endl;
	}
}

void printStack(Stack* temp) {
	if (temp != NULL) {
		cout << endl;
		Stack* current = temp;
		int i = 1;
		do {
			cout << i << ". " << current->value << endl;
			current = current->next;
			i++;
		} while (current != NULL);
	}
}

void menu() {
	srand(time(0));
	init();
	bool stop=true;
	while (stop) {
		cout << "Выберите команду из предложенных: " << endl
			<< "1. Добавить элемент в главный стек" << endl
			<< "2. Удалить элемент из вершины главного стека" << endl
			<< "3. Вывести состояние главного стека" << endl
			<< "4. Добавить несколько рандомных чисел в главный стек" << endl
			<< "5. Вывести состояние вспомогательного стека" << endl
			<< "6. Остановить программу" << endl
			<< "=====================================================" << endl;
		int command1 = check();
		switch (command1) {
		case 1:
		{
			cout << "Уточните происхождение этого элемента: " << endl
				<< "1. Действительно создание нового элемента" << endl
				<< "2. Выбор его с вершины вспомогательного стека" << endl;
			int command2 = check();
			if (command2 == 1) {
				cout << "Введите число: " << endl;
				int num = check();
				stack = add(stack, num);
			}
			else if (command2 == 2) {
				if (!isEmptySup()) {
					addFromSup();
				}
				else {
					cout << "Вспомогательный стек пуст" << endl;
				}
			}
			else {
				cout << "Ошибка ввода, повторите попытку" << endl;
			}
			break;
		}
		case 2:
		{
			cout << "Уточните что делать с этим элементом: " << endl
				<< "1. Действительно удалить с освобождение памяти" << endl
				<< "2. Включить его в вершину вспомогательного стека" << endl;
			int command2 = check();
			if (command2 == 1) {
				if (!isEmpty()) {
					stack = remove(stack);
				}
				else {
					cout << "Главный стек пуст" << endl;
				}
			}
			else if (command2 == 2) {
				if (!isEmpty()) {
					moveToSup();

				}
				else {
					cout << "Главный стек пуст" << endl;

				}
			}
			else {
				cout << "Ошибка ввода, повторите попытку" << endl;
			}
			break;
		}
		case 3:
		{
			if (!isEmpty()) {
				cout << "Состояние главного стека: ";
				printStack(stack);
			}
			else {
				cout << "Главный стек пуст" << endl;
			}
			break;
		}
		case 4:
		{
			addRand();
			break;
		}
		case 5:
		{
			if (!isEmptySup()) {
				cout << "Состояние вспомогательного стека: " << endl;
				printStack(stackSup);
			}
			else {
				cout << "Вспомогательный стек пуст" << endl;
			}
			break;
		}
		case 6:
		{
			stop = !stop;
			cout << "Программа завершила работу" << endl;
			break;
		}
		default:
		{
			cout << "Ошибка ввода, повторите попытку" << endl;
		}
		}
		
		cout << "=====================================================" << endl;

	}
}


int main()
{
	setlocale(LC_ALL, "RU");
	menu();
	delete stack, stackSup;
}

