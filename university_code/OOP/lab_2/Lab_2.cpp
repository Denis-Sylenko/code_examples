#include "pch.h"
#include <iostream>
#include"List.h"


struct Memory_location {
	short* location = nullptr;
	int length = int();
};

std::ostream& operator << (std::ostream& out, const Memory_location& ml) {
	out << ml.length << std::endl;
	return out;
}

class Memory {
public:
	Memory(int count);
	void ShowMemory();

	void occupyMemory(Memory_location ml);

	void deoccupyMemory(Memory_location ml);

	void first_suitable(int count);

	void most_suitable(int count);
	void less_suitable(int count);
	void make_memory_free(int count);

	void check_and_modify_right(Memory_location& ml);
	void check_and_modify_left(Memory_location& ml, int position);
	int return_by_pointer(short* pointer);

private:
	short* memory;
	int size = 0;
	List<Memory_location> free_memory;
	List<Memory_location> not_free_memory;
};


int main()
{
	std::cout << "Enter memory size in Bytes, please: ";
	int size;
	std::cin >> size;
	Memory* memory = new Memory(size);
	int n, tmp;
	std::cout << "1 - Show Memory\n2 - First suitable\n3 - Most suitable\n4 - Less suitable\n5 - Make memory free\n6 - Exit" << std::endl;
	bool exit = false;
	while (!exit) {
		std::cout << "Enter command: ";
		std::cin >> n;
		switch (n)
		{
		case 1:
			std::cout << "Memory:" << std::endl;
			memory->ShowMemory();
			break;
		case 2:
			std::cout << "Enter size in Bytes: ";
			std::cin >> tmp;
			if(tmp>0)
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
			exit = true;
			continue;
		default:
			std::cout << "Not in range!" << std::endl;
			break;
		}
	}
}

Memory::Memory(int count){
	memory = new short[count * 8]{};
	size = count;
	free_memory.push_back({ memory, size });
}

void Memory::ShowMemory() {
	std::cout << "Memory: " << std::endl;
	for (int i = 0; i < size * 8; ++i) {
		if (i % 8 == 0 && i != 0) { std::cout << " "; }
		std::cout << *(memory + i);
	}
	std::cout << std::endl;
}

void Memory::occupyMemory(Memory_location ml) {
	for (int i = 0; i < ml.length * 8; ++i) {
		ml.location[i] = 1;
	}
}

void Memory::deoccupyMemory(Memory_location ml) {
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
				if (free_memory[most_suit].length > free_memory[i].length ) {
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
			if (free_memory[less_suit].length  < free_memory[i].length ) {
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

void Memory::check_and_modify_right(Memory_location & ml) {
	if (ml.location + (ml.length * 8) != memory + (size * 8)) {
		int tmp = return_by_pointer(ml.location + (ml.length * 8));
		if (tmp != -1) {
			ml.length += free_memory[tmp].length;
			free_memory.removeAt(tmp);
		}
	}
}

void Memory::check_and_modify_left(Memory_location & ml, int position) {
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

