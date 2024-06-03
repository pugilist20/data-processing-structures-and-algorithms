#include <iostream>

using namespace std;

int* arr = NULL;
int num;
int max_key;

struct List {
    int key = -1;
    List* pNext = NULL;
    List* tail = NULL;
} *list = NULL, * head = NULL;


int check() {
    int a;
    while (!(cin >> a) || (cin.peek() != '\n'))
    {
        cin.clear();
        while (cin.get() != '\n');
        cout << "\n Ошибка ввода. Повторите попытку ";
    }
    return a;
}

int* copyArr() {
    int* cpArr = new int[num];
    for (int i = 0; i < num; i++) {
        cpArr[i] = arr[i];
    }
    return cpArr;
}

void printArr(int* cpArr) {
    for (int i = 0; i < num; i++) {
        cout << cpArr[i] << " ";
    }
    cout << endl;
    cout << endl;
}

void createArray(int n) {
    int temp, r;
    if (num == NULL) {
    cout << "Введите количество элементов массива (не более 10 000) ";
}
    while (num < 1 || num > 10000) {
        num = check();

        if (num < 1 || num > 10000) {
            cout << "Введенное недопустимое значение. Повторите ввод:" << endl;
        }
    }
    if (arr != NULL) {
        delete[] arr;
    }
    arr = new int[num];
    if (n == 1) {
        for (int i = 0; i < num; i++) {
            arr[i] = i;
        }
        max_key = num;
    }
    else if (n == 2) {
        max_key = num - num / 3;
        for (int i = 0; i < max_key; i++) {
            arr[i] = i;
        }
        for (int i = max_key; i < num; i++) {
            arr[i] = rand() % max_key;
        }
    }

    for (int i = 0; i < num; i++) {
        r = rand() % num;
        temp = arr[i];
        arr[i] = arr[r];
        arr[r] = temp;
    }
    printArr(arr);
}



void pocketSort() {
    createArray(1);
    int* cpArr = copyArr();
    int temp, n = -1;
    cout << "Использовать второй массив? \n Да - 1\n Нет - 2\n Выбор: ";
    n = check();
    while (n < 1 || n > 2) {
        cout << "Ошибка ввода. Повторите попытку" << endl;
        n = check();
    }
    if (n == 1) {
        for (int i = 0; i < num; i++) {
            while (cpArr[i] != i) {
                temp = cpArr[cpArr[i]];
                cpArr[cpArr[i]] = cpArr[i];
                cpArr[i] = temp;
            }
        }
    }
    else {
        int* secondArr = new int[num];
        for (int i = 0; i < num; i++) {
            secondArr[cpArr[i]] = cpArr[i];
        }
        delete[] cpArr;
        cpArr = secondArr;
    }

    printArr(cpArr);
    delete[] cpArr;
}

void cleanList(List* current) {
    if (current->pNext != NULL) {
        cleanList(current->pNext);
    }
    delete current;
}

int* list_toArray(List* _head) {
    List* current = _head;
    int* cpArr = new int[num];
    for (int i = 0; i < num; i++) {
        cpArr[i] = current->key;
        current = current->pNext;
    }
    return cpArr;
}

List* combine(List* _list) {
    List* _head = new List;
    _head->key = _list[0].key;
    _head->pNext = _list[0].pNext;
    _head->tail = _list[0].tail;
    List* current = _head;
    for (int i = 0; i < max_key - 1; i++) {
        if (_list[i].tail != NULL) {
            current = _list[i].tail;
        }
        current->pNext = new List;
        current = current->pNext;
        current->key = _list[i + 1].key;
        current->pNext = _list[i + 1].pNext;
        current->tail = _list[i + 1].tail;
    }
    return _head;
}

void general_pocketSort() {
    createArray(2);
    int* cpArr = copyArr();
    list = new List[max_key];
    for (int i = 0; i < num; i++) {
        if (list[cpArr[i]].key == -1) {
            list[cpArr[i]].key = cpArr[i];
        }
        else if (list[cpArr[i]].pNext == NULL) {
            list[cpArr[i]].pNext = new List;
            list[cpArr[i]].tail = list[cpArr[i]].pNext;
            list[cpArr[i]].pNext->key = cpArr[i];
        }
        else if (list[cpArr[i]].tail->pNext == NULL) {
            list[cpArr[i]].tail->pNext = new List;
            list[cpArr[i]].tail->pNext->key = cpArr[i];
            list[cpArr[i]].tail = list[cpArr[i]].tail->pNext;
        }
    }
    head = combine(list);
    cpArr = list_toArray(head);
    head = NULL;
    printArr(cpArr);
    delete[] cpArr;
    delete[] list;
}

void bit_pocketSorting() {
    createArray(2);
    int* cpArr = copyArr();
    int temp = max_key;
    int k = 0;
    int x, _max;
    while (temp != 0) {
        temp = temp / 10;
        k++;
    }
    cout << "Count of bits: " << k << endl;
    for (int i = 1; i <= k; i++) {
        list = new List[10];
        for (int j = 0; j < num; j++) {
            x = cpArr[j];
            for (int z = 1; z < i; z++) {
                x = x / 10;
            }
            x = x % 10;
            if (list[x].key == -1) {
                list[x].key = cpArr[j];
            }
            else if (list[x].pNext == NULL) {
                list[x].pNext = new List;
                list[x].tail = list[x].pNext;
                list[x].pNext->key = cpArr[j];
            }
            else if (list[x].tail->pNext == NULL) {
                list[x].tail->pNext = new List;
                list[x].tail->pNext->key = cpArr[j];
                list[x].tail = list[x].tail->pNext;
            }
        }
        _max = max_key;
        max_key = 10;
        head = combine(list);
        max_key = _max;
        cpArr = list_toArray(head);
        cleanList(head);
        head = NULL;
        cout << "Sorting by k = " << i << endl;
        printArr(cpArr);
        delete[] list;
    }
    delete[] cpArr;
}   

int main() {
    setlocale(LC_ALL, "RU");
    srand(static_cast<unsigned int>(time(0)));
    bool stop = true;
    while (stop) {
        cout << " ___________________________________________________________\n\n"
            << " Специальные методы сортировки\n"
            << "\n Выберите метод из списка\n"
            << " 1 - выполнить простейшую карманную сортировку\n"
            << " 2 - выполнить обобщенную карманную сортировку\n"
            << " 3 - выполнить поразрядную сортировку\n"
            << " 0 - выход из программы\n"
            << " Ваш выбор: ";  
        int command = check();
        switch (command) {
        case 1: {
            pocketSort();
            break;
        }
        case 2: {
            general_pocketSort();
            break;
        }
        case 3: {
            bit_pocketSorting();
            break;
        }
        case 0: {
            cout << "Программа завершила работу";
            delete[] arr;
            break;
        }
        }
    }
}
