// priority_queue.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include"binary_heap.h"

int main()
{

	binary_heap bh;
	List<pair<int, string>> tmp_list;
	std::cout << "1 - Add element\n2 - Get Max\n3 - Print\n4 - Size\n5 - Get max without deletion\n6 - Increase value\n7 - Exit" << std::endl;
	int n, tmp = 0, tmp2 = 0;
	string tmp_string;
	bool exit = false;
	while (!exit) {
		std::cout << "Enter command: ";
		std::cin >> n;
		switch (n)
		{
		case 1:
			std::cout << "Enter priority and value: " << std::endl;
			cin >> tmp >> tmp_string;
			bh.add_to_heap(tmp,tmp_string);
			std::cout << "Success! " << std::endl;
			break;
		case 2:
			std::cout << "Priority: " << bh.get_max().first << "Value: " << bh.get_max().second<< endl;
			break;
		case 3:
			cout << "Binary heap" << endl;
			bh.print();
			break;
		case 4:
			std::cout << "Size of heap: " << bh.heap_count() << endl;
			break;
		case 5:
			std::cout << "Priority: " << bh.get_max_without_deletion().first << "Value: " << bh.get_max_without_deletion().second << endl;
			break;
		case 6:
			std::cout << "Enter old and new priority: " << std::endl;
			cin >> tmp >> tmp2;
			bh.increase_value(tmp, tmp2);
		case 7:
			exit = true;
			continue;
		default:
			std::cout << "Not in range!" << std::endl;
			break;
		}
	}
	return 0;
}
