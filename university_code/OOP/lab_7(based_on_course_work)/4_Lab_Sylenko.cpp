#include "pch.h"
#include "Controller.h"
#include "thread_demonstration.h"

int main()
{	
	thread_demonstration* demonstrator = new thread_demonstration();
	sf::RenderWindow* window = Singleton::getInstance();
	demonstrator -> start_demonstration(window);
	sf::Event event;
	while (true) {
		demonstrator->move_to_aim(window);
		window->clear();
		demonstrator->draw(window);
		window->display();
		window->pollEvent(event);
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) {
			window->close();
			break;
		}
	}
	return 0;
}