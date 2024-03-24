#include <iostream>
#include <cstdlib>

using namespace std;

bool founded = false;

int check() {
	int a;
	while (!(cin >> a) || (cin.peek() != '\n'))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "\nОшибка ввода. Повторите попытку ";
	}
	return a;
}

struct Tree {
	int value;
	int counter;
	Tree* Left;
	Tree* Right;
} *pRoot = NULL, * pParent = NULL;

void symmetric(Tree* pCurrent) {
	if (pCurrent != NULL) {
		symmetric(pCurrent->Left);
		cout << pCurrent->value << "(" << pCurrent->counter << "); ";
		symmetric(pCurrent->Right);
	}
}

void backSymmetric(Tree* pCurrent, int level) {
	if (pCurrent != NULL) {
		backSymmetric(pCurrent->Right, level + 1);
		string str;
		for (int i = 0; i < level; i++)
			str += "     ";
		cout << " " << str << pCurrent->value << "\n";
		backSymmetric(pCurrent->Left, level + 1);
	}
}

Tree* find(int _value) {
	Tree* pCurrent = pRoot;
	pParent = NULL;
	bool Stop = false;
	while ((pCurrent != NULL) && (!Stop)) {
		if (_value < pCurrent->value) {
			pParent = pCurrent;
			pCurrent = pCurrent->Left;
		}
		else if (_value > pCurrent->value) {
			pParent = pCurrent;
			pCurrent = pCurrent->Right;
		}
		else
			Stop = true;
	}
	return pCurrent;
}

void findDialog() {
	int _value;
	cout << "\nВведите значение ключа, которое хотите найти: "; _value = check();
	Tree* pTemp = find(_value);
	if (pTemp != NULL)
		cout << "Элемент с ключом '" << _value << "' найден. Число появлений: \n" << pTemp->counter << "\n";
	else
		cout << "Элемент с ключом '" << _value << "' не найден\n";
}

void print(int n) {
	if (pRoot != NULL) {
		if (n == 1) {
			cout << "\nПострочный вывод всех вершин в одну строку в соответствии с возрастанием их ключей (в строку):\n\n";
			symmetric(pRoot);
			cout << "\n";
		}
		if (n == 2) {
			cout << "\nПострочный вывод в обратно-симметричном порядке:\n\n";
			backSymmetric(pRoot, 0);
			cout << "\n";
		}
	}
	else {
		cout << "Дерево пустое\n\n";
	}
}

Tree* addRecursive(Tree* pCurrent, int _value) {
	if (pCurrent == NULL)
	{
		pCurrent = new Tree;
		pCurrent->value = _value;
		pCurrent->Left = pCurrent->Right = NULL;
		pCurrent->counter = 1;
	}
	else {
		if (_value < pCurrent->value)
			pCurrent->Left = addRecursive(pCurrent->Left, _value);
		else if (_value > pCurrent->value)
			pCurrent->Right = addRecursive(pCurrent->Right, _value);
		else
			pCurrent->counter++;
	}
	return pCurrent;
}

void addNonRecursive(int _value) {
	if (pRoot == NULL) {
		pRoot = new Tree;
		pRoot->Left = pRoot->Right = NULL;
		pRoot->value = _value;
		pRoot->counter = 1;
	}
	else {
		Tree* pParent = NULL, * pCurrent = pRoot;
		while (pCurrent != NULL) {
			pParent = pCurrent;
			if (_value < pCurrent->value)
				pCurrent = pCurrent->Left;
			else if (_value > pCurrent->value)
				pCurrent = pCurrent->Right;
			else {
				pCurrent = NULL;
				pCurrent->counter++;
			}
		}
		if (_value < pParent->value) {
			pCurrent = new Tree;
			pCurrent->Left = pCurrent->Right = NULL;
			pCurrent->counter = 1;
			pCurrent->value = _value;
			pParent->Left = pCurrent;
		}
		else if (_value > pParent->value) {
			pCurrent = new Tree;
			pCurrent->Left = pCurrent->Right = NULL;
			pCurrent->counter = 1;
			pCurrent->value = _value;
			pParent->Right = pCurrent;
		}
	}
}

void addNode() {
	int _value, n;
	cout << "\nВведите значение ключа у новой вершины: ";
	_value = check();
	cout << "\nКакой способ добавления использовать?\n1 - Рекурсивный способ\n2 - Нерекурсивный способ\nВаш выбор: ";
	n = check();
	while ((n != 1) && (n != 2)) {
		cout << "Такой команды не существует. Повторите ввод: "; n = check();
	}
	if (n == 1) {
		cout << "Выбран рекурсивный способ добавления \n";
		pRoot = addRecursive(pRoot, _value);
	}
	if (n == 2) {
		cout << "Выбран нерекурсивный способ добавления \n";
		addNonRecursive(_value);
	}
	cout << "Вершина с ключом '" << _value << "' добавлена \n";
}

void treeCreator() {
	srand(static_cast<unsigned int>(time(0)));
	int num = -1;
	while (num <= 0) {
		cout << "Сколько вершин будет в дереве?\nКол-во вершин: ";
		num = check();
		if (num <= 0) cout << "Невозможно создать дерево с отрицательным числом " << num << ". Повторите ввод\n";
		else {
			for (int i = 0; i < num; i++)
				pRoot = addRecursive(pRoot, rand() % 100);
			cout << "Двоичное дерево поиска с числом вершин '" << num << "' создано\n";
		}
	}
}

void delTree(Tree* pCurrent) {
	if (pCurrent != NULL) {
		delTree(pCurrent->Left);
		delTree(pCurrent->Right);
		delete pCurrent;
		cout << "Поддерево со значением корневой вершины '" << pCurrent->value << "' удалено\n";
	}
};

Tree* changer(Tree* p) {
	if (p->Right != NULL)
		p = changer(p->Right);
	return p;
};

Tree* deleteNode(Tree* pCurrent, int _value) {
	if (pCurrent == NULL)
		cout << "Удаляемая вершина не найдена\n";
	else if (_value < pCurrent->value)
		pCurrent->Left = deleteNode(pCurrent->Left, _value);
	else if (_value > pCurrent->value)
		pCurrent->Right = deleteNode(pCurrent->Right, _value);
	else {
		if (pCurrent->counter > 1)
			pCurrent->counter--;
		else {
			Tree* pTemp = pCurrent;
			if (pTemp->Right == NULL)
				pCurrent = pTemp->Left;
			else if (pTemp->Left == NULL)
				pCurrent = pTemp->Right;
			else if ((pTemp->Right == NULL) && (pTemp->Left == NULL))
				pCurrent = NULL;
			else {
				Tree* p = changer(pCurrent->Left);
				p = find(p->value);
				cout << "Значение заменяемой вершины: " << p->value << ", а родителя: " << pParent->value;
				pParent->Right = p->Left;
				pCurrent->value = p->value;
				pCurrent->Left = deleteNode(pCurrent->Left, p->value);
				pTemp = p;
				return pCurrent;
			}
			delete pTemp;
		}
	}
	return pCurrent;
}

void delNode() {
	print(2);
	int _value;
	cout << "\nВведите значение ключа вершины, которую хотите удалить: "; _value = check();
	pRoot = deleteNode(pRoot, _value);
	cout << "Вершина с ключом '" << _value << "' удалена\nТеперь дерево поиска имеет вид: \n";
	print(2);
}

int main() {
	setlocale(LC_ALL, "RU");
	srand(static_cast<unsigned int>(time(0)));
	pRoot = NULL;
	bool stop = true;
	while (stop) {
		cout << "___________________________________________________________\n\n"
			<< "Выберите действие из списка\n"
			<< "1 - Создание дерева с заданным числом вершин со случайными ключами\n"
			<< "2 - Добавление в дерево одной вершины с заданным пользователем значением ключа\n"
			<< "3 - Поиск в дереве вершины с заданным ключом\n"
			<< "4 - Вывод дерева в наглядном виде с помощью обратно-симметричного обхода\n"
			<< "5 - Вывод всех вершин в порядке возрастания их ключей\n"
			<< "6 - Удаление вершины с заданным значением ключа\n"
			<< "0 - Выход из программы\n"
			<< "Ваш выбор: ";
		int command = check();
		switch (command) {
		case 1: {
			treeCreator();
			break;
		}
		case 2: {
			addNode();
			break;
		}
		case 3: {
			findDialog();
			break;
		}
		case 4: {
			print(2);
			break;
		}
		case 5: {
			print(1);
			break;
		}
		case 6: {
			delNode();
			break;
		}
		case 7: {
			stop = false;
			delTree(pRoot);
			cout << "Программа завершила работу";
			break;
		}
		default: {
			cout << " Такой команды не существует. Повторите ввод: ";
			break;
		}
		}
	}
}
