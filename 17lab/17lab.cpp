#include <iostream>


using namespace std;

int const gl_size = 10;
string hashTable[gl_size];
int hash_counter = 0;

string keys[] = { "COMPUTER", "MONITOR", "KEYBOARD", "MOUSE", "PRINTER", "LAPTOP",
    "DESKTOP", "SERVER", "ROUTER", "SWITCH", "CABLE", "SPEAKER",
    "HEADPHONE", "MICROPHONE", "CAMERA", "PHONE", "NOTEBOOK", "TABLET",
    "CHARGER", "BATTERY", "LED", "LCD", "SSD", "HARD DRIVE", "MEMORY",
    "PROCESSOR", "GRAPHICS", "FAN", "COOLER", "MOTHERBOARD" };

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
    code = code % _size;
    return code;
}

string get_string() {
    string str;
    cin >> str;
    return str;
}

bool key_find(string _key) {
    bool a = false;
    for (int i = 0; i < 30; i++) {
        if (_key == keys[i]) {
            a = true;
            break;
        }
    }
    return a;
}

int findElement(string _str, int _hashSize, string _hashTable[]) {
    int code = get_code(_str, _hashSize);
    int switch_counter = 0;
    for (int i = 0; i < _hashSize; i++) {
        switch_counter++;
        if (_hashTable[code] == "") {
            return -1;
        }
        else if (_hashTable[code] == _str) {
            cout << "Было сравнений для нахождения: " << switch_counter << endl;
            return code;
        }
        code = (code + 1) % _hashSize;
    }
}



void print_hash() {
    for (int i = 0; i < gl_size; i++) {
        cout << i << ") " << hashTable[i] << endl;
    }
}

void add_element(string _str) {
    int code = 0;
    int switch_counter = 0;

    code = get_code(_str, gl_size);
    for (int i = 0; i < gl_size; i++) {
        if (hashTable[code] == "") {
            hashTable[code] = _str;
            hash_counter++;
            cout << "Элемент был добавлен в индекс " << code << endl;
            break;
        }
        else if (hashTable[code] == _str) {
            cout << "Элемент уже добавлен" << endl;
            return;
        }
        code = (code + 1) % gl_size;
        switch_counter++;
    }
    cout << "Было сравнений для добавления: " << switch_counter << endl;
}

void deleteElement() {
    int code = 0;
    int switch_counter = 0;
    cout << "Введите ключ, который хотите удалить: " << endl;
    string _str = get_string();

    code = get_code(_str, gl_size);
    for (int i = 0; i < gl_size; i++) {
        if (hashTable[code] == _str) {
            hashTable[code] = "";
            hash_counter--;
            cout << "Элемент " << _str << " был удален" << endl;
            break;
        }
        else if (i == gl_size - 1) {
            cout << "Элемент не был найден" << endl;
        }
        code = (code + 1) % gl_size;
        switch_counter++;
    }
    cout << "Было сравнений для удаления: " << switch_counter << endl;
}

int addElementTest(string _hashTable[], string words[], int _hashSize, string randomWord) {
    int switch_counter = 0;
    for (int i = 0; i < 10; i++) {
        int code = get_code(words[i], _hashSize);
        for (int j = 0; j < _hashSize; j++) {
            switch_counter++;
            if (_hashTable[code] == "") {
                _hashTable[code] = words[i];
                break;
            }
            code = (code + 1) % _hashSize;
        }
    }
    findElement(randomWord, _hashSize, _hashTable);
    for (int i = 0; i < _hashSize; i++) {
        _hashTable[i] = "";
    }
    return switch_counter;
}

void testHash() {
    string hashTable11[11];
    string hashTable13[13];
    string hashTable17[17];
    string words[10];
    int random, switch_counter = 0;
    bool b;

    for (int i = 0; i < 10; i++) {
        while (true) {
            b = false;
            random = rand() % 30;
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
    }
    cout << endl;
    random = rand() % 10;
    cout << "Попытка найти слово " << words[random] << endl;
    cout << "Хэш-таблица размером 11: " << endl;
    switch_counter = addElementTest(hashTable11, words, 11, words[random]);
    cout << "Количество сравнений: " << switch_counter << endl;
    cout << endl;
    cout << "Хэш-таблица размером 13: " << endl;
    switch_counter = addElementTest(hashTable13, words, 13, words[random]);
    cout << "Количество сравнений: " << switch_counter << endl;
    cout << endl;
    cout << "Хэш-таблица размером 17: " << endl;
    switch_counter = addElementTest(hashTable17, words, 17, words[random]);
    cout << "Количество сравнений: " << switch_counter << endl;
    cout << endl;
}

void menu() {

    int code = 0;
    string str;
    int choice;


    for (int i = 0; i < gl_size; i++) {
        hashTable[i] = "";
    }

    while (true) {
        cout << "List of keys: COMPUTER, MONITOR, KEYBOARD, MOUSE, PRINTER, LAPTOP, DESKTOP, SERVER, ROUTER, SWITCH,\n CABLE, SPEAKER, HEADPHONE, MICROPHONE, CAMERA, PHONE, NOTEBOOK, TABLET, CHARGER, BATTERY,\n LED, LCD, SSD, HARD DRIVE, MEMORY, PROCESSOR, GRAPHICS, FAN, COOLER, MOTHERBOARD " << endl;
        cout << "\nВведите номер команды:\n";
        cout << "1. Добавить новый элемент\n";
        cout << "2. Поиск элемента\n";
        cout << "3. Печать таблицы\n";
        cout << "4. Автоматическое тестирование\n";
        cout << "5. Удалить элемент\n";
        cout << "0. Выйти\n";
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
                else {
                    cout << "Элемент найден на позиции " << result << endl;
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
                deleteElement();
            }
            else {
                cout << "Таблица пуста" << endl;
            }
        }
        else if (choice == 0) {
            break;
        }
        else {
            cout << "\nОшибка ввода. Повторите команду\n";
        }
    }
}

int main()
{
    setlocale(LC_ALL, "RU");
    srand(time(NULL));
    menu();
    return 0;
}