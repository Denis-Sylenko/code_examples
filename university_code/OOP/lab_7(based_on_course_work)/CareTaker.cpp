#include "pch.h"
#include "CareTaker.h"

Memento * care_taker::get_memento() {
	return cared_memento;
}

void care_taker::set_memento(Memento * memento) {
	cared_memento = memento;
}
