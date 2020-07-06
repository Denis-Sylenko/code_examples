#pragma once
#include <string>
#include "Memento.h"
class care_taker {
public:
	Memento* get_memento();
	void set_memento(Memento* memento);
private:
	Memento * cared_memento = nullptr;
};