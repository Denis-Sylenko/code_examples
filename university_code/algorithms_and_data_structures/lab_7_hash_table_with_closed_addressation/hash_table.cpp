// Sylenko_7_With_List.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include<string>
#include<memory>
#include <openssl/sha.h>
#include "List.h"

struct hash_table_deleter {
	void operator()(pair<int, List<string>>* table) {
		delete[] table;
	}
};

class Hash_Table {
public:
	Hash_Table(size_t _capacity = 256, size_t _size = 0) : capacity(_capacity), size(_size) {
		table._Myptr() = new pair<int, List<string>>[capacity];
	};
	void insert(const string& data) {
		int index = hash(data);
		
		(table.get() + index)->second.push_back(data);
		if (++size == capacity) {
			capacity *= 2;
			unique_ptr<pair<int, List<string>>[], hash_table_deleter> tmp_table;
			tmp_table._Myptr() = new pair<int, List<string>>[capacity];
			copy(table.get(), (table.get() + capacity), tmp_table.get());
			table._Myptr() = tmp_table.get();
		}
	};
	List<string>* find(int key) {
		return &table[key].second;
	};
	void erase(int key) {
		table[key].second = List<string>();
	};

	void print_map() {
		for (size_t i = 0; i < capacity; ++i) {
			cout << i << " : "; (table.get() + i)->second.PrintList();
		}
	}
private:
	int hash(const string& data) {
		unique_ptr<unsigned char[]> input = make_unique<unsigned char[]>(data.length());
		for (int i = 0; i < data.length(); ++i) {
			input[i] = data[i];
		}
		unsigned char output[20];
		SHA1(input.get(), data.length(), output);
		return static_cast<int>(output[0]);
	}
	unique_ptr<pair<int, List<string>>[], hash_table_deleter> table;
	size_t capacity;
	size_t size;
};




int main()
{
	Hash_Table* table = new Hash_Table;
	std::cout << "1 - insert\n2 - find\n3 - erase\n4 - print_map\n5 - Exit" << std::endl;
	int n, tmp = 0;
	string info;
	List<string>* list_info;
	bool exit = false;
	while (!exit) {
		std::cout << "Enter command: ";
		std::cin >> n;
		switch (n)
		{
		case 1:
			std::cout << "Enter element: " << std::endl;
			cin >> info;
			table->insert(info);
			std::cout << "Success " << std::endl;
			break;
		case 2:
			std::cout << "Enter key: " << std::endl;
			cin >> tmp;
			list_info = table->find(tmp);
			std::cout << "Success " << std::endl;
			break;
		case 3:
			std::cout << "Enter key: " << std::endl;
			cin >> tmp;
			table->erase(tmp);
			std::cout << "Success " << std::endl;
			break;
		case 4:
			table->print_map();
			break;
		case 5:
			exit = true;
			continue;
		default:
			std::cout << "Not in range!" << std::endl;
			break;
		}
	}
	return 0;
}
