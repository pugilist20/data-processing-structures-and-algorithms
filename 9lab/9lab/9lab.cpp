#include <iostream>
#include <cstdlib>
#include <string>

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
    setlocale(LC_ALL, "RU");
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

        cout << "\nПострочный вывод в обратно-симметричном порядке:\n\n";
        backSymmetric(pRoot, 0);

        cout << "\nОчистка памяти\n";
        delTp(pRoot);
    }

    return 0;
}
