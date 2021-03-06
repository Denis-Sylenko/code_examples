#include "pch.h"
#include <iostream>
#include<memory>
#include<vector>

using namespace std;

template <typename T>
T reverse(T array, int size) {
	for (int i = 0; i < size; i++) {
		array[i] *= -1;
	}
	return array;
}

template<typename T> 
void fillArray(const T& array, int size) {
	for (int i = 0; i < size; i++) {
		cin >> array[i];
	}
}

template <typename T> 
void printArray(const T& array, int size) {
	cout << "Array: " << endl;
	for (int i = 0; i < size; i++) {
		cout << array[i] << " ";
	}
	cout << endl;
}

template <typename T> 
void printVector(const vector<T >& v) {
	cout << "Vector: " << endl;
	for (const auto& a : v) {
		cout << *a << " ";
	}
	cout << endl;
}

int main()
{
	int size, command;
	cout << "Input arrays size: ";
	cin >> size;

	//Работа с массивами

	unique_ptr<int[]> unique_ptr_array = make_unique<int[]>(size);
	shared_ptr<int[]> shared_ptr_array(new int[size], [](int *obj) {delete[]obj; });

	cout << "Enter 1 to fill arrays by yourself or 2 to generate data by random: ";
	cin >> command;
	switch (command)
	{
	case 1:
		cout << "Enter numbers to both arrays";
		fillArray(unique_ptr_array, size);
		fillArray(shared_ptr_array, size);
		break;
	case 2:
		for (int i = 0; i < size; i++) {
			unique_ptr_array[i] = rand() % 10; // Элементы будут всегда одинаовыми, но для примера достаточно наглядно
			shared_ptr_array[i] = rand() % 100;
		}
		break;
	default:
		cout << "Command is not in range";
		return 0;
	}

	printArray(unique_ptr_array, size);

	//Различные варианты передачи unique_ptr в функцию

	unique_ptr_array = reverse(move(unique_ptr_array), size);
	printArray(unique_ptr_array, size);


    printArray(shared_ptr_array, size);
    reverse(shared_ptr_array, size);
    printArray(shared_ptr_array, size);

	//Пример работы с контейнерами

	vector<unique_ptr<int>> unique_vector;
	unique_vector.push_back(make_unique<int>(10));
	unique_vector.push_back(make_unique<int>(15));
	printVector(unique_vector);
	unique_vector.pop_back();
	cout << "pop_back: " << endl;
	printVector(unique_vector);

	vector<shared_ptr<int>> shared_vector;
	shared_vector.push_back(make_shared<int>(20));
	shared_vector.push_back(make_shared<int>(30));
	printVector(shared_vector);
	shared_vector.pop_back();
	cout << "pop_back: " << endl;
	printVector(shared_vector);
	return 0;
}