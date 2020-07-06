#pragma once
#include <vector>
#include "Base_Shape.h"
#include "SFML/Graphics.hpp"
#include "composite_shape.h"
#include "CareTaker.h"
class shape_container{
public:
	shape_container();
	~shape_container();
	sf::Color get_color_by_string(std::string index);
	Memento * save_state();
	void load_state(Memento *mem);
	bool select_shape(sf::RenderWindow& window);
	void collision_color_change();
	void clear_all();
	void clear_selected();
	void add_to_all(base_shape* new_shape);
	void add_to_selected(base_shape* new_shape);
	std::vector<base_shape*>* get_all_shapes();
	base_shape* get_selected_shape();
private:
	std::vector<base_shape*>* all_shapes;
	base_shape* selected_shape;
};