#pragma once

template <typename T>
class List {
private:
	class Node {
	public:

		Node(T new_data = T(), Node* new_pNext = nullptr) : data(new_data), pNext(new_pNext){}
		T data;
		Node* pNext;
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
	void push_back(const T& data);
	void addNode(short* location, const T& data);
	void pop_back();
	void pop_front();
	void push_front(const T& data);
	void insert(const T& data, int number);
	void removeAt(int number);
	void clear();
	T& operator[] (const int& index);
	List<T>& operator = (const List& list);
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
	std::cout << "List: " << std::endl;
	if (Size == 0) { std::cout << "Empty List" << std::endl; return; }
	while (true) {
		std::cout << tmp->data << " ";
		if (tmp->pNext == nullptr) { break; }
		else tmp = tmp->pNext;
	}
	std::cout << std::endl;
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
	if (head == nullptr) { std::cout << "Empty List" << std::endl; return; }
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
void List<T>::push_back(const T& data) {
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
void List<T>::addNode(short * location, const T & data)
{
	if (head == nullptr) {
		head = Node(location, data);
	}
}

template<typename T>
void List<T>::pop_front()
{
	if (Size == 0) {
		std::cout << "Empty List" << std::endl; return;
	}
	if (head != nullptr) {
		Node* tmp = head;
		head = head->pNext;
		delete tmp;
		Size--;
	}
}
template<typename T>
void List<T>::push_front(const T& data)
{
	head = new Node(data, head);
	Size++;
}
template<typename T>
void List<T>::insert(const T& data, int number)
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
	if (Size == 0) {
		std::cout << "Empty List" << std::endl; return;
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

template<typename T>
List<T>& List<T>::operator=(const List & list)
{
	clear();

	Node* tmp = list.head;
	while (true) {
		push_back(tmp->data);
		if (tmp->pNext == nullptr) { break; }
		else tmp = tmp->pNext;
	}
}


