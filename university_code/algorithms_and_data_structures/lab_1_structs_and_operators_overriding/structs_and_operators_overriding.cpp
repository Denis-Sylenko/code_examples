#include "pch.h"
#include <iostream>
#include <string>

struct Person {
	std::string Name;
	std::string Surname;
	std::string LastName;
};

struct PersonalInfo {
	std::string Adress;
	std::string Number;
};

struct PersonalData {
	Person Person;
	PersonalInfo PersonInfo;
};

std::ostream& operator<< (std::ostream& out, const Person& p) {
	out << "Name: " << p.Name << " Surname: " << p.Surname << " Lastname: " << p.LastName << std::endl;
	return out;
}

std::ostream& operator<< (std::ostream& out, const PersonalInfo& pi) {
	out << "Adress: " << pi.Adress << " Number: " << pi.Number << std::endl;
	return out;
}

std::ostream& operator<< (std::ostream& out, const PersonalData& pd) {
	out << "Full Personal Info: " << std::endl << pd.Person << pd.PersonInfo;
	return out;
}

std::istream& operator>> (std::istream& input, Person& p) {
	input >> p.Name >> p.Surname >> p.LastName;
	return input;
}

std::istream& operator>> (std::istream& input,  PersonalInfo& pi) {
	input >> pi.Adress >> pi.Number;
	return input;
}

std::istream& operator>> (std::istream& input,  PersonalData& pd) {
	input >> pd.Person >> pd.PersonInfo;
	return input;
}

struct DataBase {
	PersonalData* dataBase = nullptr;
	int Size = 0;

	void GetPersonalNumber(std::string surname) {
		if (Size == 0) {
			std::cout << "The Base is empty now! Try to add some elenments." << std::endl;
			return;
		}
		for (int i = 0; i < Size; i++) {
			if ((dataBase + i)->Person.Surname == surname) {
				std::cout << "Number: " << (dataBase + i)->PersonInfo.Number << std::endl;
			}
		}
	}

	void PrintBase() {
		if (Size == 0) {
			std::cout << "The Base is empty now! Try to add some elenments." << std::endl;
			return;
		}
		for (int i = 0; i < Size; i++) {
			std::cout << *(dataBase + i);
		}
	}

	void PrintSize() {
		std::cout << "Size: " << Size << std::endl;
	}

	void AddElement() {
		AddElements(1);
	}

	void AddElements(int count) {
		PersonalData* newdataBase = new PersonalData[Size + count];
		for (int i = 0; i < Size; i++) {
			*(newdataBase + i) = *(dataBase + i);
		}
		delete[] dataBase;
		std::cout << "Enter " << count << " persons data" << std::endl;
		for (int i = Size; i < Size+count; i++) {
			std::cin >> *(newdataBase + i);
		}
		dataBase = newdataBase;
		newdataBase = nullptr;
		Size += count;
	}

	void DeleteElement() {
		DeleteElements(1);
	}

	void DeleteElements(int count) {
		if (Size == 0) {
			std::cout << "The Base is empty now! Try to add some elenments." << std::endl;
			return;
		}
		PersonalData* newdataBase = new PersonalData[Size-count];
		int counter = 0;
		for (int j = 0; j < count; j++) {
			std::string surname;
			std::cout << "Enter " << count << " surnames" << std::endl;
			std::cin >> surname;
			for (int i = 0; i < Size; i++) {
				if (dataBase[i].Person.Surname != surname) {
					*(newdataBase + counter) = *(dataBase + i);
					counter++;
				}
			}
		}
		delete[] dataBase;
		dataBase = newdataBase;
		newdataBase = nullptr;
		Size -= count;
	}
};

int main()
{

	int command, count;
	bool again = true;
	DataBase* database = new DataBase;
	std::string surname;
	std::cout << "Commands: " << std::endl << "1 - Add Element\n2 - Add n Elements\n3 - Delete Element\n4 - Delete n Elements\n5 - Get number by surname\n6 - Print Base\n7 - Print Base's Size\n8 - Exit" << std::endl;
	while (again) {
		std::cout << "Enter command: ";
		std::cin >> command;
		switch (command)
		{
		case 1:
			database->AddElement();
		case 2:
			std::cout << "Enter count of elements ";
			std::cin >> count;
			database->AddElements(count);
			break;
		case 3:
			database->DeleteElement();
		case 4:
			std::cout << "Enter count of elements ";
			std::cin >> count;
			database->DeleteElements(count);
			break;
		case 5:
			std::cout << "Enter surname ";
			std::cin >> surname;
			database->GetPersonalNumber(surname);
			break;
		case 6:
			database->PrintBase();
			break;
		case 7:
			database->PrintSize();
			break;
		case 8:
			again = false;
			delete[] database;
			continue;
			break;
		default:
			std::cout << "Command is not in range! " << std::endl;
			break;
		}
	}
	return 0;
}