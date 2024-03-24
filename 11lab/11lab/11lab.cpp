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
		cout << "\nОшибка ввода. Повторите попытку: ";
	}
	return a;
}

struct Tree {
	int value;
	Tree* Left;
	Tree* Right;
} *pRoot, * pParent;

void forward(Tree* pCurrent, int level) {
	if (pCurrent != NULL) {
		string str;
		for (int i = 0; i < level; i++)
			str += "     ";
		cout << " " << str << pCurrent->value << "\n";
		forward(pCurrent->Left, level + 1);
		forward(pCurrent->Right, level + 1);
	}
}

void symmetric(Tree* pCurrent, int level) {
	if (pCurrent != NULL) {
		symmetric(pCurrent->Left, level + 1);
		string str;
		for (int i = 0; i < level; i++)
			str += "     ";
		cout << " " << str << pCurrent->value << "\n";
		symmetric(pCurrent->Right, level + 1);
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

void find(Tree* pCurrent, int val) {
	if (!founded)
		if (pCurrent != NULL) {
			if (pCurrent->value == val) {
				founded = true;
				pParent = pCurrent;
			}
			else {
				find(pCurrent->Left, val);
				find(pCurrent->Right, val);
			}
		}
}

void findDialog() {
	int val;
	cout << "\nВведите значение вершины, которую хотите найти: "; val = check();
	founded = false;
	find(pRoot, val);
	if (founded) {
		cout << "Элемент '" << val << "' найден\n";
		founded = false;
	}
	else
		cout << "Элемент '" << val << "' не найден\n";
}

void print() {
	cout << "\nСостояние дерева:";
	if (pRoot != NULL) {
		cout << "\n\nПострочный вывод в прямом порядке:\n\n";
		forward(pRoot, 0);
		cout << "\nПострочный вывод в симметричном порядке:\n\n";
		symmetric(pRoot, 0);
		cout << "\nПострочный вывод в обратно-симметричном порядке:\n\n";
		backSymmetric(pRoot, 0);
	}
	else {
		cout << "Дерево пустое\n\n";
	}
}

Tree* addTree(Tree* pTemp, int val) {
	pTemp = new Tree;
	pTemp->Left = pTemp->Right = NULL;
	pTemp->value = val;
	return pTemp;
}

void addNode() {
	int val, n;
	if (pRoot != NULL) {
		cout << "\nВведите значение вершины для нового элемента: "; val = check();
		founded = false;
		find(pRoot, val);
		if (founded) {
			founded = false;
			if (pParent->Left == NULL || pParent->Right == NULL) {
				cout << "\nВведите значение, которое хотите присвоить вершине: "; val = check();
			}
			if (pParent->Left == NULL && pParent->Right == NULL) {
				cout << "\nВершина не имеет ни одного потомка. Какую вершину (1 - левый потомок; 2 - правый потомок) добавить?\n Ваш выбор: ";
				n = check();
				while ((n != 1) && (n != 2)) {
					cout << "Ошибка ввода. Повторите попытку: "; n = check();
				}
				if (n == 1) {
					pParent->Left = addTree(pParent->Left, val);
					cout << "Вершина успешно добавлена как левый потомок родительской вершины \n";
				}
				if (n == 2) {
					pParent->Right = addTree(pParent->Right, val);
					cout << "Верщина успешно добавлена как правый потомок родительской вершины\n";
				}
			}
			else if (pParent->Left == NULL) {
				pParent->Left = addTree(pParent->Left, val);
				cout << "Вершина добавлена как левый потомок родительской вершины\n";
			}
			else if (pParent->Right == NULL) {
				pParent->Right = addTree(pParent->Right, val);
				cout << "Вершина добавлена как правый потомок родительской вершины\n";
			}
			else { cout << "Добавление невозможно: вершина-родитель уже имеет двух потомков\n"; return; }
			print();
		}
		else cout << "Вершина-родитель '" << val << "' не найдена\n";
	}
	else {
		pRoot = new Tree;
		cout << "\nВведите значение вершины-корня, которую хотите добавить: "; val = check();
		pRoot->Left = pRoot->Right = NULL;
		pRoot->value = val;
		cout << "Корень дерева '" << pRoot->value << "' успешно создан\n";
	}
}

void delTree(Tree* pCurrent) {
	if (pCurrent != NULL) {
		delTree(pCurrent->Left);
		delTree(pCurrent->Right);
		delete pCurrent;
		cout << "Поддерево со значение корневой вершины'" << pCurrent->value << "' удалено\n";
	}
};

int main() {
	pRoot = NULL;
	bool stop = true;
	while (stop) {
		cout << "___________________________________________________________\n\n";
		cout << "Выберите комманду\n";
		cout << "1 - Поиск вершин с заданным значением информационной части\n";
		cout << "2 - Добавление левого или правого потомка для заданной вершины\n";
		cout << "3 - Построчный вывод дерева с помощью основных правил обхода\n";
		cout << "4 - Уничтожение всего дерева\n";
		cout << "5 - Выход из программы\n";
		cout << "Ваш выбор: ";
		int command = check();
		switch (command) {
		case 1: {
			findDialog();
			break;
		}
		case 2: {
			addNode();
			break;
		}
		case 3: {
			print();
			break;
		}
		case 4: {
			delTree(pRoot);
			pRoot = NULL;
			cout << "Дерево уничтожено";
			break;
		}
		case 5: {
			stop = false;
			cout << "\nПрограмма завершила работу\n";
			delTree(pRoot);
			break;
		}
		default: {
			cout << "Ошибка ввода. Повторите попытку";
		}
		}
	}
	return 0;
}
