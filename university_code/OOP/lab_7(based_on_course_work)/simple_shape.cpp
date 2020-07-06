#include "pch.h"
#include <sstream>
#include "simple_shape.h"

simple_shape::simple_shape(float radius, std::size_t pointCount, sf::Color color, float positionX, float positionY, float scaleX, float scaleY, float setOrX, float setOrY) :
	radius(radius),  pointCount(pointCount), shape_color(color), shape_positionX(positionX), shape_positionY(positionY), shape_scaleX(scaleX), shape_scaleY(scaleY), shape_setOrX(setOrX), shape_setOrY(setOrY)
{
	update();
	setFillColor(color);
	setPosition(positionX, positionY);
	setScale(scaleX, scaleY);
	setOrigin(setOrX, setOrY);
}
simple_shape::simple_shape(const simple_shape & simple_shape)
{
	set_radius_and_point_count(simple_shape.get_radius(), simple_shape.getPointCount());
	setFillColor(simple_shape.getFillColor());
	setPosition(simple_shape.getPosition());
	setScale(simple_shape.getScale());
}
std::string simple_shape::get_data_to_save()
{	
	return std::string("simple_shape " + std::to_string(get_radius()) + " " + std::to_string(getPointCount()) + " " + std::to_string(getFillColor().toInteger()) + " " + std::to_string(getPosition().x) + " " + std::to_string(getPosition().y) + " " + std::to_string(getScale().x) + " " + std::to_string(getScale().y) + "\n");
}
void simple_shape::resize()
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

void simple_shape::movement(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && this->getPosition().x > 0)
	{
		this->move(-shape_speed * 30, 0.0f);
		last_direction = sf::Keyboard::A;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && this->getPosition().x + scale * radius * 2 < window.getSize().x)
	{
		this->move(shape_speed * 30, 0.0f);
		last_direction = sf::Keyboard::D;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && this->getPosition().y> 0)
	{
		this->move(0.0f, -shape_speed * 30);
		last_direction = sf::Keyboard::W;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && this->getPosition().y + scale * radius*2 < window.getSize().y)
	{
		this->move(0.0f, shape_speed * 30);
		last_direction = sf::Keyboard::S;
	}
}

void simple_shape::draw_shape(sf::RenderWindow & window) const
{
	window.draw(*this);
}

void simple_shape::make_speed_bigger() {
	shape_speed += 0.1;
}

void simple_shape::make_speed_smaller() {
	shape_speed -= 0.1;
	if (shape_speed <= 0) {
		shape_speed = 0;
	}
}

void simple_shape::set_scale(float _scale)
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

void simple_shape::set_speed(double speed)
{
	shape_speed = speed;
}

void simple_shape::change_automove() {
	automove = !automove;
}

bool simple_shape::get_automove() {
	return automove;
}

void simple_shape::auto_movement(sf::RenderWindow& window)
{
	if (automove) {
			if (last_direction == sf::Keyboard::A && this->getPosition().x > 0)
			{
				this->move(-shape_speed, 0.0f);
			}
			if (last_direction == sf::Keyboard::D && this->getPosition().x + scale * radius * 2 < window.getSize().x)
			{
				this->move(shape_speed, 0.0f);
			}
			if (last_direction == sf::Keyboard::W && this->getPosition().y > 0)
			{
				this->move(0.0f, -shape_speed);
			}
			if (last_direction == sf::Keyboard::S && this->getPosition().y + scale * radius * 2 < window.getSize().y)
			{
				this->move(0.0f, shape_speed);
			}
		}
}

bool simple_shape::select_shape(sf::RenderWindow & window)
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

void simple_shape::paint_it_red()
{
	setFillColor(sf::Color::Red);
}

base_shape * simple_shape::clone()
{
	return new simple_shape(*this);
}

void simple_shape::set_radius_and_point_count(float new_radius, std::size_t new_pointCount)
{
	radius = new_radius;
	pointCount = new_pointCount;
	update();
}

void simple_shape::set_automove(bool _automove)
{
	automove = _automove;
}

float simple_shape::get_radius() const
{
	return radius;
}

simple_shape::simple_shape(Help_Class)
{
	base_shape::addPrototype(Simple_Shape_ID, this);
}

std::size_t simple_shape::getPointCount() const
{
	return pointCount;
}

Vector2f simple_shape::getPoint(std::size_t index) const
{
	static const float pi = 3.141592654f;

	float angle = index * 2 * pi / pointCount - pi / 2;
	float x = std::cos(angle) * radius;
	float y = std::sin(angle) * radius;

	return Vector2f(radius + x, radius + y);
}

void simple_shape::add_shape(base_shape * shape)
{
	return;
}

void simple_shape::collision_color_change()
{
	return;
}

simple_shape simple_shape::prototype = simple_shape(Help_Class());