#include "pch.h" //Для Visual Studio
#include <iostream>
#include"Vector.h"

template <typename T>
class CustomAllocator : public std::allocator<T>
{
private:
	using Base = std::allocator<T>;

public:
	T* allocate(size_t count)
	{
		std::cout << ">> Allocating " << count << " elements" << std::endl;
		return Base::allocate(count);
	}

	T* allocate(size_t count, const void* p)
	{
		std::cout << ">> Allocating " << count << " elements" << std::endl;
		return Base::allocate(count, p);
	}

	void deallocate(T* p, size_t count)
	{
		if (p != nullptr)
		{
			std::cout << ">> Deallocating " << count << " elements" << std::endl;
			Base::deallocate(p, count);
		}
	}
};

int main()
{
	MyLib::Vector<int> vec = {1,2,3,4,5,6,7};

	vec.pop_back();

	vec.push_back(7);

	vec.reserve(2222);

	MyLib::Vector<int> vec_2(vec);

	MyLib::Vector<int> vec_3(std::move(vec));

	vec_2 = std::move(vec_3);

	vec = vec_2;

	std::cout << "Element [3]: " << vec_2[3] << std::endl;

	vec.resize(100);

	vec.resize(3);

	std::cout << "Data: " << *(vec.data()) << std::endl;
	
	std::cout << "Does vector empty? : " << std::boolalpha << vec.empty() << std::endl;

	MyLib::Vector<int, CustomAllocator> custom_alloc_vector;

	custom_alloc_vector.push_back(10);

	MyLib::Vector<int, CustomAllocator> custom_alloc_vector_2 = custom_alloc_vector;
	
	custom_alloc_vector.resize(1300);

    return 0; 
}