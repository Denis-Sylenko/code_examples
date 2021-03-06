#include "pch.h"
#include <iostream>
#include<vector>

//Абстрактные классы рыцаря, стрелка и пехотинца

class Knight { 
public:
	virtual void Information() = 0;
	virtual ~Knight() {}
};

class Shooter {
public:
	virtual void Information() = 0;
	virtual ~Shooter() {}
};

class Infantryman {
public:
	virtual void Information() = 0;
	virtual ~Infantryman() {}
};

//Унаследованные от них классы соответствующих боевых единиц английской и французской сторон

class EnglishKnight :public Knight { 
public:
	void Information() {
		std::cout << "English Knight";
	}
};

class EnglishShooter :public Shooter {
public:
	void Information() {
		std::cout << "English Shooter";
	}
};

class EnglishInfantryman :public Infantryman {
public:
	void Information() {
		std::cout << "English Infantryman";
	}
};

class FrenchKnight :public Knight {
public:
	void Information() {
		std::cout << "French Knight";
	}
};

class FrenchShooter :public Shooter {
public:
	void Information() {
		std::cout << "French Shooter";
	}
};

class FrenchInfantryman :public Infantryman {
public:
	void Information() {
		std::cout << "French Infantryman";
	}
};

//Абстрактная фабрика по производству воинов

class ArmyFactory
{
public:
	virtual Knight* createKnight() = 0;
	virtual Shooter* createShooter() = 0;
	virtual Infantryman* createInfantryman() = 0;
	virtual ~ArmyFactory() {}
};

//Унаследованные от нее английская и французская фабрики

class EnglishArmyFactory : public ArmyFactory { 
public:
	Knight* createKnight() {
		return new EnglishKnight;
	}
	Shooter* createShooter() {
		return new EnglishShooter;
	}
	Infantryman* createInfantryman() {
		return new EnglishInfantryman;
	}
};

class FrenchArmyFactory : public ArmyFactory {
public:
	Knight* createKnight() {
		return new FrenchKnight;
	}
	Shooter* createShooter() {
		return new FrenchShooter;
	}
	Infantryman* createInfantryman() {
		return new FrenchInfantryman;
	}
};

class Army //Класс армия
{
public:
	
	void Information() {
		if (Knights.size() > 0) {
			Knights[0]->Information(); 
			std::cout << " : " << Knights.size() << std::endl;
		}
		else std::cout << " This army hasn't got any Knights! " << std::endl;
		if (Shooters.size() > 0) {
			Shooters[0]->Information();
			std::cout << " : " << Shooters.size() << std::endl;
		}
		else std::cout << " This army hasn't got any Shooters! " << std::endl;
		if (Infantrymans.size() > 0) {
			Infantrymans[0]->Information();
			std::cout << " : " << Infantrymans.size() << std::endl;
		}
		else std::cout << " This army hasn't got any Infantryman! " << std::endl;
	}

	~Army() {
		for (Knight* SingleKnight : Knights) delete SingleKnight;
		for (Shooter* SingleShooter : Shooters)  delete SingleShooter;
		for (Infantryman* SingleInfantryman : Infantrymans) delete SingleInfantryman;
	}
	std::vector<Knight*> Knights;
	std::vector<Shooter*> Shooters;
	std::vector<Infantryman*> Infantrymans;

};

class Battle { //Класс битва, в котором определенный метод создает армию с помощью абстрактной фабрики
public:
	Army* createArmy(ArmyFactory& factory, int size) {
		Army* newArmy = new Army;
		for (int i = 0; i < size; i++) {
			newArmy->Knights.push_back(factory.createKnight());
			newArmy->Shooters.push_back(factory.createShooter());
			newArmy->Infantrymans.push_back(factory.createInfantryman());
		}
		return newArmy;
	}
};


int main()
{
	//Демонстрация
	Battle battle;
	EnglishArmyFactory EnglishFactory;
	FrenchArmyFactory FrenchFactory;

	Army* EnglishArmy = battle.createArmy(EnglishFactory, 15000);
	Army* FrenchArmy = battle.createArmy(FrenchFactory, 10000);

	std::cout << "English army: " << std::endl;
	EnglishArmy->Information();

	std::cout << "French army: " << std::endl;
	FrenchArmy->Information();
}
