// The task is to find the AES ECB string form "crypto.txt" file

#include "pch.h"//Для VS
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <fstream>

using namespace std;

void ReadFromFileToVector(vector<vector<string>>& vector_of_vector_of_strings, string&& file) { // Прочитаем все строки из файла и каждую из них поделим на строки по 16 байт (128 бит)
	ifstream is(move(file));																	//Поскольку размер блока AES равен 128 бит == 16 байт
	string line;
	size_t count = 0;
	
	if (is) {
		while (getline(is, line)) {
			vector_of_vector_of_strings.push_back({});
			for (size_t i = 0; i < line.length(); i += 16) {
				vector_of_vector_of_strings[count].push_back( line.substr(i, 16) );
			}
			++count;
		}
	}
	else {
		std::cout << "Can't find that file!" << std::endl;
	}
};

int AmountOfRepeat(vector<string>& vector_of_strings) { //В режиме ECB одинаковым блокам данным соответствуют одинаковые блоки шифрокода.
	set<string> tmp_set;								//Соответственно, необходимо определить строку, в которой будут присутствовать одинаковые шифроблоки
	for (auto a : vector_of_strings) {
		tmp_set.insert(a);								//Я решил это реализовать с использованием дополнительной памяти в виде контейнера set, элементы в котором не повторяются
	}													//Можно было бы не использовать дополнительную память, а использовать vector.count(), но я посчитал, что так мы будем иметь квадратическую сложность алгоритма, поскольку count() необходимо было бы выполнить для каждого элемента
	return vector_of_strings.size() - tmp_set.size();	//Эта разница определяет, были ли в векторе повторяющиеся элементы
}

int IndexOfMaximumRepetitionString(vector<vector<string>>& vector_of_vector_of_strings) {//Находим строку с наибольшим колличеством повторений
	int maximum = 0, index = 0;
	for (int i = 0; i < vector_of_vector_of_strings.size(); ++i) {
		int amount = AmountOfRepeat(vector_of_vector_of_strings[i]);
		if (maximum < amount) {
			maximum = amount;
			index = i;
		};
	}
	return index; //Вернем ее индекс 
}

int main()
{
	vector<vector<string>> vector_of_ciphertexts;
	ReadFromFileToVector(vector_of_ciphertexts, "crypto.txt");//Расположение файла, который был дан в задании. Переименовал его для удобства 
	int index_of_AES_ECB_string = IndexOfMaximumRepetitionString(vector_of_ciphertexts);
	std::cout << index_of_AES_ECB_string << std::endl;
	for (const string& a : vector_of_ciphertexts[index_of_AES_ECB_string]) {
		std::cout << a << " "; // Вывод строки, разбитой пробелами для наглядной демонстрации повторяющихся блоков
	}
	std::cout << endl;
	return 0;
}
