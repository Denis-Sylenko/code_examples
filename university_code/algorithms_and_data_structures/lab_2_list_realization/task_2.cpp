#include "pch.h"
#include <iostream>
#include<string>

using namespace std;

template <typename T>
class List {
private:
	class Node {
	public:

		Node(T data = T(), Node *pNext = nullptr) {
			this->data = data;
			this->pNext = pNext;
		}
		Node *pNext;
		T data;
	};

	Node *head;
	int Size;
public:
	Node* GetElement(int number) {
		--number;
		int counter = 0;
		Node *current = head;
		while (true) {
			if (number == counter) {
				return current;
			}
			current = current->pNext;
			counter++;
		}
	};
	List() {
		head = nullptr;
		Size = 0;
	};
	List(const List& list) {
		Node* tmp = list.head;
		for (int i = 0; i < list.GetSize(); i++) {
			push_back(tmp->data);
			tmp = tmp->pNext;
		}
	};
	~List() {
		clear();
	};
	int GetSize() { return Size; }
	void PrintList() {
		Node* tmp = head;
		cout << "List: " << endl;
		if (Size == 0) { cout << "Empty List"; return; }
		for (int i = 0; i < Size; i++) {
			cout << tmp->data << " ";
			tmp = tmp->pNext;
		}
		cout << endl;
	};

	void remove_at(int index) {
		if (Size == 0) { return; }
		--index;
		if (index == 0) { pop_front(); return; }
		Node* tmp = head;
		for (int i = 0; i < (index - 1); ++i) {
			tmp = tmp->pNext;
		}
		Node* prev = tmp;
		tmp = tmp->pNext;
		prev->pNext = tmp->pNext;
		delete tmp;
		--Size;

	}

	void push_back(T data) {
		if (head == nullptr) {
			head = new Node(data);
			head->pNext = head;
		}
		else {
			Node *current = head;
			while (current->pNext != head) {
				current = current->pNext;
			}
			current->pNext = new Node(data, head);
		}
		Size++;
	};
	void pop_front() {
		if (head != nullptr) {
			Node *tmp = head;
			Node *tmp_head = head;
			while (tmp->pNext != head) { tmp = tmp->pNext; }
			head = head->pNext;
			tmp->pNext = head;
			delete tmp_head;
			Size--;
		}
	};
	void PrintWinners(List<T>& rhs, int win_number, int n, int t) {
		List<T> list;
		if (win_number > Size || win_number > rhs.GetSize()) { std::cout << "Too much winners" << std::endl; return; }
		int init_n = n, init_t = t;
		cout << "Our Winners!: " << endl;
		for (int i = 0; i < win_number; i++) {
			cout << GetElement(n)->data << " " << rhs.GetElement(t)->data << endl;
			remove_at(n);
			rhs.remove_at(t);
			n += init_n - 1;
			t += init_t - 1;
		}
	};
	void clear() {
		while (Size) {
			pop_front();
		}
	};
};

int main()
{
	int part_number, prize_number, win_number, n, t;
	List<string>* part_list = new List<string>;
		List<string>*	prize_list = new List<string>;
	cout << "Enter number of participants and list of them: " << endl;
	cin >> part_number;
	for (int i = 0; i < part_number; i++) {
		string user_string;
		cin >> user_string;
		part_list->push_back(user_string);
	}
	cout << "Enter number of prizes and list of them: " << endl;
	cin >> prize_number;
	for (int i = 0; i < prize_number; i++) {
		string user_string;
		cin >> user_string;
		prize_list->push_back(user_string);
	}
	cout << "Enter amount of winners, n and t: " << endl;
	cin >> win_number >> n >> t;
	part_list->PrintWinners(*prize_list, win_number, n, t);
	return 0;
}