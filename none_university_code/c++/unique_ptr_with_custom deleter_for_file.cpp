#include "pch.h" //Для Visual Studio
#include <iostream>
#include<windows.h>
using namespace std;
struct Deleter { //Создаем структуру, которую передадим как второй аргумент в список шаблонных параметров unique_ptr
	void operator()(HANDLE* file_handle) const {
		if (CloseHandle(*file_handle)) cout << "Right!"; //cout нужен только для демонстративности
		else cout << "Error";
	};
};
int main()
{
	HANDLE handle = CreateFile(
		L"D:\\SimpleFile_1.txt",
		GENERIC_WRITE,
		NULL,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (handle != INVALID_HANDLE_VALUE) {
		std::unique_ptr<HANDLE, Deleter> up(&handle); //Создаем unique_ptr с custom deleter над нашим объектом
	}
	return 0;
}
