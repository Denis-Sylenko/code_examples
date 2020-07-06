#pragma once
#include "SFML\Graphics.hpp"
class Singleton
{
private:
	Singleton() {}
	Singleton(const Singleton&) = delete;
	Singleton& operator=(Singleton&) = delete;
	
public:
	static sf::RenderWindow* getInstance() {
		static sf::RenderWindow  instance({ 1600,980 }, "kursovaya", sf::Style::Default);
		return &instance;
	}
};