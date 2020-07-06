#include "pch.h"
#include "simple_shape.h"
#include <sstream>
#include "rectangle_shape.h"
#include "shape_container.h"
#include "CareTaker.h"
shape_container::shape_container()
{
	all_shapes = new std::vector<base_shape*>();
	selected_shape = nullptr;
}

shape_container::~shape_container()
{
	clear_all();
}

sf::Color shape_container::get_color_by_string(std::string index)
{
	if(index == "4294967295")
		return sf::Color::White;
	else if (index == "4278255615")
		return sf::Color::Magenta;
	else if (index == "16711935")
		return sf::Color::Green;
	else if (index == "4294902015")
		return sf::Color::Yellow;
	else throw std::runtime_error("Unknown color");
}

Memento * shape_container::save_state()
{
	std::string scene_data("ALL " + std::to_string(all_shapes->size()) + " \n");

	for (auto shape : *all_shapes) {
		scene_data +=shape->get_data_to_save();
	}
	scene_data +="SELECTED\n";
	scene_data +=selected_shape->get_data_to_save();
	Memento* scene_memento = new Memento(scene_data);
	return scene_memento;
}

void shape_container::load_state(Memento * memento)
{
	clear_all();
	clear_selected();
	std::fstream stream;
	stream.open(memento->get_filename());
	std::string tmp_str;
	std::vector<std::string> all_strings;
	std::vector<std::string> words;
	while (std::getline(stream, tmp_str))
		all_strings.push_back(tmp_str);

	std::stringstream tmp_stream;
	tmp_stream << all_strings[0];
	while (std::getline(tmp_stream, tmp_str, ' '))
		words.push_back(tmp_str);
	int tmp_count = std::stoi(words[1]);
	int i;
	int string_number = 0;
	for (i = 1; i <= tmp_count; ++i) {
		string_number++;
		tmp_stream.clear();
		words.clear();
		tmp_stream << all_strings[string_number];
		while (std::getline(tmp_stream, tmp_str, ' '))
			words.push_back(tmp_str);
		if (words[0] == "simple_shape") {
			base_shape* tmp_shape = base_shape::create_shape(Simple_Shape_ID);
			dynamic_cast<simple_shape*>(tmp_shape)->set_radius_and_point_count(std::stof(words[1]), std::stoi(words[2]));
			tmp_shape->setFillColor(get_color_by_string(words[3]));
			tmp_shape->setPosition(std::stof(words[4]), std::stoi(words[5]));
			tmp_shape->setScale(std::stof(words[6]), std::stoi(words[7]));
			all_shapes->push_back(tmp_shape);
		}
		else if (words[0] == "rectangle_shape") {
			base_shape* tmp_shape = base_shape::create_shape(Rectangle_Shape_ID);
			Vector2f size(std::stof(words[1]), std::stoi(words[2]));
			dynamic_cast<rectangle_shape*>(tmp_shape)->set_size(size);
			tmp_shape->setFillColor(get_color_by_string(words[3]));
			tmp_shape->setPosition(std::stof(words[4]), std::stoi(words[5]));
			tmp_shape->setScale(std::stof(words[6]), std::stoi(words[7]));
			all_shapes->push_back(tmp_shape);
		}
		else if (words[0] == "composite_shape") {
			int iterations_count = std::stoi(words[1]);
			base_shape* new_composite = new composite_shape();
			for (int j = 0; j < iterations_count; ++j) {
				++string_number;
				tmp_stream.clear();
				words.clear();
				tmp_stream << all_strings[string_number];
				while (std::getline(tmp_stream, tmp_str, ' '))
					words.push_back(tmp_str);
				if (words[0] == "simple_shape") {
					base_shape* tmp_shape = base_shape::create_shape(Simple_Shape_ID);
					dynamic_cast<simple_shape*>(tmp_shape)->set_radius_and_point_count(std::stof(words[1]), std::stoi(words[2]));
					tmp_shape->setFillColor(get_color_by_string(words[3]));
					tmp_shape->setPosition(std::stof(words[4]), std::stoi(words[5]));
					tmp_shape->setScale(std::stof(words[6]), std::stoi(words[7]));
					new_composite->add_shape(tmp_shape);
				}
				else if (words[0] == "rectangle_shape") {
					base_shape* tmp_shape = base_shape::create_shape(Rectangle_Shape_ID);
					Vector2f size(std::stof(words[1]), std::stoi(words[2]));
					dynamic_cast<rectangle_shape*>(tmp_shape)->set_size(size);
					tmp_shape->setFillColor(get_color_by_string(words[3]));
					tmp_shape->setPosition(std::stof(words[4]), std::stoi(words[5]));
					tmp_shape->setScale(std::stof(words[6]), std::stoi(words[7]));
					new_composite->add_shape(tmp_shape);
				}
				else if (words[0] == "composite_shape") {
					int iterat_count = std::stoi(words[1]);
					base_shape* inclosed_composite = new composite_shape();
					for (int k = 0; k < iterat_count; ++k) {
						++string_number;
						tmp_stream.clear();
						words.clear();
						tmp_stream << all_strings[string_number];
						while (std::getline(tmp_stream, tmp_str, ' '))
							words.push_back(tmp_str);
						if (words[0] == "simple_shape") {
							base_shape* tmp_shape = base_shape::create_shape(Simple_Shape_ID);
							dynamic_cast<simple_shape*>(tmp_shape)->set_radius_and_point_count(std::stof(words[1]), std::stoi(words[2]));
							tmp_shape->setFillColor(get_color_by_string(words[3]));
							tmp_shape->setPosition(std::stof(words[4]), std::stoi(words[5]));
							tmp_shape->setScale(std::stof(words[6]), std::stoi(words[7]));
							inclosed_composite->add_shape(tmp_shape);
						}
						else if (words[0] == "rectangle_shape") {
							base_shape* tmp_shape = base_shape::create_shape(Rectangle_Shape_ID);
							Vector2f size(std::stof(words[1]), std::stoi(words[2]));
							dynamic_cast<rectangle_shape*>(tmp_shape)->set_size(size);
							tmp_shape->setFillColor(get_color_by_string(words[3]));
							tmp_shape->setPosition(std::stof(words[4]), std::stoi(words[5]));
							tmp_shape->setScale(std::stof(words[6]), std::stoi(words[7]));
							inclosed_composite->add_shape(tmp_shape);
						}
					}
					new_composite->add_shape(inclosed_composite);
				}
			}
				all_shapes->push_back(new_composite);
		}
	}
	++string_number;
	tmp_stream.clear();
	words.clear();
	tmp_stream << all_strings[++string_number];
	selected_shape = new composite_shape();
	while (std::getline(tmp_stream, tmp_str, ' '))
		words.push_back(tmp_str);
	tmp_count = std::stoi(words[1]); 
	for (int j = 0; j < tmp_count; ++j) {
		tmp_stream.clear();
		words.clear();
		tmp_stream << all_strings[++string_number];
		while (std::getline(tmp_stream, tmp_str, ' '))
			words.push_back(tmp_str);
		if (words[0] == "simple_shape") {
			base_shape* tmp_shape = base_shape::create_shape(Simple_Shape_ID);
			dynamic_cast<simple_shape*>(tmp_shape)->set_radius_and_point_count(std::stof(words[1]), std::stoi(words[2]));
			tmp_shape->setFillColor(get_color_by_string(words[3]));
			tmp_shape->setPosition(std::stof(words[4]), std::stoi(words[5]));
			tmp_shape->setScale(std::stof(words[6]), std::stoi(words[7]));
			selected_shape->add_shape(tmp_shape);
		}
		else if (words[0] == "rectangle_shape") {
			base_shape* tmp_shape = base_shape::create_shape(Rectangle_Shape_ID);
			Vector2f size(std::stof(words[1]), std::stoi(words[2]));
			dynamic_cast<rectangle_shape*>(tmp_shape)->set_size(size);
			tmp_shape->setFillColor(get_color_by_string(words[3]));
			tmp_shape->setPosition(std::stof(words[4]), std::stoi(words[5]));
			tmp_shape->setScale(std::stof(words[6]), std::stoi(words[7]));
			selected_shape->add_shape(tmp_shape);
		}
		else if (words[0] == "composite_shape") {
			int iterations_count = std::stoi(words[1]);
			base_shape* new_composite = new composite_shape();
			for (int k = 0; k < iterations_count; ++k) {
				++string_number;
				tmp_stream.clear();
				words.clear();
				tmp_stream << all_strings[string_number];
				while (std::getline(tmp_stream, tmp_str, ' '))
					words.push_back(tmp_str);
				if (words[0] == "simple_shape") {
					base_shape* tmp_shape = base_shape::create_shape(Simple_Shape_ID);
					dynamic_cast<simple_shape*>(tmp_shape)->set_radius_and_point_count(std::stof(words[1]), std::stoi(words[2]));
					tmp_shape->setFillColor(get_color_by_string(words[3]));
					tmp_shape->setPosition(std::stof(words[4]), std::stoi(words[5]));
					tmp_shape->setScale(std::stof(words[6]), std::stoi(words[7]));
					new_composite->add_shape(tmp_shape);
				}
				else if (words[0] == "rectangle_shape") {
					base_shape* tmp_shape = base_shape::create_shape(Rectangle_Shape_ID);
					Vector2f size(std::stof(words[1]), std::stoi(words[2]));
					dynamic_cast<rectangle_shape*>(tmp_shape)->set_size(size);
					tmp_shape->setFillColor(get_color_by_string(words[3]));
					tmp_shape->setPosition(std::stof(words[4]), std::stoi(words[5]));
					tmp_shape->setScale(std::stof(words[6]), std::stoi(words[7]));
					new_composite->add_shape(tmp_shape);
				}
			}
			selected_shape->add_shape(new_composite);
		}
	}
}

bool shape_container::select_shape(sf::RenderWindow & window)
{
	sf::Vector2f mouse_position;
	mouse_position.x = sf::Mouse::getPosition(window).x;
	mouse_position.y = sf::Mouse::getPosition(window).y;

	for (auto shape = all_shapes->rbegin(); shape != all_shapes->rend(); ++shape)
	{
		bool exist = false;
			if ((*shape)->select_shape(window))
			{
				exist = true;
			}
		if (exist) {
			if (selected_shape == nullptr) {
				selected_shape = new composite_shape();
				base_shape * tmp_shape = (*shape)->clone();
				selected_shape->add_shape(tmp_shape);
			}
			else {
				selected_shape = new composite_shape(*dynamic_cast<composite_shape*>(selected_shape));
				base_shape * tmp_shape = (*shape)->clone();
				selected_shape->add_shape(tmp_shape);
				//all_shapes->insert(all_shapes->begin(), selected_shape);
				all_shapes->push_back(selected_shape);
			}
			return true;
		}
	}
	return false;
}



void shape_container::collision_color_change()
{
	if (selected_shape != nullptr) {
		selected_shape->collision_color_change();
	}
}

void shape_container::clear_all()
{
	for (auto shape : *all_shapes) {
		if (shape != nullptr) 
			delete shape;
	}
	all_shapes->clear();
	clear_selected();
}

void shape_container::clear_selected()
{
		selected_shape = nullptr;
}

void shape_container::add_to_all(base_shape * new_shape)
{
	all_shapes->push_back(new_shape);
}

void shape_container::add_to_selected(base_shape* new_shape)
{
	if (selected_shape != nullptr) {
		selected_shape->add_shape(new_shape);
	}
	else {
		selected_shape = new composite_shape();
		selected_shape->add_shape(new_shape);
	}
}

std::vector<base_shape*>* shape_container::get_all_shapes()
{
	return all_shapes;
}

base_shape * shape_container::get_selected_shape()
{
	return selected_shape;
}
