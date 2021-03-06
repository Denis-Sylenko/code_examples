#include "pch.h"  //cout нужен только для демонстративности
#include <iostream>
#include<windows.h>

using namespace std;

class FileGuard { // Класс FileGuard, который служит оберткой над нашим дескриптором
public:
	FileGuard(HANDLE handle) : file_handle(handle) {
		cout << "Open" << endl;
	};
	~FileGuard() {//В дескрипторе закрываем file_handle
		cout << "Close" << endl;
		CloseHandle(file_handle);
	};

	 operator HANDLE () {
		 	return file_handle;
	}
private:
	HANDLE file_handle;
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
		FileGuard guard(handle); //Создаем на стеке объект нашего класса, который при вызове деструктора закроет наш handle 
	}
	return 0;
}
