#include "pch.h"
#include <iostream>

template <typename T>
class Queue {
private:
	class Node {
	public:
		Node(T new_data = T(), Node* new_prev = nullptr, Node* new_next = nullptr) : data(new_data), pPrev(new_prev), pNext(new_next) {}
		T data;
		Node* pPrev;
		Node* pNext;
	};
	Node* first;
	Node* last;
	size_t size;
public:
	Queue() :first(nullptr), last(nullptr),size(0) {}
	~Queue() {
		clear();
	}
	void push(const T& data) {		
		if (size == 0) {
			first = last = new Node(data, nullptr, nullptr);
		}
		else {
			Node* tmp = new Node(data, last, nullptr);
			last->pNext = tmp;
			last = tmp;
			tmp = nullptr;
		}
		++size;
	}

	Node* front() {
		if (size == 0) { std::cout << "Queue is empty!" << std::endl; return nullptr; }
		return first;
	}

	Node* back() {
		if (size == 0) { std::cout << "Queue is empty!" << std::endl; return nullptr; }
		return last;
	}

	int getSize() {
		return size;
	}

	void pop() {
		if (size == 0) { std::cout << "Queue is empty!" << std::endl; return; }
		if (size == 1) {
			delete first; 
			--size;
			return;
		}
		Node* tmp = first;
		first = first->pNext;
		delete tmp;
		first->pPrev = nullptr;
		--size;
	}

	void PrintQueue() {
		if (size == 0) { std::cout << "Queue is empty!" << std::endl; return; }
		Node* tmp = last;
		while (tmp != nullptr) {
			std::cout << tmp->data << " ";
			tmp = tmp->pPrev;
		}
		std::cout << std::endl;
	}

	bool empty() {
		return size == 0;
	}

	void clear() {
		if (size == 0) { std::cout << "Queue is empty!" << std::endl; return; }
		while (size > 0) {
			pop();
		}
	}

	void ChangeLastAndFirst() {
		if (size == 0) { std::cout << "Queue is empty!" << std::endl; return; }
		std::swap(last->data, first->data);
	}

	void swap(Queue& other) {
		if (size != other.getSize()) { std::cout << "Different sizes" << std::endl;  return; }
		Node* this_tmp = last;
		Node* other_tmp = other.back();
		while (this_tmp != nullptr) {
			std::swap(this_tmp->data, other_tmp->data);
			this_tmp = this_tmp->pPrev;
			other_tmp = other_tmp->pPrev;
		}
	}

	bool contain(const T& _data) {
		Node* tmp = last;
		while (tmp != nullptr) {
			if (tmp->data == _data) { return true; }
			tmp = tmp->pPrev;
		}
		return false;
	};

	void reverse() {
		if (size == 0) { std::cout << "Stack is empty!" << std::endl; return; }
		Queue<T> new_queue;
		Node* tmp = last;
		while (tmp != nullptr) {
			new_queue.push(tmp->data);
			tmp = tmp->pPrev;
		}
		new_queue.swap(*this);
	}
};

int main()
{
	std::cout << "1 - getSize\n2 - empty\n3 - front\n4 - clear\n5 - push\n6 - pop\n7 - contain\n8 - reverse\n9 - ChangeLastAndFirst\n10 - Print Queue\n11 - Back\n12 - Exit" << std::endl;
	int n, tmp = 0;
	bool exit = false;
	Queue<int> queue;
	while (!exit) {
		std::cout << "Enter command: ";
		std::cin >> n;
		switch (n)
		{
		case 1:
			std::cout << "Queue size: " << queue.getSize() << std::endl;
			break;
		case 2:
			std::cout << "Queue is empty? " << std::boolalpha << queue.empty() << std::endl;
			break;
		case 3:
			if (queue.front() != nullptr) {
				std::cout << "Front element: " << queue.front()->data << std::endl;
			}
			break;
		case 4:
			queue.clear();
			break;
		case 5:
			std::cout << "Enter data: ";
			std::cin >> tmp;
			queue.push(tmp);
			break;
		case 6:
			queue.pop();
			break;
		case 7:
			std::cout << "Enter data: ";
			std::cin >> tmp;
			std::cout << "Does queue contain? " << std::boolalpha << queue.contain(tmp) << std::endl;
			break;
		case 8:
			queue.reverse();
			break;
		case 9:
			queue.ChangeLastAndFirst();
			break;
		case 10:
			queue.PrintQueue();
			break;
		case 11:
			if (queue.back() != nullptr) {
				std::cout << "Back element: " << queue.back()->data << std::endl;
			}
			break;
		case 12:
			exit = true;
			continue;
		default:
			std::cout << "Not in range!" << std::endl;
			break;
		}
	}
	return 0;
};