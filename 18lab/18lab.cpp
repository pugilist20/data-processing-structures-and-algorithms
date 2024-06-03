#include <iostream>

using namespace std;

int const gl_size = 10;
int hash_counter = 0;
int switch_counter = 0;

string keys[] = { "Binate", "Curolo", "Dimune", "Exave", "Furcon",
    "Golire", "Hirset", "Icival", "Jasune", "Kobate",
    "Lemure", "Morove", "Nurato", "Opele", "Pexise",
    "Quomel", "Risole", "Sutave", "Tupile", "Uleset",
    "Vivore", "Wenove", "Xofine", "Yulore", "Zedire",
    "Amelox", "Bregilo", "Crepeto", "Dusene", "Eraqu",
    "Folime", "Grinote", "Huxilo", "Isorex", "Jopune",
    "Ketale", "Limire", "Mavero", "Noveno", "Oxipe",
    "Perale", "Quixote", "Rolene", "Stemix", "Tuxedo",
    "Uveral", "Venore", "Wexite", "Xenose", "Yofime" };

int console_work() {
    int a;
    while (!(cin >> a) || (cin.peek() != '\n'))
    {
        cin.clear();
        while (cin.get() != '\n');
        cout << "\n ОШИБКА ВВОДА. ПОВТОРИТЕ ВВОД: ";
    }
    return a;
}

struct Node {
    Node* pNext = NULL;
    Node* pPrev = NULL;
    string value = "";
};

struct hashElement {
    Node* first = NULL;
    Node* last = NULL;
    int el_count = 0;
} hashTable[gl_size];

bool isEmpty() {
    return hash_counter == 0;
}

bool isFull() {
    return hash_counter == gl_size;
}

int get_code(string _str, int _size) {
    int code = 0;
    for (int i = 0; i < _str.length(); i++) {
        code += (int)_str[i];
    }
    // cout << "Code of key is " << code << endl;
    code = code % _size;
    //cout << "Index of element is " << code << endl;
    return code;
}

string get_string() {
    string str;
    cin >> str;
    return str;
}

void add_element(string _str) {
    int code = 0;
    code = get_code(_str, gl_size);
    Node* current = hashTable[code].first;

    while (current != NULL) {
        if (current->value == _str) {
            cout << "Элемент уже добавлен" << endl;
            return;
        }
        current = current->pNext;
    }

    Node* new_el = new Node();
    new_el->value = _str;
    hashTable[code].el_count++;

    if (hashTable[code].first == NULL) {
        hashTable[code].first = new_el;
        hashTable[code].last = new_el;
        hash_counter++;
        cout << "Элемент добавлен по индексу " << code << endl;
    }
    else {
        Node* _current = hashTable[code].last;
        _current->pNext = new_el;
        new_el->pPrev = _current;
        hashTable[code].last = new_el;
        cout << "Элемент добавлен в конец списка, индекс которого " << code << endl;
        cout << "Количество сравнений: " << hashTable[code].el_count << endl;
    }
}

void deleteElement(string _str) {
    int code = 0;
    code = get_code(_str, gl_size);
    int switch_counter = 0;
    Node* current = hashTable[code].first;
    switch_counter++;

    while (current->value != _str) {
        switch_counter++;
        current = current->pNext;
    }

    if (hashTable[code].first == hashTable[code].last) {
        hashTable[code].first = NULL;
        hashTable[code].last = NULL;
        hash_counter--;
    }
    else if (current == hashTable[code].first) {
        hashTable[code].first = current->pNext;
        hashTable[code].first->pPrev = NULL;
    }
    else if (current == hashTable[code].last) {
        hashTable[code].last = current->pPrev;
        hashTable[code].last->pNext = NULL;
    }
    else {
        Node* temp = current->pPrev;
        current->pNext->pPrev = temp;
        temp->pNext = current->pNext;
    }

    hashTable[code].el_count--;
    cout << "Элемент " << _str << " был удален" << endl;
    cout << "Количество сравнений: " << switch_counter << endl;
    delete current;
}

int findElement(string _str, int _hashSize, hashElement _hashTable[]) {
    switch_counter = 0;
    int code = 0;
    code = get_code(_str, _hashSize);
    Node* current = _hashTable[code].first;
    switch_counter++;
    while (current != NULL) {
        if (current->value == _str) {
            break;
        }
        switch_counter++;
        current = current->pNext;
    }
    if (current == NULL) {
        return -1;
    }
    else {
        cout << "Элемент " << _str << " в списке " << code << ") " << " на позиции " << switch_counter - 1 << endl;
        cout << "Количество сравнений: " << switch_counter << endl;
        return code;
    }
}

void print_hash() {
    for (int i = 0; i < gl_size; i++) {
        if (hashTable[i].first != NULL) {
            cout << i << ") ";
            Node* current = hashTable[i].first;
            while (current != NULL) {
                cout << current->value << " ";
                current = current->pNext;
            }
            cout << endl;
        }
    }
}

void clean() {
    for (int i = 0; i < gl_size; i++) {
        Node* current = hashTable[i].first;
        Node* temp;
        while (current != NULL) {
            temp = current;
            current = current->pNext;
            delete temp;
        }
        hashTable[i].first = NULL;
        hashTable[i].last = NULL;
    }
}

int addElementTest(hashElement _hashTable[], string words[], int _hashSize, string randomWord) {
    int switch_counter = 0;
    for (int i = 0; i < 20; i++) {
        int code = get_code(words[i], _hashSize);
        Node* new_el = new Node();
        new_el->value = words[i];
        if (_hashTable[code].first == NULL) {
            _hashTable[code].first = new_el;
            _hashTable[code].last = new_el;
        }
        else {
            Node* _current = _hashTable[code].last;
            _current->pNext = new_el;
            new_el->pPrev = _current;
            _hashTable[code].last = new_el;
        }
        _hashTable[code].el_count++;
        switch_counter += _hashTable[code].el_count;
    }
    findElement(randomWord, _hashSize, _hashTable);
    for (int j = 0; j < _hashSize; j++) {
        Node* current = _hashTable[j].first;
        Node* temp;
        while (current != NULL) {
            temp = current;
            current = current->pNext;
            delete temp;
        }
        _hashTable[j].first = NULL;
        _hashTable[j].last = NULL;
    }
    return switch_counter;
}

void testHash() {
    hashElement hashTable9[9];
    hashElement hashTable17[17];
    hashElement hashTable23[23];
    string words[20];
    int random, switch_counter_add = 0;
    bool b;

    for (int i = 0; i < 20; i++) {
        while (true) {
            b = false;
            random = rand() % 50;
            for (int j = 0; j <= i; j++) {
                if (keys[random] == words[j]) {
                    b = true;
                    break;
                }
            }
            if (!b) {
                break;
            }
        }
        words[i] = keys[random];
        cout << words[i] << " ";
        if (i % 5 == 0) {
            cout << endl;
        }
    }
    cout << endl;
    random = rand() % 20;
    cout << "Попробуйте найти слово " << words[random] << endl;
    cout << "Хеш-таблица размером 9: " << endl;
    switch_counter_add = addElementTest(hashTable9, words, 9, words[random]);
    cout << "Количество сравнений: " << switch_counter_add << endl;
    cout << "Количество сравнений для поиска: " << switch_counter << endl;
    cout << endl;
    cout << "Хеш-таблица размером 17: " << endl;
    switch_counter_add =

        addElementTest(hashTable17, words, 17, words[random]);
    cout << "Количество сравнений: " << switch_counter_add << endl;
    cout << "Количество сравнений для поиска: " << switch_counter << endl;
    cout << endl;
    cout << "Хеш-таблица размером 23: " << endl;
    switch_counter_add = addElementTest(hashTable23, words, 23, words[random]);
    cout << "Количество сравнений: " << switch_counter_add << endl;
    cout << "Количество сравнений для поиска: " << switch_counter << endl;
    cout << endl;

}

void menu() {

    int code = 0;
    string str;
    int choice;

    while (true) {
        cout << "1. Добавить новый элемент\n";
        cout << "2. Поиск элемента\n";
        cout << "3. Печать таблицы\n";
        cout << "4. Автоматическое тестирование\n";
        cout << "5. Удалить элемент\n";
        cout << "0. Выход\n";
        cout << "Введите номер команды: ";

        choice = console_work();

        if (choice == 1) {
            if (!isFull()) {
                cout << "Введите строку: " << endl;
                add_element(get_string());
            }
            else {
                cout << "Таблица полна" << endl;
            }

        }
        else if (choice == 2) {
            if (!isEmpty()) {
                cout << "Введите ключ: " << endl;
                str = get_string();
                int result = findElement(str, gl_size, hashTable);
                if (result == -1) {
                    cout << "Элемент не найден" << endl;

                }
            }
            else {
                cout << "Таблица пуста" << endl;
            }


        }
        else if (choice == 3) {
            if (!isEmpty()) {
                print_hash();
            }
            else {
                cout << "Таблица пуста" << endl;
            }
        }
        else if (choice == 4) {
            testHash();
        }
        else if (choice == 5) {
            if (!isEmpty()) {
                while (true) {
                    str = get_string();
                    if (findElement(str, gl_size, hashTable) != -1) {
                        break;
                    }
                    else {
                        cout << "Элемент не найден, попробуйте снова" << endl;
                    }
                }
                deleteElement(str);
            }
            else {
                cout << "Таблица пуста" << endl;
            }
        }
        else if (choice == 0) {
            clean();
            break;
        }
        else {
            cout << "\nОшибка ввода. Повторите команду\n";
        }
    }
}

int main()
{
    setlocale(LC_ALL,"RU");
    srand(time(NULL));
    menu();
    return 0;
}
