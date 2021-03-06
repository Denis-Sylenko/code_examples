#include "pch.h"
#include <iostream>
#include<memory>

using namespace std;

class Soldier {
public:
	Soldier() {
		hp = 100;
	}
	void SetHealth(int new_hp) {
		hp = new_hp;
		throw runtime_error("Our Exception"); //Демонстрационное исключение 
	}
	void Information() {
		cout << "I am soldier! I've got " << hp << " hp!" << endl;
	};
private:
	int hp;
};

class Army {
public: 
	Army() {
		reforms_amount = 0;
		soldier = make_shared<Soldier>();
	};
	void HealthReform(int new_hp) {	//										//Функция предоставляет строгую гарантию безопасноти исключений благодаря стратегии Copy and Swap
		shared_ptr<Soldier> tmp_soldier = make_shared<Soldier>(*soldier);	//Создаем копию объекта, который хотим изменить и оборачиваем ее в интеллектуальный указатель, чтоб не получить утечку ресурсов в дальнейшем 
		try {																//Данный блок try призван продемонстрировать транзитивность исключений в дальнейшем
			tmp_soldier->SetHealth(new_hp);									//Все операции проводим над копией объекта, чтоб в случае исключения не повредить исходный
		}																	//
		catch (exception& e) {												//Ловим исключение
			cout << "First catch: " << e.what() << endl;					//Выводим его сообщение 									
			throw;															//И пробрасываем
		}																	//
		reforms_amount++;													//Далее изменяем счетчик реформ. Это безопасная операция, но ее следует проводить уже после опасных, чтоб в случае возникновения в них исключения не изменить счетчик просто так
		swap(tmp_soldier, soldier);											//Далее выполняем функцию swap, предоставляющую строгую гарантию безопасности исключений
	};																		//Таким образом данная функция обещает, что если исключение будет возбуждено, то состояние программы не изменится 
	void PrintInformation() {
		soldier->Information();
	}
private:
	shared_ptr<Soldier> soldier;
	int reforms_amount; 
};

int main()
{
	Army ar;
	ar.PrintInformation();
	try {					//Ловим возможное исключение
		ar.HealthReform(200);
	}
	catch (exception& e) {	
		cout << "Second catch: " << e.what() << endl; //Демонстрируем транзитивность исключений
	}
	ar.PrintInformation();	// При возникновении исключения не произойдет утечек памяти и состояние программы и ее сущности (в частности - объекта ar) не изменится. Если исключений не будет - все отработает корректно
	return 0;
}
