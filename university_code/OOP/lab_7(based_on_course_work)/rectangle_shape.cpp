#include "pch.h"
#include "rectangle_shape.h"
#include<sstream>

rectangle_shape::rectangle_shape(Help_Class)
{
	base_shape::addPrototype(Rectangle_Shape_ID, this);
}

std::size_t rectangle_shape::getPointCount() const
{
	return 4;
}

Vector2f rectangle_shape::getPoint(std::size_t index) const
{
	switch (index)
	{
	default:
	case 0: return Vector2f(0, 0);
	case 1: return Vector2f(size.x, 0);
	case 2: return Vector2f(size.x, size.y);
	case 3: return Vector2f(0, size.y);
	}
}

rectangle_shape::rectangle_shape(const Vector2f & new_size, sf::Color color, float positionX, float positionY, float scaleX, float scaleY) :
	size(new_size), shape_color(color), shape_positionX(positionX), shape_positionY(positionY), shape_scaleX(scaleX), shape_scaleY(scaleY)
{
	update();
	setFillColor(color);
	setPosition(positionX, positionY);
	setScale(scaleX, scaleY);
}

rectangle_shape::rectangle_shape(const rectangle_shape & rectangle)
{
	set_size(rectangle.get_size());
	setFillColor(rectangle.getFillColor());
	setPosition(rectangle.getPosition());
	setScale(rectangle.getScale());
}

std::string rectangle_shape::get_data_to_save()
{
	return std::string("rectangle_shape " + std::to_string(get_size().x) + " " + std::to_string(get_size().y) + " " + std::to_string(getFillColor().toInteger()) + " " + std::to_string(getPosition().x) + " " + std::to_string(getPosition().y) + " " + std::to_string(getScale().x) + " " + std::to_string(getScale().y) + "\n");

}

void rectangle_shape::resize()
{
	switch (shape_size)
	{
	case size_of_shape::small:
		this->setScale(1.5f, 1.5f);
		shape_size = size_of_shape::big;
		scale = 1.5f;
		break;
	case size_of_shape::medium:
		this->setScale(0.5f, 0.5f);
		shape_size = size_of_shape::small;
		scale = 0.5f;
		break;

	case size_of_shape::big:
		this->setScale(1.f, 1.f);
		shape_size = size_of_shape::medium;
		scale = 1.f;
		break;
	}
}

void rectangle_shape::movement(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && this->getPosition().x > 0)
	{
		this->move(-shape_speed * 30, 0.0f);
		last_direction = sf::Keyboard::A;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && this->getPosition().x + scale * this->get_size().x < window.getSize().x)
	{
		this->move(shape_speed * 30, 0.0f);
		last_direction = sf::Keyboard::D;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && this->getPosition().y > 0)
	{
		this->move(0.0f, -shape_speed * 30);
		last_direction = sf::Keyboard::W;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && this->getPosition().y + scale * this->get_size().y < window.getSize().y)
	{
		this->move(0.0f, shape_speed * 30);
		last_direction = sf::Keyboard::S;
	}
}

void rectangle_shape::draw_shape(sf::RenderWindow & window) const
{
	window.draw(*this);
}

void rectangle_shape::auto_movement(sf::RenderWindow& window)
{
	if (automove) {
		if (last_direction == sf::Keyboard::A && this->getPosition().x > 0)
		{
			this->move(-shape_speed, 0.0f);
		}
		if (last_direction == sf::Keyboard::D && this->getPosition().x + scale * this->get_size().x < window.getSize().x)
		{
			this->move(shape_speed, 0.0f);
		}
		if (last_direction == sf::Keyboard::W && this->getPosition().y > 0)
		{
			this->move(0.0f, -shape_speed);
		}
		if (last_direction == sf::Keyboard::S && this->getPosition().y + scale * this->get_size().y < window.getSize().y)
		{
			this->move(0.0f, shape_speed);
		}
	}
}

bool rectangle_shape::select_shape(sf::RenderWindow & window)
{
	sf::Vector2f mouse_position;
	mouse_position.x = sf::Mouse::getPosition(window).x;
	mouse_position.y = sf::Mouse::getPosition(window).y;
	if (this->getGlobalBounds().contains(mouse_position))
	{
		return true;

	}
	return false;
}

base_shape * rectangle_shape::clone()
{
	return new rectangle_shape(*this);
}

void rectangle_shape::set_size(Vector2f new_size)
{
		size = new_size;
		update();
}

Vector2f rectangle_shape::get_size() const
{
		return size;
}

void rectangle_shape::paint_it_red()
{
	setFillColor(sf::Color::Red);
}

void rectangle_shape::add_shape(base_shape * shape)
{
	return;
}

void rectangle_shape::set_scale(float _scale)
{
	scale = _scale;
	if (_scale == 1.5f) {
		shape_size = size_of_shape::big;
	}
	else if (_scale == 1.f) {
		size_of_shape::medium;
	}
	else if (_scale == 0.5f) {
		size_of_shape::small;
	}
}

void rectangle_shape::make_speed_bigger() {
	shape_speed += 0.1;
}

void rectangle_shape::make_speed_smaller() {
	shape_speed -= 0.1;
	if (shape_speed <= 0) {
		shape_speed = 0;
	}
}

void rectangle_shape::set_speed(double speed)
{
	shape_speed = speed;
}

void rectangle_shape::change_automove() {
	automove = !automove;
}


void rectangle_shape::set_automove(bool _automove)
{
	automove = _automove;
}

void rectangle_shape::collision_color_change()
{
	return;
}

rectangle_shape rectangle_shape::prototype = rectangle_shape(Help_Class());