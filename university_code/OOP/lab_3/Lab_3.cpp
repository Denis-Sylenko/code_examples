#include "pch.h"
#include <iostream>
#include<List.h>

std::ostream& operator << (std::ostream& out, const my_list::Memory_location& ml) {
	out << ml.length << std::endl;
	return out;
}



class Pseudo;

class Memory {
public:
	Memory(int count);
	~Memory();
	void ShowMemory();

	void ShowMemory(size_t from, size_t to);

	void occupyMemory(my_list::Memory_location ml);

	void deoccupyMemory(my_list::Memory_location ml);

	void first_suitable(int count);

	void most_suitable(int count);
	void less_suitable(int count);
	void make_memory_free(int count);

	void check_and_modify_right(my_list::Memory_location& ml);
	void check_and_modify_left(my_list::Memory_location& ml, int position);
	int return_by_pointer(short* pointer);
	friend class Pseudo;
	Pseudo operator()(size_t i, size_t j);
private:
	short* memory;
	int size = 0;
	my_list::List free_memory;
	my_list::List not_free_memory;

};

class Memory_Guard {
public:
	Memory_Guard(Memory* new_memory) : memory(new_memory) {}
	~Memory_Guard() {
		delete memory;
	};

	Memory* get() const {
		return memory;
	};

	Memory& operator*() const {
		return *memory;
	};

	Memory* operator->() const {
		return memory;
	};
private:
	Memory* memory;
};


class Pseudo
{
public:
	Pseudo(Memory & memory_obj, int a, int b) : memory(memory_obj), from(a), to(b) {}

	Memory & operator= (bool condition) {
		int count = to - from;
		if (condition) {
			while (count >= 0) {
				memory.occupyMemory({ (memory.memory + from * 8) ,1 });
				++from;
				--count;
			}
		}
		else {
			while (count >= 0) {
				memory.deoccupyMemory({ (memory.memory + from * 8) ,1 });
				++from;
				--count;
			}
		}
		return memory;
	}
	Memory& memory;
	size_t from;
	size_t to;
};


int main()
{
	std::cout << "Enter memory size in Bytes, please: ";
	int size;
	std::cin >> size;
	Memory* p_memory = new Memory(size);
	Memory_Guard memory(p_memory);
	int n, tmp;
	size_t to, from;
	int mark;
	std::cout << "1 - Show Memory\n2 - First suitable\n3 - Most suitable\n4 - Less suitable\n5 - Make memory free\n6 - Pseudo operation\n7 - Show from -> to\n8 - Exit" << std::endl;
	bool exit = false;
	while (!exit) {
		std::cout << "Enter command: ";
		std::cin >> n;
		switch (n)
		{
		case 1:
			memory->ShowMemory();
			break;
		case 2:
			std::cout << "Enter size in Bytes: ";
			std::cin >> tmp;
			if (tmp > 0)
				memory->first_suitable(tmp);
			break;
		case 3:
			std::cout << "Enter size in Bytes: ";
			std::cin >> tmp;
			if (tmp > 0)
				memory->most_suitable(tmp);
			break;
		case 4:
			std::cout << "Enter size in Bytes: ";
			std::cin >> tmp;
			if (tmp > 0)
				memory->less_suitable(tmp);
			break;
		case 5:
			std::cout << "Enter size in Bytes: ";
			std::cin >> tmp;
			if (tmp > 0)
				memory->make_memory_free(tmp);
			break;
		case 6:
			std::cout << "Enter to and from and your mark: ";
			std::cin >> to >> from >> mark;
			try {
				memory->operator()(to, from) = mark;
			}
			catch (const std::exception& e) {
				std::cout << e.what() << std::endl;
			}
			continue;
		case 7:
			std::cout << "Enter to and from: ";
			std::cin >> to >> from;
			memory->ShowMemory(to, from);
			continue;
		case 8:
			exit = true;
			continue;
		default:
			std::cout << "Not in range!" << std::endl;
			break;
		}
	}
}

Memory::Memory(int count) {
	memory = new short[count * 8]{};
	size = count;
	free_memory.push_back({ memory, size });
}

Memory::~Memory()
{
	free_memory.clear();
	not_free_memory.clear();
	delete[] memory;
}

void Memory::ShowMemory() {
	std::cout << "Memory: " << std::endl;
	for (int i = 0; i < size * 8; ++i) {
		if (i % 8 == 0 && i != 0) { std::cout << " "; }
		std::cout << *(memory + i);
	}
	std::cout << std::endl;
}

void Memory::ShowMemory(size_t from, size_t to)
{
	if (from < 0 || to > size || from > to) {
		std::cout << "Wrong arguments!" << std::endl; 
		return;
	}
	std::cout << "Memory: " << std::endl;
	bool first_iteration = true;
	for (int i = from * 8; i < (to + 1) * 8; ++i) {
		if (i % 8 == 0 && !first_iteration) { std::cout << " "; }
		std::cout << *(memory + i);
		first_iteration = false;
	}
	std::cout << std::endl;
}

void Memory::occupyMemory(my_list::Memory_location ml) {
	for (int i = 0; i < ml.length * 8; ++i) {
		ml.location[i] = 1;
	}
}

void Memory::deoccupyMemory(my_list::Memory_location ml) {
	for (int i = 0; i < ml.length * 8; ++i) {
		ml.location[i] = 0;
	}
}

void Memory::first_suitable(int count) {
	for (int i = 0; i < free_memory.GetSize(); ++i) {
		if (free_memory[i].length >= count) {
			not_free_memory.push_back({ free_memory[i].location ,count });
			occupyMemory({ free_memory[i].location ,count });
			if (free_memory[i].length > count) {
				free_memory[i].location += 8 * count;
				free_memory[i].length -= count;
			}
			else {
				free_memory.removeAt(i);
			}
			return;
		}
	}
	std::cout << "There is not enough memory!" << std::endl;
}

void Memory::most_suitable(int count) {
	int most_suit;
	bool is_first = true, is_enough_memory = false;
	for (int i = 0; i < free_memory.GetSize(); ++i) {
		if (free_memory[i].length >= count) {
			is_enough_memory = true;
			if (free_memory[i].length == count) {
				not_free_memory.push_back({ free_memory[i].location ,count });
				occupyMemory({ free_memory[i].location ,count });
				free_memory.removeAt(i);
				return;
			}
			if (is_first) {
				most_suit = i;
				is_first = false;
			}
			else {
				if (free_memory[most_suit].length > free_memory[i].length) {
					most_suit = i;
				}
			}

		}
	}
	if (is_enough_memory) {
		not_free_memory.push_back({ free_memory[most_suit].location ,count });
		occupyMemory({ free_memory[most_suit].location ,count });
		free_memory[most_suit].location += 8 * count;
		free_memory[most_suit].length -= count;
		return;
	}
	std::cout << "There is not enough memory!" << std::endl;
}

void Memory::less_suitable(int count) {
	int less_suit;
	bool is_first = true, is_enough_memory = false;
	for (int i = 0; i < free_memory.GetSize(); ++i) {
		if (free_memory[i].length >= count) {
			is_enough_memory = true;
			if (is_first) {
				less_suit = i;
				is_first = false;
			}
			if (free_memory[less_suit].length < free_memory[i].length) {
				less_suit = i;
			}
		}
	}
	if (is_enough_memory) {
		not_free_memory.push_back({ free_memory[less_suit].location ,count });
		occupyMemory({ free_memory[less_suit].location ,count });
		if (free_memory[less_suit].length - count == 0) {
			free_memory.removeAt(less_suit);
			return;
		}
		free_memory[less_suit].location += 8 * count;
		free_memory[less_suit].length -= count;
		return;
	}
	std::cout << "There is not enough memory!" << std::endl;
}

void Memory::make_memory_free(int count) {
	bool clear_something = false;
	int tmp_size = not_free_memory.GetSize();
	for (int i = 0; i < tmp_size; ++i) {
		if (count <= 0) {
			break;
		}
		count -= not_free_memory[0].length;
		deoccupyMemory({ not_free_memory[0].location ,not_free_memory[0].length });
		free_memory.push_back({ not_free_memory[0].location, not_free_memory[0].length });
		check_and_modify_right(free_memory[free_memory.GetSize() - 1]);
		check_and_modify_left(free_memory[free_memory.GetSize() - 1], free_memory.GetSize() - 1);
		not_free_memory.pop_front();
		clear_something = true;
	}
	if (!clear_something || count > 0) {
		std::cout << "All memory is free" << std::endl;
	}
}

void Memory::check_and_modify_right(my_list::Memory_location & ml) {
	if (ml.location + (ml.length * 8) != memory + (size * 8)) {
		int tmp = return_by_pointer(ml.location + (ml.length * 8));
		if (tmp != -1) {
			ml.length += free_memory[tmp].length;
			free_memory.removeAt(tmp);
		}
	}
}

void Memory::check_and_modify_left(my_list::Memory_location & ml, int position) {
	short* tmp = ml.location;
	while (tmp != memory && *(tmp--) != 1) {
		--tmp;
	}
	if (tmp != ml.location) {
		int int_tmp = return_by_pointer(tmp);
		if (int_tmp != -1) {
			free_memory[int_tmp].length += ml.length;
			free_memory.removeAt(position);
		}
	}
}

int Memory::return_by_pointer(short * pointer) {
	for (int i = 0; i < free_memory.GetSize(); ++i) {
		if (free_memory[i].location == pointer) {
			return i;
		}
	}
	return -1;
}

Pseudo Memory::operator()(size_t i, size_t j)
{
	if (i < 0 || j > size || i > j) {
		throw std::invalid_argument("Wrong arguments!");
	}
	return Pseudo(*this, i, j);

}




