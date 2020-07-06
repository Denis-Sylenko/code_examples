#pragma once
#include <utility>
#include <thread>
#include <vector>
#include <windows.h>
#include <mutex>
#include <set>
#include <stdlib.h>
#include <time.h>
#include "Base_Shape.h"
#include "simple_shape.h"

class thread_demonstration {
public:
	thread_demonstration() {
		colors = {sf::Color::Blue, sf::Color::Green,
				  sf::Color::Cyan,sf::Color::Magenta, sf::Color::Red,
				  sf::Color::White, sf::Color::Yellow };
	}

	void set_aims() {
		aim_adder = std::thread([&]() {
			std::lock_guard<std::mutex> mut_guard(mut);
			if (shapes_vector.size() > 1) {
				for (int i = 0; i < shapes_vector.size(); ++i) {
					if (shapes_vector[i].first == -1 || shapes_vector[i].first >= shapes_vector.size()
						|| shapes_vector[i].first == i) {
						int new_aim = -1;
						while (new_aim == -1 || new_aim == i) {
							new_aim = rand() % shapes_vector.size();
						}
						shapes_vector[i].first = new_aim;
					}
				}
			}
		});
		aim_adder.detach();
	}

	void move_to_aim(sf::RenderWindow* window) {
		mover = std::thread([&]() {
			std::lock_guard<std::mutex> mut_guard(mut);
			for (int i = 0; i < shapes_vector.size(); ++i) {
				if (shapes_vector[i].first != -1) {
					int aim_index = shapes_vector[i].first;
					if (shapes_vector[aim_index].second->getPosition().x < shapes_vector[i].second->getPosition().x) {
						shapes_vector[i].second->move(-shape_speed, 0.0f);
					}
					else if (shapes_vector[aim_index].second->getPosition().x > shapes_vector[i].second->getPosition().x) {
						shapes_vector[i].second->move(shape_speed, 0.0f);
					}
					if (shapes_vector[aim_index].second->getPosition().y < shapes_vector[i].second->getPosition().y) {
						shapes_vector[i].second->move(0.0f, -shape_speed);
					}
					else if (shapes_vector[aim_index].second->getPosition().y > shapes_vector[i].second->getPosition().y) {
						shapes_vector[i].second->move(0.0f, shape_speed);
					}
				}
			}
		});
		mover.detach();
		delete_collision(window);
	}

	void delete_collision(sf::RenderWindow* window) {
		deleter = std::thread([&]() {
			std::lock_guard<std::mutex> mut_guard(mut);
			std::set<size_t> to_delete;
			for (int i = 0; i < shapes_vector.size(); ++i) {
				for (int j = 0; j < shapes_vector.size(); ++j) {
					if (shapes_vector[i].second->getGlobalBounds().intersects(shapes_vector[j].second->getGlobalBounds()) && i != j 
						&& (shapes_vector[i].first == j || shapes_vector[j].first == i)) {
						to_delete.insert(i);
						to_delete.insert(j);
					}
				}
			}
			for (auto index : to_delete) {
				delete shapes_vector[index].second;
				shapes_vector[index].second = nullptr;
			}

			shapes_vector.erase(std::remove_if(shapes_vector.begin(), shapes_vector.end(), [](const std::pair<int, simple_shape*>& elem) {
				return elem.second == nullptr;
			}), shapes_vector.end());

		});
		set_aims();
		deleter.detach();
	}


	void start_demonstration(sf::RenderWindow* window) {
		//long ltime = time(NULL);
		//unsigned int stime = (unsigned int)ltime / 2;
		//srand(stime);
		shape_adder = std::thread([&]() {
			while (true) {
				while (shapes_vector.size() < 10) {
					simple_shape* new_shape_to_add = new simple_shape();
					new_shape_to_add->setFillColor(colors[rand() % colors.size()]);
					new_shape_to_add->set_radius_and_point_count(80, rand() % 20 + 3);
					new_shape_to_add->setPosition(rand() % 1400 + 100, rand() % 780 + 100);
					{
						std::lock_guard<std::mutex> mut_guard(mut);
						shapes_vector.push_back({-1, new_shape_to_add });
					}
					set_aims();
					Sleep(50);
				}
			}
		});

		shape_adder.detach();
	}

	void draw(sf::RenderWindow* window) {
		std::lock_guard<std::mutex> mut_guard(mut);
		for (auto shape : shapes_vector) {
				shape.second->draw_shape(*window);
		}
	}
private:
	std::thread shape_adder;
	std::thread aim_adder;
	std::thread mover;
	std::thread deleter;
	std::vector<std::pair<int, simple_shape*>> shapes_vector;
	std::vector<sf::Color> colors;
	std::mutex mut;
	float shape_speed = 0.2;
};