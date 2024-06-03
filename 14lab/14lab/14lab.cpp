#include <iostream>
#include <string>
#include <windows.h>
#include <time.h>

using namespace std;

int quickSort_diff_count = 0;
int quickSort_change_count = 0;

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
	cout << "\n Количество сравнений: " << compares << ", Количество пересылок: " << changes / 3 << "\n";
}

void shell_sort(int arr[], int* steps, int steps_size, int size_arr) {
	int step;
	int change_counts = 0;
	int diff_counts = 0;
	for (int x = 0; x < steps_size; x++) {
		step = steps[x];
		for (int i = step; i < size_arr; i++) {
			int j = i;
			change_counts++;
			int insert_el = arr[i];
			while (j >= 0) {
				diff_counts++;
				if ((arr[j - step] <= insert_el) || (j == 0) || (j - step < 0)) {
					change_counts++;
					arr[j] = insert_el;
					break;
				}
				change_counts++;
				arr[j] = arr[j - step];
				j -= step;
			}
		}
	}
	cout << "Результат:" << endl;
	for (int i = 0; i < size_arr; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
	cout << "Количество перестановок: " << change_counts / 3 << endl;
	cout << "Количество сравнений: " << diff_counts << endl;
}

void pyramid_sort(int arr[], int size_arr) {
	size_arr++;
	int* pyramid = new int[size_arr];
	int temp, current, smallest;

	int change_count_for_build = 0;
	int change_count_for_rebuild = 0;
	int diff_count_for_build = 0;
	int diff_count_for_rebuild = 0;

	int pyramid_size = size_arr - 1;
	for (int i = 1; i < size_arr; i++) {
		current = i;

		change_count_for_build++;
		pyramid[i] = arr[i - 1];

		while (current > 1) {
			diff_count_for_build++;
			if (pyramid[current] < pyramid[current / 2]) {

				change_count_for_build += 3;
				temp = pyramid[current];
				pyramid[current] = pyramid[current / 2];
				pyramid[current / 2] = temp;

			}
			else {
				break;
			}
			current = current / 2;
		}
	}

	for (int i = 0; i < size_arr; i++) {
		change_count_for_build += 2;
		arr[i] = pyramid[1];
		pyramid[1] = pyramid[pyramid_size];

		pyramid_size -= 1;
		current = 1;
		while (current <= pyramid_size) {
			smallest = current;

			diff_count_for_rebuild++;
			if (current * 2 <= pyramid_size) {
				if ((pyramid[current] > pyramid[current * 2]) && (current * 2 <= pyramid_size)) {
					smallest = current * 2;
				}

				diff_count_for_rebuild++;
				if ((pyramid[smallest] > pyramid[current * 2 + 1]) && ((current * 2 + 1) <= pyramid_size)) {
					smallest = current * 2 + 1;
				}
			}
			if (smallest == current) {
				break;
			}
			else {

				change_count_for_rebuild += 3;
				temp = pyramid[current];
				pyramid[current] = pyramid[smallest];
				pyramid[smallest] = temp;

				current = smallest;
			}
		}
	}
	cout << "Результат:" << endl;
	for (int i = 0; i < size_arr; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
	cout << "---------------------" << endl;
	cout << "Общее количество перестановок: " << change_count_for_build / 3 + change_count_for_rebuild / 3 << endl;
	cout << "Общее количество сравнений: " << diff_count_for_build + diff_count_for_rebuild << endl;

	delete[] pyramid;
}

void quick_sort(int arr[], int _i, int size_arr) {
	int mid = arr[(size_arr + _i) / 2];
	int i = _i;
	int j = size_arr;
	while (i <= j) {
		while (arr[i] < mid) {
			quickSort_diff_count++;
			i++;
		}
		while (arr[j] > mid) {
			quickSort_diff_count++;
			j--;
		}
		if (i <= j) {
			quickSort_change_count++;
			int temp = arr[j];
			arr[j] = arr[i];
			arr[i] = temp;
			i++;
			j--;
		}
	}
	if (_i <= j) {
		quick_sort(arr, _i, j);
	}
	if (i <= size_arr) {
		quick_sort(arr, i, size_arr);
	}
}

int main() {
	setlocale(LC_ALL, "RU");
	srand(time(NULL));
	int command = 0;
	int step_count, step;
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
			cout << "---------------------" << endl;
			cout << "Выберите команду:" << endl;
			cout << "1) Показать исходный массив" << endl << "2) Сортировка пузырьком" << endl << "3) Сортировка выбором" << endl << "4) Сортировка вставкой" << endl << "5) Сортировка тремя методами" << endl<< "6) Сортировка Шелла" << endl << "7) Пирамидная сортировка" << endl << "8) Быстрая сортировка" << endl << "9) Выход" << endl;
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
			cout << "Введите количество шагов:" << endl;
			step_count = check();
			int* steps = new int[step_count];
			cout << "Введите величины шагов в убывающем порядке" << endl;
			for (int i = 0; i < step_count; i++) {
				if (i == step_count - 1) {
					cout << "Последний шаг обязательно должен быть равен 1, поэтому ставим его по умолчанию" << endl;
					steps[i] = 1;
					break;
				}
				cout << "Введите значение шага:" << endl;
				cout << "Минимальная величина, которая доступна: " << step_count - i << endl;
				while (true) {
					cout << "> ";
						step = check();
						if (step >= size_arr) {
							cout << "Шаг не может быть больше длины массива" << endl;
							continue;
						}
						if (step < step_count - i) {
							cout << "Пока такая величина не может быть принята" << endl;
							continue;
						}
						if (i != 0) {
							if (step >= steps[i - 1]) {
								cout << "Шаги должны быть в убывающем порядке" << endl;
								continue;
							}
						}
						break;
					cout << "Получено не натуральное число" << endl;
				}
				steps[i] = step;
			}

			shell_sort(temp, steps, step_count, size_arr);
			for (int i = 0; i < size_arr; i++) {
				temp[i] = arr[i];
			}
			delete[] steps;
			break;
		}
		case 7: {
			pyramid_sort(temp, size_arr);
			for (int i = 0; i < size_arr; i++) {
				temp[i] = arr[i];
			}
			break;
		}
		case 8: {
			quickSort_change_count = 0;
			quickSort_diff_count = 0;

			quick_sort(temp, 0, size_arr - 1);
			cout << "Результат: " << endl;
			for (int i = 0; i < size_arr; i++) {
				cout << temp[i] << " ";
				temp[i] = arr[i];
			}
			cout << endl;
			cout << "Количество перестановок: " << quickSort_change_count << endl;
			cout << "Количество сравнений: " << quickSort_diff_count << endl;
			break;
		}
		case 9: {
			cout << "Программа завершила работу" << endl;
			stop = false;
			delete[] arr;
			delete[] temp;
			break;
		}
		default: {
			cout << "Неизвестная команда" << endl;
			break;
		}
		}
	}
	return 0;
}
