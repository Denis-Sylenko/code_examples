#include "pch.h"
#include <sstream>
#include "Composite_Shape.h"

composite_shape::composite_shape() : shape_size(size_of_shape::medium)
{
	shapes = std::list<base_shape*>();
}

composite_shape::composite_shape(const composite_shape & composite_shape)
{
	shapes = composite_shape.get_shapes();
	shape_size = composite_shape.get_size_of_shape();
}

std::string composite_shape::get_data_to_save()
{
	std::string compose_data("composite_shape " + std::to_string(shapes.size()) + "\n");
	for (auto shape : shapes) {
		compose_data +=shape->get_data_to_save();
	}
	return compose_data;
}

void composite_shape::add_shape(base_shape* shape) {
	shapes.push_back(shape);
}


void composite_shape::draw_shape(sf::RenderWindow& window) const {
	for (auto shape : shapes) {
		shape->draw_shape(window);
	}
}

bool composite_shape::select_shape(sf::RenderWindow & window)
{
	sf::Vector2f mouse_position;
	mouse_position.x = sf::Mouse::getPosition(window).x;
	mouse_position.y = sf::Mouse::getPosition(window).y;
	
	if (this->contains(mouse_position)) {
			return true;
	}
	
	return false;
}

bool composite_shape::contains(const Vector2f& point) const
{
	for (auto shape : shapes)
	{
		if (shape->contains(point))
		{
			return true;
		}
	}
	return false;
}

void composite_shape::clear()
{
	return;
}

void composite_shape::resize() {
	switch (shape_size)
	{
	case size_of_shape::small:
		shape_size = size_of_shape::big;
		scale = 1.5f;
		for (auto shape : shapes) {
			shape->setScale(1.5f, 1.5f);
			shape->set_scale(scale);
		}		
		break;
	case size_of_shape::medium:
		shape_size = size_of_shape::small;
		scale = 0.5f;
		for (auto shape : shapes) {
			shape->setScale(0.5f, 0.5f);
			shape->set_scale(scale);
		}
		break;

	case size_of_shape::big:
		shape_size = size_of_shape::medium;
		scale = 1.f;
		for (auto shape : shapes) {
			shape->setScale(1.f, 1.f);
			shape->set_scale(scale);
		}
		break;
	}
}
	void composite_shape::movement(sf::RenderWindow& window){
		for (auto shape : shapes) {
			shape->movement(window);
		}
	}

	void composite_shape::auto_movement(sf::RenderWindow& window) {
		if (automove) {
			for (auto shape : shapes) {
				shape->auto_movement(window);
			}
		}
	}

	void composite_shape::make_speed_bigger() {
		shape_speed += 0.1;
		for (auto shape : shapes) {
			shape->set_speed(shape_speed);
		}
	}

	void composite_shape::make_speed_smaller() {
		shape_speed -= 0.1;
		if (shape_speed <= 0) {
			shape_speed = 0;
		}
		for (auto shape : shapes) {
			shape->set_speed(shape_speed);
		}
	}

	void composite_shape::set_speed(double speed)
	{
	}

	void composite_shape::set_scale(float _scale)
	{
	}

	void composite_shape::set_automove(bool _automove)
	{
	}

	void composite_shape::change_automove() {
		automove = !automove;
		for (auto shape : shapes) {
			shape->set_automove(automove);
		}
	}

	void composite_shape::paint_it_red()
	{
		for (auto shape : shapes) {
			for (auto shape2 : shapes) {
				if (shape->getGlobalBounds().intersects(shape2->getGlobalBounds()) && shape != shape2) {
					shape->paint_it_red();
					shape2->paint_it_red();
				}
			}
		}
	}

	FloatRect composite_shape::getGlobalBounds() const
	{
		float shape_left, shape_top, shape_width, shape_heigth;
		float left = 100000, top = 100000, right = -100000, bottom = -100000;
		FloatRect bounds;

		for (auto shape : shapes)
		{
			bounds = shape->getGlobalBounds();

			shape_left = bounds.left;
			shape_top = bounds.top;
			shape_width = bounds.width;
			shape_heigth = bounds.height;

			if (shape_left < left)
				left = shape_left;
			if (shape_left + shape_width > right)
				right = shape_left + shape_width;
			if (shape_top < top)
				top = shape_top;
			if (shape_top + shape_heigth > bottom)
				bottom = shape_top + shape_heigth;
		}
		return FloatRect(left, top, right - left, bottom - top);
	}

	std::list<base_shape*> composite_shape::get_shapes() const
	{
		return shapes;
	}

	composite_shape::size_of_shape composite_shape::get_size_of_shape() const
	{
		return shape_size;
	}

	std::size_t composite_shape::getPointCount() const
	{
		return std::size_t();
	}

	Vector2f composite_shape::getPoint(std::size_t index) const
	{
		return Vector2f();
	}

	void composite_shape::collision_color_change()
	{
		for (auto shape : shapes) {
			for (auto shape2 : shapes) {
				if (shape->getGlobalBounds().intersects(shape2->getGlobalBounds()) && shape != shape2)
				{
					shape->paint_it_red();
					shape2->paint_it_red();
				}
			}
		}
	}



	base_shape * composite_shape::clone()
	{
		composite_shape* copy = new composite_shape();
		for (auto shape : shapes)
		{
			copy->add_shape(shape->clone());
		}
		copy->shape_size = shape_size;

		return copy;
	}


