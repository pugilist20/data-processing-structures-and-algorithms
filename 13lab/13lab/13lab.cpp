#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

int* a = NULL;
int compares = 0, changes = 0;
int num = 0;

int check() {
    int a;
    while (!(cin >> a) || (cin.peek() != '\n'))
    {
        cin.clear();
        while (cin.get() != '\n');
        cout << "\n Ошибка ввода. Повторите попытку: ";
    }
    return a;
}

void bubble_sort(int arr[], int size_arr) {
	int temp;
	int changes = 0;
	int compares = 0;
	for (int i = 0; i < size_arr; i++) {
		for (int j = 1; j < (size_arr - i); j++) {
			compares++;
			if (arr[j - 1] > arr[j]) {
				changes++;
				temp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = temp;
			}
		}
	}
	cout << "Результат сортировки пузырьком:" << endl;
	for (int i = 0; i < size_arr; i++) {
		cout << arr[i] << " ";
	}
	cout << "\n Количество сравнений: " << compares << ", Количество пересылок: " << changes << "\n";
}

void sort_choice(int arr[], int size_arr) {
	int temp;
	int changes = 0;
	int compares = 0;
	for (int i = 0; i < (size_arr - 1); i++) {
		int min_index = i;
		for (int j = i + 1; j < size_arr; j++) {
			compares++;
			if (arr[j] < arr[min_index]) {
				min_index = j;
			}
		}
		if (i != min_index) {
			changes++;
			temp = arr[i];
			arr[i] = arr[min_index];
			arr[min_index] = temp;
		}
	}
	cout << "Результат сортировки выбором:" << endl;
	for (int i = 0; i < size_arr; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
	cout << "\n Количество сравнений: " << compares << ", Количество пересылок: " << changes << "\n";
}

void sort_insert(int arr[], int size_arr) {
	int j;
	int insert_el;
	int changes = 0;
	int compares = 0;
	for (int i = 1; i < size_arr; i++) {
		int j = i;
		changes++;
		insert_el = arr[i];
		while (j > 0) {
			compares++;
			if (arr[j - 1] <= insert_el) {
				changes++;
				arr[j] = insert_el;
				break;
			}
			changes++;
			arr[j] = arr[j - 1];
			j--;
		}
		if (j == 0) {
			changes++;
			arr[j] = insert_el;
		}
	}
	cout << "Результат сортировки вставкой:" << endl;
	for (int i = 0; i < size_arr; i++) {
		cout << arr[i] << " ";
	}
	cout << "\n Количество сравнений: " << compares << ", Количество пересылок: " << changes/3 << "\n";
}


int main() {
	setlocale(LC_ALL, "RU");
	srand(time(NULL));
	int command = 0;
	int random;
	int size_arr = 0;
	int* arr;
	int* temp;
	cout << "Введите размер массива: " << endl;
	size_arr = check();
	arr = new int[size_arr];
	temp = new int[size_arr];
	bool stop = true;

	for (int i = 0; i < size_arr; i++) {
		random = rand() % (size_arr + 10);
		arr[i] = random;
		temp[i] = random;
	}
	cout << "Массив создан!" << endl;
	while (stop) {
		cout << "Выберите команду:" << endl;
		cout << "1) Показать исходный массив" << endl << "2) Сортировка пузырьком" << endl << "3) Сортировка выбором" << endl << "4) Сортировка вставкой" << endl<<"5) Сортировка тремя методами"<<endl << "6) Выход" << endl;
		cout << "Команда:" << endl;
		cout << "> ";
		command = check();
		switch (command) {
		case 1: {
			for (int i = 0; i < size_arr; i++) {
				cout << temp[i] << " ";
			}
			cout << endl;
			break;
		}
		case 2: {
			bubble_sort(temp, size_arr);
			for (int i = 0; i < size_arr; i++) {
				temp[i] = arr[i];
			}
			break;
		}
		case 3: {
			sort_choice(temp, size_arr);
			for (int i = 0; i < size_arr; i++) {
				temp[i] = arr[i];
			}
			break;
		}
		case 4: {
			sort_insert(temp, size_arr);
			for (int i = 0; i < size_arr; i++) {
				temp[i] = arr[i];
			}
			break;
		}
		case 5: {
			bubble_sort(temp, size_arr);
			for (int i = 0; i < size_arr; i++) {
				temp[i] = arr[i];
			}
			cout << endl;
			sort_choice(temp, size_arr);
			for (int i = 0; i < size_arr; i++) {
				temp[i] = arr[i];
			}
			cout << endl;
			sort_insert(temp, size_arr);
			for (int i = 0; i < size_arr; i++) {
				temp[i] = arr[i];
			}
			cout << endl;
			break;
		}
		case 6: {
			cout << "Программа завершила работу" << endl;
			delete[] arr;
			delete[] temp;
			break;
			break;
		}
		default: {
			cout << "Неизвестная команда" << endl;
		}
		}
	}
	return 0;
}
