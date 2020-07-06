#include "pch.h"
#include "Controller.h"
#include "CareTaker.h"
void Controller::start()
{
	shape_container my_shape;
	care_taker* memento_care = new care_taker();
	sf::RenderWindow* window = Singleton::getInstance();
	bool tail_visible = false;
	while (window->isOpen())
	{
		sf::Event event;

		while (window->pollEvent(event))
		{
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
				window->close();
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
				if (my_shape.get_selected_shape() != nullptr) {
					my_shape.get_selected_shape()->make_speed_bigger();
				}
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
			{
				if (my_shape.get_selected_shape() != nullptr) {
					my_shape.get_selected_shape()->make_speed_smaller();
				}
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1)
			{
				my_shape.clear_selected();
				base_shape* tmp_shape = base_shape::create_shape(Rectangle_Shape_ID);
				Vector2f size(200, 100);
				dynamic_cast<rectangle_shape*>(tmp_shape)->set_size(size);
				my_shape.add_to_all(tmp_shape);
				tmp_shape->setFillColor(sf::Color::White);
				tmp_shape->setPosition(150, 120);
				base_shape* temp_shape = tmp_shape->clone();
				my_shape.add_to_all(temp_shape);
				my_shape.add_to_selected(temp_shape);
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2)
			{
				my_shape.clear_selected();
				base_shape* tmp_shape = base_shape::create_shape(Simple_Shape_ID);
				dynamic_cast<simple_shape*>(tmp_shape)->set_radius_and_point_count(100.f, 50);
				tmp_shape->setFillColor(sf::Color::Magenta);
				tmp_shape->setPosition(350, 120);
				my_shape.add_to_all(tmp_shape);
				base_shape* temp_shape = tmp_shape->clone();
				my_shape.add_to_all(temp_shape);
				my_shape.add_to_selected(temp_shape);
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num3)
			{
				my_shape.clear_selected();
				base_shape* tmp_shape = base_shape::create_shape(Simple_Shape_ID);
				dynamic_cast<simple_shape*>(tmp_shape)->set_radius_and_point_count(100.f, 4);
				tmp_shape->setFillColor(sf::Color::Green);
				tmp_shape->setPosition(550, 120);
				my_shape.add_to_all(tmp_shape);
				base_shape* temp_shape = tmp_shape->clone();
				my_shape.add_to_all(temp_shape);
				my_shape.add_to_selected(temp_shape);
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num4)
			{
				my_shape.clear_selected();
				base_shape* tmp_shape = base_shape::create_shape(Simple_Shape_ID);
				dynamic_cast<simple_shape*>(tmp_shape)->set_radius_and_point_count(100.f, 3);
				tmp_shape->setFillColor(sf::Color::Yellow);
				tmp_shape->setPosition(750, 120);
				my_shape.add_to_all(tmp_shape);
				base_shape* temp_shape = tmp_shape->clone();
				my_shape.add_to_all(temp_shape);
				my_shape.add_to_selected(temp_shape);
			}

			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M)
			{
				if (my_shape.get_selected_shape() != nullptr) {
					my_shape.get_selected_shape()->change_automove();
				}
			}

			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)
			{
				memento_care->set_memento(my_shape.save_state());
			}

			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::L)
			{
				if (memento_care->get_memento() != nullptr) {
					my_shape.load_state(memento_care->get_memento());
				}
			}

			else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				Sleep(500);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					my_shape.select_shape(*window);
				}
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				my_shape.clear_selected();
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::D)
			{
				if (my_shape.get_selected_shape() != nullptr) {
					my_shape.get_selected_shape()->movement(*window);
				}
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
			{
				if (my_shape.get_selected_shape() != nullptr) {
					my_shape.get_selected_shape()->resize();
				}
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C)
			{
				my_shape.clear_all();
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
			{
				tail_visible = !tail_visible;
			}
		}
		if (!tail_visible) {
			window->clear();
		}

		my_shape.collision_color_change();
		if (my_shape.get_selected_shape() != nullptr) {
			my_shape.get_selected_shape()->auto_movement(*window);
			my_shape.get_selected_shape()->draw_shape(*window);
		}
		window->display();
	}
}
