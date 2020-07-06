//////////////////////////////////Code with mistakes///////////////////////////////////////


#include <iostream>
#include <vector>
#include <memory>

template <typename T>
class MyVector {
public:
	MyVector() {
		my_vector = std::make_shared<std::vector<std::pair<T, std::string>>>();
	};
	MyVector(const MyVector& other) : my_vector(other.my_vector) {};
	
	//We use smart pointer as field, so we can leave default destructor for our class

	void push_back(const T& object, const std::string& name) {
		copy();
		my_vector->push_back({ object, name });
	};

	std::pair<const T&, const std::string&> operator[](size_t index) const {
		if (index >= my_vector->size()) { throw std::out_of_range("Index is out of range!"); }
		return (*my_vector)[index];
	};

	std::pair< T&, std::string&> operator[](size_t index)  {
		if (index >= my_vector->size()) { throw std::out_of_range("Index is out of range!"); }
		return { (*my_vector)[index].first, (*my_vector)[index].second };
	};

	const T& operator[](const std::string& name) const {
		for (auto a : *my_vector) {
			if (a.second == name) { return a.first; }
		}
		throw std::invalid_argument("There is not such element in the vector!");
	};
	
	 T& operator[](const std::string& name) {
		 for (size_t i = 0; i < my_vector->size(); ++i) {
			if ((*my_vector)[i].second == name) { return (*my_vector)[i].first; }
		}
		throw std::invalid_argument("There is not such element in the vector!");
	};

	 typename std::vector<std::pair<T, std::string>>::iterator begin() { return my_vector->begin(); };
	 typename std::vector<std::pair<T, std::string>>::const_iterator cbegin() const { return my_vector->cbegin(); };
	 typename std::vector<std::pair<T, std::string>>::iterator end() { return my_vector->end(); };
	 typename std::vector<std::pair<T, std::string>>::const_iterator cend() { return my_vector->cend(); };

	 int size() { return my_vector->size(); };
	 bool empty() { return my_vector->empty(); };
	 void clear() {	my_vector->clear(); };
	 void reverse(size_t new_cap) { return my_vector->reserve(new_cap); };

private:
	void copy() {//For CoW idiom
		if (my_vector.use_count() == 1) { return;}
		my_vector = std::make_shared<std::vector<std::pair<T, std::string>>>(*my_vector);
	};
	std::shared_ptr<std::vector<std::pair<T, std::string>>> my_vector;
};




//////////////////////////////////Correct code///////////////////////////////////////

#include <iostream>
#include<vector>

template <typename T>
class MyVector : public std::vector<T> //Do not inherit from the vector class, as it is not intended to be basic
{
public:
	MyVector()
	{
		m_ref_ptr = new size_t(1);					//Incorrect initialization order
		m_names = new std::vector<std::string>();   //If this new throws an exception - object MyVector will be not created, accordingly, the destructor will not be called for it; the memory has already been allocated by m_ref_ptr - memory leak
	}

	MyVector(const MyVector& other)
		: std::vector<T>(other),		
		m_ref_ptr(other.m_ref_ptr),	//Incorrect initialization order
		m_names(other.m_names)
	{
		(*m_ref_ptr)++; // It's more effective to use prefix increment, not to create an extra temporary object 
	}

	~MyVector() 
	{
		if (--*m_ref_ptr == 0)
		{
			delete m_ref_ptr;
			delete m_names;
		}
	}

	void push_back(const T& obj, const std::string& name)
	{
		copy_names();

		std::vector<T>::push_back(obj);
		m_names->push_back(name);
	}

	std::pair<const T&, const std::string&> operator[](int index) const
	{
		if (index >= std::vector<T>::size())
		{
			throw new std::out_of_range("Index is out of range"); //We should throw exeptions by value
		}

		return std::pair<const T&, const std::string&>(std::vector<T>::operator[](index), (*m_names)[index]);
	}

	const T& operator[](const std::string& name) const
	{
		std::vector<std::string>::const_iterator iter = std::find(m_names->begin(), m_names->end(), name);
		if (iter == m_names->end())
		{
			throw new std::invalid_argument(name + " is not found in the MyVector"); //We should throw exeptions by value
		}

		return std::vector<T>::operator[](iter - m_names->begin());
	}

private:
	void copy_names()
	{
		if (*m_ref_ptr == 1)
		{
			return;
		}

		size_t* temp_ref_ptr = new size_t(1); // An extra temporary object is created
		std::vector<std::string>* temp_names = new std::vector<std::string>(*m_names);// An extra temporary object is created

		(*m_ref_ptr)--;// It's more effective to use prefix increment, not to create an extra temporary object 
		m_ref_ptr = temp_ref_ptr;
		m_names = temp_names;
	}

private:
	// Use copy-on-write idiom for efficiency (not a premature optimization)
	std::vector<std::string>* m_names; //RAII ideom is not complied
	size_t* m_ref_ptr;//RAII idiom is not complied
};
