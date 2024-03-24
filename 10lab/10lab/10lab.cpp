#include <iostream>
#include <cstdlib>

using namespace std;

int amount;

int check() {
    int a;
    while (!(cin >> a) || (cin.peek() != '\n')) {
        cin.clear();
        while (cin.get() != '\n');
        cout << "\nОшибка ввода. Повторите попытку \n" << endl;
    }
    return a;
}

struct Tree {
    int value;
    Tree* left;
    Tree* right;
} *pRoot;

struct Stack {
    int level;
    Tree* point;
    Stack* next;
} *sp;

inline void initStack(Tree* pRoot) {
    sp = new Stack;
    sp->point = pRoot;
    sp->level = -1;
    sp->next = NULL;
}

bool isEmpty() {
    if (sp->level < 0) return 1;
    else return 0;
}

Tree* addNodes(Tree* pCurrent, int aN) {
    Tree* pTemp;
    int Nl, Nr;
    if (aN == 0)
        return NULL;
    else {
        Nl = aN / 2;
        Nr = aN - Nl - 1;
        pTemp = new Tree;
        pTemp->value = rand() % 100;
        pTemp->left = addNodes(pTemp->left, Nl);
        pTemp->right = addNodes(pTemp->right, Nr);
        pCurrent = pTemp;
        return pTemp;
    }
}

void forward(Tree* pCurrent, int level) {
    if (pCurrent != NULL) {
        string str;
        for (int i = 0; i < level; i++)
            str += "     ";
        cout << " " << str << pCurrent->value << "\n";
        forward(pCurrent->left, level + 1);
        forward(pCurrent->right, level + 1);
    }
}

void nonRecursive() {
    initStack(pRoot);
    Tree* pCurrentTree = pRoot;
    bool Stop = false;
    int level = 0;

    while (!Stop) {
        while (pCurrentTree != NULL) {
            Stack* item = new Stack;
            item->level = level;
            item->point = pCurrentTree;
            item->next = sp;
            sp = item;
            pCurrentTree = sp->point;
            pCurrentTree = pCurrentTree->left;
            level++;
        }
        if (isEmpty())
            Stop = true;
        else {
            level = sp->level;
            pCurrentTree = sp->point;
            string str = "";
            for (int i = 0; i < level; i++)
                str += "     ";
            cout << " " << str << (pCurrentTree->value) << "\n";
            Stack* current = sp;
            sp = sp->next;
            delete current;
            pCurrentTree = pCurrentTree->right;
            level++;
        }
    }
}

void symmetric(Tree* pCurrent, int level) {
    if (pCurrent != NULL) {
        symmetric(pCurrent->left, level + 1);
        string str;
        for (int i = 0; i < level; i++)
            str += "     ";
        cout << " " << str << pCurrent->value << "\n";
        symmetric(pCurrent->right, level + 1);
    }
}

void backSymmetric(Tree* pCurrent, int level) {
    if (pCurrent != NULL) {
        backSymmetric(pCurrent->right, level + 1);
        string str;
        for (int i = 0; i < level; i++)
            str += "     ";
        cout << " " << str << pCurrent->value << "\n";
        backSymmetric(pCurrent->left, level + 1);
    }
}

void delTp(Tree* pCurrent) {
    if (pCurrent != NULL) {
        delTp(pCurrent->left);
        delTp(pCurrent->right);
        delete pCurrent;
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0)));
    while (true) {
        cout << " ___________________________________________________________\n\n";
        amount = -1;
        while (amount <= 0) {
            cout << "Сколько вершин будет в идеально сбалансированном двоичном дереве?\nКол-во вершин: ";
            amount = check();
            if (amount <= 0) cout << "Дерево с неположительным числом " << amount << " выводиться не будет. Повторите вывод\n";
            else {
                pRoot = addNodes(pRoot, amount);
                cout << "Идеально сбалансированное дерево с " << amount << " вершинами создано\n";
            }
        }
        cout << "\nПострочный вывод в прямом порядке:\n\n";
        forward(pRoot, 0);
        cout << "\nПострочный вывод в симметричном порядке:\n\n";
        symmetric(pRoot, 0);
        cout << "\n Нерекурсивный вариант симметричного обхода:\n\n";
        nonRecursive();
        cout << "\nПострочный вывод в обратно-симметричном порядке:\n\n";
        backSymmetric(pRoot, 0);
        cout << "\nОчистка памяти\n";
        delTp(pRoot);
    }
    return 0;
}
