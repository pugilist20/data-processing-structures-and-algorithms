#include <iostream>

using namespace std;

string* arr = NULL;
int num = 10;
string keys[] = { "START", "STOP", "END", "RETURN", "GET", "STRING", "IF", "ELSE", "THIS", "PRIVATE" };

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

string get_string() {
    string str;
    cin >> str;
    return str;
}

bool key_find(string _key) {
    bool a = false;
    for (int i = 0; i < num; i++) {
        if (_key == keys[i]) {
            a = true;
            break;
        }
    }
    return a;
}

int get_code(string _str) {
    int code = 0;
    for (int i = 0; i < _str.length(); i++) {
        code += (int)_str[i];
    }
    cout << "Код ключа " << code << endl;
    code = code % 10;
    cout << "Индекс элемента " << code << endl;
    return code;
}

void print_arr(int* _arr) {
    for (int i = 0; i < num; i++) {
        cout << _arr[i] << " ";
    }
    cout << endl;
}

bool add_element(string _str) {
    int code = 0;
    if (key_find(_str)) {
        code = get_code(_str);
        if (arr[code] != _str) {
            arr[code] = _str;
            return true;
        }
        else {
            cout << "Элемент уже добавлен" << endl;
        }
    }
    else {
        cout << "Этот тип ключа невозможен" << endl;
    }
    return false;
}

void menu() {
    int k = 0;
    int code = 0;
    string str;
    int choice;
    arr = new string[num];

    for (int i = 0; i < num; i++) {
        arr[i] = "<Пусто>";
    }

    while (true) {
        cout << "Список ключей: START, STOP, END, RETURN, GET, STRING, IF, ELSE, THIS, PRIVATE " << endl;
        cout << "Количество непустых ячеек " << k << endl;
        cout << "\nВведите номер команды:\n";
        cout << "1. Добавить новый элемент\n";
        cout << "2. Поиск элемента\n";
        cout << "3. Печать таблицы\n";
        cout << "4. Автоматическое добавление\n";
        cout << "5. Удалить элемент\n";
        cout << "0. Выход\n";
        cout << "Введите номер команды: ";

        choice = console_work();

        if (choice == 1) {
            if (k < num) {
                cout << "Введите строку: " << endl;
                if (add_element(get_string())) {
                    k++;
                }
            }
            else {
                cout << "Таблица заполнена" << endl;
            }

        }
        else if (choice == 2) {
            cout << "Введите ключ: " << endl;
            str = get_string();
            code = get_code(str);
            if (str == arr[code]) {
                cout << "Элемент найден на позиции " << code << endl;
            }
            else {
                cout << "Элемент не найден" << endl;
            }

        }
        else if (choice == 3) {
            for (int i = 0; i < num; i++) {
                cout << i << ") " << arr[i] << endl;
            }
        }
        else if (choice == 4) {
            for (int i = 0; i < num; i++) {
                add_element(keys[i]);
            }
            k = num;
        }
        else if (choice == 5) {
            cout << "Введите ключ, который хотите удалить: " << endl;
            str = get_string();
            code = get_code(str);
            if (str == arr[code]) {
                arr[code] = "<Пусто>";
                cout << "Элемент удален" << endl;
                k--;
            }
            else {
                cout << "Элемент не найден" << endl;
            }

        }
        else if (choice == 0) {
            delete[] arr;
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
    menu();
    return 0;
}
