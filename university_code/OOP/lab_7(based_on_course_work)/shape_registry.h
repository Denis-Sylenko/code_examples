#pragma once
class shape_registry
{
private:
	shape_registry() {}
	shape_registry(const shape_registry&) = delete;
	shape_registry& operator=(shape_registry&) = delete;
public:
	static shape_registry& getInstance() {
		static shape_registry  instance;
		return instance;
	}
};