#pragma once
#include <list>
#include "Base_Shape.h"
#include "SFML/Graphics.hpp"
class composite_shape : public base_shape
{
	virtual std::size_t getPointCount() const override;
	virtual Vector2f getPoint(std::size_t index) const override;

	using Transformable::setPosition;
	using Transformable::setOrigin;
	using Transformable::getPosition;
	using Transformable::getRotation;
	using Transformable::getScale;
	using Transformable::getOrigin;
	using Transformable::getTransform;
	using Transformable::getInverseTransform;

	enum size_of_shape
	{
		small,
		medium,
		big
	};

	float scale = 1.f;
	std::list<base_shape*> shapes;
	size_of_shape shape_size;
	double shape_speed = 0.1;
	sf::Keyboard::Key last_direction = sf::Keyboard::A;
	bool automove = false;
public:
	composite_shape();
	composite_shape(const composite_shape& composite_shape);
	std::string get_data_to_save() override;
	void add_shape(base_shape* shape) override;
	void resize() override;
	void movement(sf::RenderWindow& window) override;
	void draw_shape(sf::RenderWindow& window) const override;
	bool select_shape(sf::RenderWindow& window) override;
	void clear() override;
	void collision_color_change() override;
	base_shape* clone() override;
    bool contains(const Vector2f& point) const override;
	void auto_movement(sf::RenderWindow& window) override;
	void paint_it_red() override;
	FloatRect getGlobalBounds() const override;
	std::list<base_shape*> get_shapes() const;
	size_of_shape get_size_of_shape() const;
	void make_speed_bigger() override;
	void change_automove() override;
	void make_speed_smaller() override;
	virtual void set_speed(double speed);
	void set_scale(float _scale) override;
	virtual void set_automove(bool _automove);
};