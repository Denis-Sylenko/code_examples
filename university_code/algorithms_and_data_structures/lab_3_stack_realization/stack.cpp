#include "pch.h"
#include <iostream>

template <typename T>
class Stack {
private:
	class Node {
	public:
		Node(T new_data = T(), Node* new_prev = nullptr) : data(new_data), pPrev(new_prev) {}
		T data;
		Node* pPrev;
	};
	Node* top;
	size_t size;
public:
	Stack():top(nullptr), size(0) {}
	~Stack() {
		clear();
	}
	void push(const T& data) {
			top = new Node(data, top);
			++size;
	}

	Node* Top() {
		if (size == 0) { std::cout << "Stack is empty!" << std::endl; }
		return top;
	}

	int getSize() {
		return size;
	}

	void pop() {
		if (size == 0) { std::cout << "Stack is empty!" << std::endl; return; }
		Node* tmp = top;
		top = top->pPrev;
		delete tmp;
		size--;
	}
	
	void PrintStack() {
		if (size == 0) { std::cout << "Stack is empty!" << std::endl; return; }
		Node* tmp = top;
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
		if (size == 0) { std::cout << "Stack is empty!" << std::endl; return; }
		while (size > 0) {
			pop();
		}
	}

	void ChangeLastAndFirst() {
		if (size == 0) { std::cout << "Stack is empty!" << std::endl; return; }
		Node* tmp = top;
		while (tmp->pPrev != nullptr) {
			tmp = tmp->pPrev;
		}
		std::swap(tmp->data, top->data);
	}

	void swap(Stack& other) {
		if (size != other.getSize()) { std::cout << "Different sizes" << std::endl;  return; }
		Node* this_tmp = top;
		Node* other_tmp = other.Top();
		while (this_tmp != nullptr) {
			std::swap(this_tmp->data, other_tmp->data);
			this_tmp = this_tmp->pPrev;
			other_tmp = other_tmp->pPrev;
		}
	}

	bool contain(const T& _data) {
		Node* tmp = top;
		while (tmp != nullptr) {
			if (tmp->data == _data) { return true; }
			tmp = tmp->pPrev;
		}
		return false;
	};

	void reverse() {
		if (size == 0) { std::cout << "Stack is empty!" << std::endl; return; }
		Stack<T> new_stack;
		Node* tmp = top;
		while (tmp != nullptr) {
			new_stack.push(tmp->data);
			tmp = tmp->pPrev;
		}
		new_stack.swap(*this);
	}
};

int main()
{
	std::cout << "1 - getSize\n2 - empty\n3 - top\n4 - clear\n5 - push\n6 - pop\n7 - contain\n8 - reverse\n9 - ChangeLastAndFirst\n10 - Print Stack\n11 - Exit" << std::endl;
	int n, tmp = 0;
	bool exit = false;
	Stack<int> stack;
	while (!exit) {
		std::cout << "Enter command: ";
		std::cin >> n;
		switch (n)
		{
		case 1:
			std::cout << "Stack size: " << stack.getSize() << std::endl;
			break;
		case 2:
			std::cout << "Stack is empty? " << std::boolalpha << stack.empty() << std::endl;
			break;
		case 3:
			if (stack.Top() != nullptr) {
				std::cout << "Top element: " << stack.Top()->data << std::endl;
			}
			break;
		case 4:
			stack.clear();
			break;
		case 5:
			std::cout << "Enter data: ";
			std::cin >> tmp;
			stack.push(tmp);
			break;
		case 6:
			stack.pop();
			break;
		case 7:
			std::cout << "Enter data: ";
			std::cin >> tmp;
			std::cout << "Does stack contain? " << std::boolalpha << stack.contain(tmp) << std::endl;
			break;
		case 8:
			stack.reverse();
			break;
		case 9:
			stack.ChangeLastAndFirst();
			break;
		case 10:
			stack.PrintStack();
			break;
		case 11:
			exit = true;
			continue;
		default:
			std::cout << "Not in range!" << std::endl;
			break;
		}
	}
	return 0;
};