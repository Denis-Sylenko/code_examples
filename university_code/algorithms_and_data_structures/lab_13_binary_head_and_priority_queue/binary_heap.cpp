// lab_13_sylenko.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "List.h"
using namespace std;

class binary_heap {
public:
	void add_to_heap(int value) {
		lst.push_back(value);
		int index_of_new_element = heap_count() - 1;
		int index_of_parent = (index_of_new_element - 1) / 2;

		while (index_of_new_element > 0 && lst[index_of_parent] < lst[index_of_new_element]) {
			int tmp = lst[index_of_new_element];
			lst[index_of_new_element] = lst[index_of_parent];
			lst[index_of_parent] = tmp;

			index_of_new_element = index_of_parent;
			index_of_parent = (index_of_new_element - 1) / 2;
		}
	}

	void modify(int i)
	{
		int left_child;
		int right_child;
		int largest_child;

		while (true)
		{
			left_child = 2 * i + 1;
			right_child = 2 * i + 2;
			largest_child = i;

			if (left_child < heap_count() && lst[left_child] > lst[largest_child])
			{
				largest_child = left_child;
			}

			if (right_child < heap_count() && lst[right_child] > lst[largest_child])
			{
				largest_child = right_child;
			}

			if (largest_child == i)
			{
				break;
			}

			int tmp = lst[i];
			lst[i] = lst[largest_child];
			lst[largest_child] = tmp;
			i = largest_child;
		}
	}

	int get_max() {
		if (heap_count() > 0) {
			int result = lst[0];
			lst[0] = lst[heap_count() - 1];
			lst.pop_back();
			return result;
		}
		return -99999999;
	}

	void heap_sort(List<int>& new_list) {
		build_heap(new_list, new_list.GetSize());
		for (int i = new_list.GetSize() - 1; i >= 0; --i) {
			new_list[i] = get_max();
			modify(0);
		}
	}

	void build_heap(List<int>& new_list, int size) {
		lst.clear();
		List<int> tmp;
		for (int i = 0; i < new_list.GetSize(); ++i) {
			lst.push_back(new_list[i]);
		}
		for (int i =  new_list.GetSize()/ 2; i >= 0; --i) {
			modify(i);
		}
	}

	void print() {
		for (int i = 0; i < heap_count(); ++i) {
			cout << "Priority: " << lst[i]<<endl;
		}
	}


	int heap_count() {
		return lst.GetSize();
	}
private:
	List<int> lst;
};

int main()
{
	binary_heap bh;
	List<int> tmp_list;
	std::cout << "1 - Add element\n2 - Get Max\n3 - Print\n4 - Size\n5 - sort\n6 - Exit" << std::endl;
	int n, tmp = 0, tmp2 = 0;
	bool exit = false;
	while (!exit) {
		std::cout << "Enter command: ";
		std::cin >> n;
		switch (n)
		{
		case 1:
			std::cout << "Enter element: " << std::endl;
			cin >> tmp;
			bh.add_to_heap(tmp);
			std::cout << "Success! " << std::endl;
			break;
		case 2:
			std::cout << "Max element: " << bh.get_max()<<endl;
			break;
		case 3:
			cout << "Binary heap" << endl;
			bh.print();
			break;
		case 4:
			std::cout << "Size of heap: " << bh.heap_count() << endl;
			break;
		case 5:
			std::cout << "Enter number of elements: ";
			std::cin >> tmp;
			for (int i = 0; i < tmp; ++i) {
				cin >> tmp2;
				tmp_list.push_back(tmp2);
			}
			bh.heap_sort(tmp_list);
			tmp_list.PrintList();
			break;
		case 6:
			exit = true;
			continue;
		default:
			std::cout << "Not in range!" << std::endl;
			break;
		}
	}
	return 0;
}
