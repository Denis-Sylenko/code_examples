#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Handler {
public:
	virtual Handler *set_next(Handler *handler) = 0;
	virtual string handle(string request) = 0;
};

class AbstractHandler : public Handler {
public:
	AbstractHandler() : next_handler(nullptr) {}
	Handler *set_next(Handler *handler) override {
		next_handler = handler;
		return handler;
	}
	string handle(string request) override {
		if (next_handler) {
			return next_handler->handle(request);
		}

		return string();
	}
private:
	Handler *next_handler;
};

class InfantryHandler : public AbstractHandler {
public:
	string handle(string request) override {
		if (request == "Sword") {
			return "Infantryman : I'll take  the " + request + "\n";
		}
		else {
			return AbstractHandler::handle(request);
		}
	}
};

class ArcherHandler : public AbstractHandler {
public:
	string handle(string request) override {
		if (request == "Arrows") {
			return "Archer : I'll take  the " + request + "\n";
		}
		else {
			return AbstractHandler::handle(request);
		}
	}
};

class HorsemanHandler : public AbstractHandler {
public:
	string handle(string request) override {
		if (request == "Spare") {
			return "Horseman : I'll take  the " + request + "\n";
		}
		else {
			return AbstractHandler::handle(request);
		}
	}
};

class CrossbowHandler : public AbstractHandler {
public:
	string handle(string request) override {
		if (request == "Crossbow") {
			return "Crossbowman : I'll take  the " + request + "\n";
		}
		else {
			return AbstractHandler::handle(request);
		}
	}
};

void GeneralOfTheArmy(Handler &handler) {
	vector<string> weapons = { "Arrows", "Shield", "Sword", "Spare", "Axe", "Crossbow", "Blade" };
	for (auto weapon : weapons) {
		string result = handler.handle(weapon);
		if (!result.empty()) {
			cout << result;
		}
		else {
			cout << "We haven't got any soldiers that can use " << weapon << endl;
		}
	}
}

class HandlerManager {
public:
	HandlerManager() {
		infantry->set_next(archer)->set_next(horseman)->set_next(crossbowman);
	}
	~HandlerManager() {
		delete infantry;
		delete archer;
		delete horseman;
		delete crossbowman;
	}
	Handler& get_chain() {
		return *infantry;
	}
private:
	InfantryHandler* infantry = new InfantryHandler();
	ArcherHandler* archer = new ArcherHandler();
	HorsemanHandler* horseman = new HorsemanHandler();
	CrossbowHandler* crossbowman = new CrossbowHandler();
};

int main()
{
	HandlerManager manager;
	GeneralOfTheArmy(manager.get_chain());
	return 0;
}
