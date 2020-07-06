#pragma once
#include "Base_Shape.h"
#include "SFML/Graphics.hpp"

class simple_shape : public base_shape
{
public:

	simple_shape(float radius = 100, std::size_t pointCount = 3, sf::Color color = sf::Color::Blue, float positionX = 100.f, float positionY = 100.f, float scaleX = 1.f, float scaleY = 1.f, float setOrX = 100.f, float setOrY = 100.f);
	simple_shape(const simple_shape& composite_shape);
	~simple_shape() {
	
	};

	std::string get_data_to_save() override;
	void resize() override;
	void movement(sf::RenderWindow& window) override;
	void draw_shape(sf::RenderWindow& window) const override;
	void collision_color_change() override;
	void auto_movement(sf::RenderWindow& window) override;
	bool select_shape(sf::RenderWindow& window) override;
	void paint_it_red() override;
	base_shape* clone() override;
	void set_radius_and_point_count(float radius, std::size_t pointCount);
	void make_speed_bigger() override;
	void change_automove() override;
	void make_speed_smaller() override;
	void set_scale(float _scale) override;
	void set_speed(double speed);
	void set_automove(bool automove);
	float get_radius() const;

	using Transformable::setPosition;
	using Transformable::setOrigin;
private:
	simple_shape(Help_Class);
	static simple_shape prototype;
	std::size_t getPointCount() const override;
	Vector2f getPoint(std::size_t index) const override;
	void add_shape(base_shape* shape) override;
	using Transformable::getPosition;
	using Transformable::getRotation;
	using Transformable::getScale;
	using Transformable::getOrigin;
	using Transformable::getTransform;
	using Transformable::getInverseTransform;


	double shape_speed = 0.1;
	sf::Keyboard::Key last_direction = sf::Keyboard::A;
	bool automove = false;

	enum size_of_shape
	{
		small,
		medium,
		big
	};

	float scale = 1.f;
	size_of_shape shape_size;
	float       radius;   
	std::size_t pointCount;
	sf::Color shape_color;
	float shape_positionX;
	float shape_positionY;
	float shape_scaleX;
	float shape_scaleY;
	float shape_setOrX;
	float shape_setOrY;
};
