#include "pch.h"
#include <iostream>

using namespace std;

template <typename T>
class List {
private:
	class Node {
	public:

		Node(T data = T(), Node* pNext = nullptr) {
			this->data = data;
			this->pNext = pNext;
		}
		Node* pNext;
		T data;
	};

	Node* head;
	int Size;
public:
	List();
	List(const List& list);
	~List();
	int GetSize() { return Size; }
	void PrintList();
	void Merge(List* second_list);
	void Sort();
	void push_back(T data);
	void pop_back();
	void pop_front();
	void push_front(T data);
	List<T>* GeneralElements(List<T>* rhs);
	void Move(int position, int count);
	void insert(T data, int number);
	void removeAt(int number);
	List<T>* removeEveryN(int number);
	void clear();
	T& operator[] (const int& index);
};

template <typename T>
List<T>::List() {
	head = nullptr;
	Size = 0;
}

template<typename T>
List<T>::List(const List<T>& list)
{
	Node* tmp = list.head;
	while (true) {
		push_back(tmp->data);
		if (tmp->pNext == nullptr) { break; }
		else tmp = tmp->pNext;
	}
}

template<typename T>
List<T>::~List()
{
	clear();
}

template<typename T>
void List<T>::PrintList()
{
	Node* tmp = head;
	cout << "List: " << endl;
	if (Size == 0) { cout << "Empty List" << endl; return; }
	while (true) {
		cout << tmp->data << " ";
		if (tmp->pNext == nullptr) { break; }
		else tmp = tmp->pNext;
	}
	cout << endl;
}


template<typename T>
void List<T>::Merge(List* second_list)
{
	if (head == nullptr) {
		head = second_list->head;
		Size += second_list->GetSize();
		return;
	}
	Size += second_list->Size;
	Node* tmp = head;
	while (tmp->pNext != nullptr) {
		tmp = tmp->pNext;
	}
	tmp->pNext = second_list->head;
	second_list->head = nullptr;
	second_list->Size = 0;
}

template<typename T>
void List<T>::Sort()
{
	if (head == nullptr) { cout << "Empty List" << endl; return; }
	Node* tmp = head;
	while (true) {
		if (tmp->pNext == nullptr) { break; }
		Node* next = tmp->pNext;
		while (true) {
			if (tmp->data > next->data) {
				swap(tmp->data, next->data);
			}
			if (next->pNext == nullptr) { break; };
			next = next->pNext;
		}
		tmp = tmp->pNext;
	}
}


template <typename T>
void List<T>::push_back(T data) {
	if (head == nullptr) {
		head = new Node(data);
	}
	else {
		Node* current = head;
		while (current->pNext != nullptr) {
			current = current->pNext;
		}
		current->pNext = new Node(data);
	}
	Size++;
}

template<typename T>
void List<T>::pop_front()
{
	if (Size == 0) {
		cout << "Empty List" << endl; return;
	}
	if (head != nullptr) {
		Node* tmp = head;
		head = head->pNext;
		delete tmp;
		Size--;
	}
}
template<typename T>
void List<T>::push_front(T data)
{
	head = new Node(data, head);
	Size++;
}
template<typename T>
List<T>* List<T>::GeneralElements(List<T>* _rhs)
{
	List<T>* list = new List();
	Node* lhs = head;
	while (true) {
		Node* rhs = _rhs->head;
		while (true) {
			if (lhs->data == rhs->data) {
				list->push_back(lhs->data);
			}
			if (rhs->pNext == nullptr) { break; }
			else rhs = rhs->pNext;
		}
		if (lhs->pNext == nullptr) { break; }
		else lhs = lhs->pNext;
	}
	return list;
}
template<typename T>
void List<T>::Move(int position, int count)
{
	if (position > Size) {
		return;
	}
	Node* tmp = head;
	for (int i = 0; i < position; i++) {
		tmp = tmp->pNext;
	}
	if ((position + count + 1) <= Size) {
		insert(tmp->data, position + count + 1);
	}
	else push_back(tmp->data);
	removeAt(position);
}
template<typename T>
void List<T>::insert(T data, int number)
{
	if (number >= Size) {
		push_back(data);
	}
	else {
		Node* previous = head;
		for (int i = 0; i < number; i++) {
			previous = previous->pNext;
		}
		previous->pNext = new Node(data, previous->pNext);
		Size++;
	}
}
template<typename T>
void List<T>::removeAt(int number)
{
	number--;
	if (Size == 0) {
		cout << "Empty List" << endl; return;
	}
	if (number == 0) {
		pop_front();
	}
	else {
		Node* previous = head;
		for (int i = 0; i < number - 1; i++) {
			previous = previous->pNext;
		}
		Node* toDelete = previous->pNext;
		previous->pNext = toDelete->pNext;
		delete toDelete;
		Size--;
	}


}
template<typename T>
List<T>* List<T>::removeEveryN(int number)
{
	List<T>* tmp = new List();
	if (Size == 0) {
		cout << "Empty List" << endl; return this;
	}
	int count = 1;
	Node* tmp_n = head;
	int init_number = number;
	while (true) {
		if (count % number != 0) {
			tmp->push_back(tmp_n->data);
		}
		count++;
		if (tmp_n->pNext != nullptr)tmp_n = tmp_n->pNext;
		else break;
	}
	return tmp;
}
template<typename T>
void List<T>::pop_back()
{
	removeAt(Size - 1);
}
template<typename T>
void List<T>::clear()
{
	while (Size) {
		pop_front();
	}
}
template<typename T>
T& List<T>::operator[](const int& number)
{
	int counter = 0;
	Node* current = head;
	while (current != nullptr) {
		if (number == counter) {
			return current->data;
		}
		current = current->pNext;
		counter++;
	}
}

int main()
{
	int command, count;
	int data, position, element, number, s_size;
	List<int> s_list;
	List<int> new_list;
	bool again = true;
	List<int> list;
	std::cout << "Commands: " << std::endl << "1 - Get Size\n2 - Print List\n3 - Merge\n4 - Sort\n5 - push_back\n6 - pop_back\n7 - pop_front\n8 - push_front\n9 - General Elements\n10 - Move\n11 - insert\n12 - removeAt\n13 - remove every N\n14 - clear\n15 - Exit" << std::endl;
	while (again) {

		std::cout << "Enter command: ";
		std::cin >> command;
		switch (command)
		{
		case 1:
			cout << "List size " << list.GetSize() << endl;;
			break;
		case 2:
			list.PrintList();
			break;
		case 3:
			cout << "Enter second List size and elements to merge: ";
			cin >> s_size;
			for (int i = 0; i < s_size; i++) {
				cin >> element;
				s_list.push_back(element);
			}
			list.Merge(&s_list);
			cout << "After merge: " << endl;
			list.PrintList();
			break;
		case 4:
			list.Sort();
			cout << "After sort: " << endl;
			list.PrintList();
			break;
		case 5:
			cout << "Enter Element: ";
			cin >> element;
			list.push_back(element);
			break;
		case 6:
			list.pop_back();
			break;
		case 7:
			list.pop_front();
			break;
		case 8:
			cout << "Enter Element: ";
			cin >> element;
			list.push_front(element);
			break;
		case 9:
			cout << "Enter second List size and elements to General Elements: ";
			cin >> s_size;
			for (int i = 0; i < s_size; i++) {
				int element;
				cin >> element;
				s_list.push_back(element);
			}
			new_list = *list.GeneralElements(&s_list);
			cout << "After Gen: " << endl;
			new_list.PrintList();
		case 10:
			cout << "Enter position and count: ";
			cin >> position >> count;
			list.Move(position, count);
			break;
		case 11:
			cout << "Enter data and position: ";
			cin >> data >> position;
			list.insert(data, position);
		case 12:
			cout << "Enter number: ";
			cin >> number;
			list.removeAt(number);
			break;
		case 13:
			cout << "Enter number: ";
			cin >> number;
			list = *list.removeEveryN(number);
			break;
		case 14:
			list.clear();
			break;
		case 15:
			again = false;
			continue;
			break;
		default:
			std::cout << "Command is not in range! " << std::endl;
			break;
		}
	}
	return 0;
}