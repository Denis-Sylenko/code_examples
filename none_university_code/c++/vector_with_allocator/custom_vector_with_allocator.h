#pragma once
#include <memory>
namespace MyLib
{
	template <
		typename T,
		template <typename Y> class Allocator = std::allocator
	>
		class Vector
	{
	public:
		typedef Allocator<T> AllocatorType;
		typedef Vector<T, Allocator> VectorType;
	public:
		explicit Vector(const AllocatorType& allocator = AllocatorType()) : _capacity(0), _size(0), _allocator(allocator), raw_pointer(nullptr) {
			reserve(1);
		};

		Vector(
			const std::initializer_list<T>& values,
			const AllocatorType& allocator = AllocatorType()
		) {
			_allocator = allocator;
			reserve(1);
			std::copy(values.begin(), values.end(), begin());
			_size = values.size();
		};

		~Vector() {
			clear();
			_capacity = 0; 
			_size = 0;
		};

		Vector(const Vector& rhs) : _capacity(rhs._capacity), _size(0), _allocator(rhs._allocator), raw_pointer(_allocator.allocate(rhs._capacity)) {
			for (size_t i = 0; i < rhs._size; i++) {
				push_back(rhs[i]);
			}
		};
		Vector(Vector&& rhs) noexcept : _capacity(rhs._capacity), _size(rhs._size), _allocator(rhs._allocator), raw_pointer(rhs.raw_pointer) {
			rhs.raw_pointer = nullptr;
			rhs._size = rhs._capacity = 0;
		};

		Vector& operator = (const Vector& rhs) {
			clear();

			_capacity = rhs._capacity;
			_size = 0;
			_allocator = rhs._allocator;
			raw_pointer = _allocator.allocate(_capacity);

			for (size_t i = 0; i < rhs._size; i++) {
				push_back(rhs[i]);
			}

			return *this;
		};
		Vector& operator = (Vector&& rhs) {
			clear();

			_capacity = rhs._capacity;
			_size = rhs._size;
			_allocator = rhs._allocator;
			raw_pointer = rhs.raw_pointer;
			rhs.raw_pointer = nullptr;
			rhs._size = rhs._capacity = 0;

			return *this;
		};


		void clear() {
			for (int i = 0; i < _size; ++i) {
					_allocator.destroy(raw_pointer + i);
				}
				_allocator.deallocate(raw_pointer, _capacity);
		}	

		T& operator [](std::size_t i) noexcept { if(_size > i) return *(raw_pointer + i); }; //Проверка добавлена, чтоб функция не кидала исключение в случае выхода индекса за пределы 
		const T& operator [](std::size_t i) const noexcept { if (_size > i) return *(raw_pointer + i); };

	

		void push_back(const T& value) {
			
			if (_size == _capacity) {
				reserve(_capacity * 2);
			}
			_allocator.construct(raw_pointer + _size, value);
			++_size;

			
		};
		void push_back(T&& value) {
			if (_size == _capacity) {
				reserve(_capacity * 2);
			}
			_allocator.construct(raw_pointer + _size, std::move(value));
			++_size;
		};

		void pop_back() {
			if (_size) {
				_allocator.destroy(raw_pointer+_size-1);
				--_size;
			}
		};

		void resize(std::size_t size) {
			if (size > _size) {
				for (int i = _size + 1; i <= size; ++i) {
					push_back(T());
				}
			}
			else {
				for (int i = size; i < _size; ++i) {
					pop_back();
				}
			}
		};

		void reserve(std::size_t capacity) {
			if (capacity > _capacity) {
			  T* new_raw_pointer = _allocator.allocate(capacity);
				std::move(begin(), end(), new_raw_pointer);

				clear();

				_capacity = capacity;
				raw_pointer = new_raw_pointer;

				new_raw_pointer = nullptr;
				}
		}

		T* data() noexcept { return raw_pointer; }

		const T* data() const noexcept { return raw_pointer; }

		std::size_t size() const noexcept {return _size;}

		std::size_t capacity() const noexcept { return _capacity; }

		bool empty() const noexcept { return _size == 0; }

		T* begin() { return raw_pointer; }

		T* end() { return raw_pointer + _size; }

	private:
		std::size_t _capacity;
		std::size_t _size;
		AllocatorType _allocator;
		T* raw_pointer; //В задании было сказано, что можно аккуратно использовать сырой указатель 
	};
}
