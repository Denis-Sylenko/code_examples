#include "pch.h" 

bool IsLeapYear(int year) {
	if (year < 0) { throw std::out_of_range("This is not our era"); } //Для наглядности
	if (year % 4 != 0 || (year % 100 == 0 && year % 400 != 0)) return false;
	return true;
}

int main () {
return 0;
};