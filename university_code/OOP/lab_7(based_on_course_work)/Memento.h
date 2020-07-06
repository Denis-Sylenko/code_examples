#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "base_shape.h"
class Memento {
public:
	std::string get_filename() {
		return file_name;
	}
	Memento(std::string state) {
		std::ofstream rewrite(file_name);
		rewrite.write("", 0);
		rewrite.close();

		std::ofstream stream;
		stream.open(file_name, std::ios_base::app);
		stream << state;
		stream.close();
	}
private:
	friend class base_shape;
	std::string file_name = "states.txt";
};