// 4_Lab_Sylenko.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include<vector>
#include "SFML\Graphics.hpp"
#include <thread>
#include"Shape.h"


class Test : New_Shape {
	void somth() {
		std::cout << "1";
	}

	std::size_t getPointCount() const
	{
		return 1;
	}


	////////////////////////////////////////////////////////////
	sf::Vector2f getPoint(std::size_t index) const
	{
		static const float pi = 3.141592654f;

		float angle = index * 2 * pi / 1 - pi / 2;
		float x = std::cos(angle) * 1;
		float y = std::sin(angle) * 1;

		return sf::Vector2f(1 + x, 1 + y);
	}

};

class My_Shape {
public:
	
	void resize() {
		switch (counter_for_swich_case)
		{
		case 0:

			for (auto shape : agregate_shape) {
				shape->setScale(1.5f, 1.5f);
				scale = 1.5f;
			}
			++counter_for_swich_case;
			break;
		case 1:
			for (auto shape : agregate_shape) {
				shape->setScale(0.5f, 0.5f);
				scale = 0.5f;
			}
			++counter_for_swich_case;
			break;

		default:
			for (auto shape : agregate_shape) {
				shape->setScale(1.f, 1.f);
				scale = 1.f;
			}
			counter_for_swich_case = 0;
		}
	}
	void movement(sf::RenderWindow& window)
	{
		for (auto shape : agregate_shape) {

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && shape->getPosition().x - scale * 100 >= 0)
				{
					shape->move(-shape_speed * 30, 0.0f);
					last_direction = sf::Keyboard::A;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) &&  shape->getPosition().x + scale*100 <= window.getSize().x)
				{
					shape->move(shape_speed * 30, 0.0f);
					last_direction = sf::Keyboard::D;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && shape->getPosition().y - scale * 100 >= 0 )
				{
					shape->move(0.0f, -shape_speed * 30);
					last_direction = sf::Keyboard::W;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && shape->getPosition().y + scale * 100 <= window.getSize().y)
				{
					shape->move(0.0f, shape_speed * 30);
					last_direction = sf::Keyboard::S;
				}
		}
	}


	void add_element_to_all(std::vector<sf::CircleShape*> shape) {
		all_shapes.push_back(shape);
	}

	void add_element_to_agregate(sf::CircleShape* shape) {
		agregate_shape.push_back(shape);
	}

	void draw_shapes(sf::RenderWindow& window)
	{
		for(auto a : agregate_shape) {
				window.draw(*a);
			}
	}

	void select_shapes(sf::RenderWindow& window)
	{
		
		sf::Vector2f mouse_position;
		mouse_position.x = sf::Mouse::getPosition(window).x;
		mouse_position.y = sf::Mouse::getPosition(window).y;
		
		for (auto a : all_shapes)
		{
			bool exist = false;
			for (auto shape : a) {
				if (shape->getGlobalBounds().contains(mouse_position))
				{
					exist = true;
					
				}
			}
			if (exist) {
				if (agregate_shape.empty()) {
					for (auto shape : a) 
					agregate_shape.push_back(shape);
				}
				else {
					int size = agregate_shape.size();
					for (int i = 0; i < size; ++i) {
						agregate_shape.push_back(new sf::CircleShape(*agregate_shape[i]));
					}
					for (auto shape : a)
						agregate_shape.push_back(new sf::CircleShape(*shape));
						agregate_shape.erase(agregate_shape.begin(), agregate_shape.begin()+size);			

				}
			}
		}
	}

	void clear_all() {
		for (auto shapes : all_shapes)
			for (auto shape : shapes)
				delete shape;
		all_shapes.clear();
		clear_agregate();
	}

	void collision_color_change()
	{
		for (auto shp1 : agregate_shape) {
			for (auto shp2 : agregate_shape) {
				if (shp1->getGlobalBounds().intersects(shp2->getGlobalBounds())  && shp1 != shp2)
				{
					shp2->setFillColor(sf::Color::Red);
				}
			}
		}
	}

	void automovement(sf::RenderWindow& window) {
		if (automove) {
			for (auto shape : agregate_shape) {
				if (last_direction == sf::Keyboard::A && shape->getPosition().x - scale * 100 >= 0)
				{
					shape->move(-shape_speed, 0.0f);
				}
				if (last_direction == sf::Keyboard::D && shape->getPosition().x + scale * 100 <= window.getSize().x)
				{
					shape->move(shape_speed, 0.0f);
				}
				if (last_direction == sf::Keyboard::W && shape->getPosition().y - scale * 100 >= 0)
				{
					shape->move(0.0f, -shape_speed);
				}
				if (last_direction == sf::Keyboard::S && shape->getPosition().y + scale * 100 <= window.getSize().y)
				{
					shape->move(0.0f, shape_speed);
				}
			}
		}
	}


	void make_speed_bigger() {
		shape_speed += 0.1;
	}

	void make_speed_smaller() {
		shape_speed -= 0.1;
		if (shape_speed == 0) {
			shape_speed = 0;
		}
	}

	void change_automove() {
		automove = !automove;
	}

	void clear_agregate() {
		if(agregate_shape.size() > 1)
		all_shapes.push_back(agregate_shape);
		agregate_shape.clear();
	}

private:
	bool automove = false;
	double shape_speed = 0.1;
	float scale = 1.f;
	int counter_for_swich_case = 0;
	std::vector<std::vector<sf::CircleShape*>> all_shapes;
	std::vector<sf::CircleShape*> agregate_shape;
	sf::Keyboard::Key last_direction = sf::Keyboard::A;
};

int main()
{
	
	My_Shape my_shape;
	
	sf::RenderWindow window({ 1600,980 }, "4_Lab_Sylenko", sf::Style::Default);
	bool tail_visible = false;

	while (window.isOpen())
	{
		sf::Event event;
		
		while (window.pollEvent(event))
		{
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
				window.close();
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
				my_shape.make_speed_bigger();
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
			{
				my_shape.make_speed_smaller();
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1)
			{
				my_shape.clear_agregate();
				sf::CircleShape* tmp_shape = new sf::CircleShape(100);
				tmp_shape->setScale(1.0f, 1.0f);
				tmp_shape->setFillColor(sf::Color::Green);
				tmp_shape->setOrigin(100, 100);
				tmp_shape->setPosition(100, 120);
				my_shape.add_element_to_all({ tmp_shape });
				my_shape.add_element_to_agregate(tmp_shape);
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2)
			{
				my_shape.clear_agregate();
				sf::CircleShape* tmp_shape = new sf::CircleShape(100, 4);
				tmp_shape->setScale(1.0f, 1.0f);
				tmp_shape->setFillColor(sf::Color::Magenta);
				tmp_shape->setOrigin(100, 100);
				tmp_shape->setPosition(350, 120);
				my_shape.add_element_to_all({ tmp_shape });
				my_shape.add_element_to_agregate(tmp_shape);
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num3)
			{
				my_shape.clear_agregate();
				sf::CircleShape* tmp_shape = new sf::CircleShape(100, 3);
				tmp_shape->setScale(1.0f, 1.0f);
				tmp_shape->setFillColor(sf::Color::Yellow);
				tmp_shape->setOrigin(100, 100);
				tmp_shape->setPosition(550, 120);
				my_shape.add_element_to_all({ tmp_shape });
				my_shape.add_element_to_agregate(tmp_shape);
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num4)
			{
				my_shape.clear_agregate();
				sf::CircleShape* tmp_shape = new sf::CircleShape(100, 8);
				tmp_shape->setScale(1.0f, 1.0f);
				tmp_shape->setFillColor(sf::Color::White);
				tmp_shape->setOrigin(100, 100);
				tmp_shape->setPosition(750, 120);
				my_shape.add_element_to_all({ tmp_shape });
				my_shape.add_element_to_agregate(tmp_shape);
			}

			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M)
			{
				my_shape.change_automove();
			}

			else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				my_shape.select_shapes(window);
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				my_shape.clear_agregate();
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::D)
			{
				my_shape.movement(window);
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
			{
				my_shape.resize();
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
				window.clear();
				std::cout << "cleared";
			}
		
		my_shape.collision_color_change();
		my_shape.automovement(window);
		my_shape.draw_shapes(window);
		window.display();
	}

	return 0;
}