#pragma once
#include "Base_Shape.h"
#include "SFML/Graphics.hpp"

class rectangle_shape : public base_shape
{
public:
	rectangle_shape(const Vector2f& size = Vector2f(0, 0), sf::Color color = sf::Color::Blue, float positionX = 100.f, float positionY = 100.f, float scaleX = 1.f, float scaleY = 1.f);
	rectangle_shape(const rectangle_shape& composite_shape);
	std::string get_data_to_save() override;
	void resize() override;
	void movement(sf::RenderWindow& window) override;
	void draw_shape(sf::RenderWindow& window) const override;
	void collision_color_change() override;
	void auto_movement(sf::RenderWindow& window) override;
	bool select_shape(sf::RenderWindow& window) override;
	base_shape* clone() override;
	void set_size(Vector2f new_size);
	Vector2f get_size() const;
	void paint_it_red() override;
	using Transformable::setPosition;
	using Transformable::setOrigin;
	void set_scale(float _scale) override;
	void make_speed_bigger() override;
	void change_automove() override;
	void make_speed_smaller() override;
	void set_speed(double speed);
	void set_automove(bool automove);
private:


	double shape_speed = 0.1;
	sf::Keyboard::Key last_direction = sf::Keyboard::A;
	bool automove = false;
	rectangle_shape(Help_Class);
	static rectangle_shape prototype;
	std::size_t getPointCount() const override;
	Vector2f getPoint(std::size_t index) const override;
	void add_shape(base_shape* shape) override;
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
	size_of_shape shape_size;
	Vector2f size;
	sf::Color shape_color = sf::Color::Blue;
	float shape_positionX = 100.f;
	float shape_positionY = 100.f;
	float shape_scaleX = 1.f;
	float shape_scaleY = 1.f;
};