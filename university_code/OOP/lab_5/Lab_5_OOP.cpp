#include "pch.h"
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

template <typename T>
class custom_vector {
private:
	class reload_iterator : public std::vector<T>::iterator {
	public:
		reload_iterator(typename std::vector<T>::iterator iter, typename std::vector<T>::iterator begin_iter, 
						typename std::vector<T>::iterator end_iter) : standart_iterator(iter), begin_iterator(begin_iter), end_iterator(end_iter){
		}

		reload_iterator operator+ (const int& rhs) {
			if ((end_iterator - standart_iterator > rhs) && (begin_iterator - standart_iterator <= rhs)) {
				return reload_iterator(standart_iterator + rhs, begin_iterator, end_iterator);
			}
			else throw out_of_range("Index out of range");
		}

		typename std::vector<T>::iterator get_standart() const {
			return standart_iterator;
		}

		T& operator*() {
			if (standart_iterator!=end_iterator)
			return *standart_iterator;
			else  throw out_of_range("Index out of range");
		}
	private:
		typename std::vector<T>::iterator standart_iterator;
		typename std::vector<T>::iterator begin_iterator;
		typename std::vector<T>::iterator end_iterator;
	};

public:
	custom_vector() {
		base_vector = unique_ptr<vector<T>>(new vector<T>());
	}

	custom_vector(const custom_vector& other) {
		base_vector = unique_ptr<vector<T>>(new vector<T>(other.get_base_vector()));
	}

	custom_vector& operator= (const custom_vector& other) {
		clear();
		base_vector = unique_ptr<vector<T>>(new vector<T>(other.get_base_vector()));
		return *this;
	}
	
	vector<T>& get_base_vector() const {
		return *base_vector.get();
	}

	reload_iterator erase(const reload_iterator& position) {
		if (position.get_standart() != base_vector.get()->end()) {
			return (base_vector.get()->erase(position.get_standart()), begin(), end());
		}
		else {
			throw out_of_range("Index out of range");
		}

	}

	reload_iterator insert(reload_iterator position, const T& value) {
			return (base_vector.get()->insert(position.get_standart(), value), begin(), end());
	}

	T& operator[](const int& position) {
		return *(begin() + position);
	}

	void pop_back() {
		if (!empty()) {
			base_vector.get()->pop_back();
		}
		else throw out_of_range("Empty vector");
	}

	void push_back(const T& value) {
		base_vector.get()->push_back(value);
	};

	reload_iterator begin() {
		return reload_iterator(base_vector.get()->begin(), base_vector.get()->begin(), base_vector.get()->end());
	}

	reload_iterator end() {
		return reload_iterator(base_vector.get()->end(), base_vector.get()->begin(), base_vector.get()->end());
	}

	bool empty() const {
		return base_vector.get()->empty();
	}

	bool size() const {
		return base_vector.get()->size();
	}

	bool max_size() const {
		return base_vector.get()->max_size();
	}

	void reserve(size_t size) {
		base_vector.get()->reserve(size);
	}

	void clear() {
		base_vector.get()->clear();
	}
	
	void shrink_to_fit() {
		base_vector.get()->shrink_to_fit();
	}

	size_t capacity() const {
		return base_vector.get()->capacity();
	}

	void resize(size_t count) {
		base_vector.get()->resize(count);
	};

	void swap(custom_vector& other) {
		base_vector.get()->swap(other.get_base_vector());
	};
private:
	unique_ptr<vector<T>> base_vector;
};


int main()
{
	custom_vector<int> b;
	b.push_back(5);
	custom_vector<int> c(b);
	try {
		cout << *c.end();
	}
	catch (out_of_range e) {
		cout << e.what();
	}
}
