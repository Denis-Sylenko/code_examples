#include "pch.h" //для Visual Studio
#include <iostream>


template<typename Resource>
class WeakPtr;

class Counter {//Вспомогательный класс, поля которого будут содержать колличество сильных и слабых ссылок
public: 
	Counter(){
		use_count = 0;
		weak_count = 0;
	};
	long use_count;
	long weak_count;
};

template <typename Resource>
class SharedPtr
{

public:
	friend WeakPtr<Resource>;//Для удобства
		SharedPtr() {//Создается пустой SharedPtr
		pointer = nullptr;
		count = nullptr;
	};

	explicit SharedPtr(Resource* res) { //Создается SharedPtr, указывающий на переданный ресурс
		pointer = res;
		count = new Counter(); 
		count->use_count++;
		count->weak_count++;//Появление первой сильной ссылки влечет за собой увеличение кол-ва слабых на единицу
	};

	SharedPtr(const SharedPtr<Resource>& rhs) {
		pointer = rhs.pointer;
		count = rhs.count;
		if (pointer != nullptr) {
			count->use_count++; //Поскольку создается копия мы инкрементируем кол-во сильных ссылок
		}
	};

	~SharedPtr() {
		if (count != nullptr) { //Чтоб не удалять из пустого объекта
			if (--(count->use_count) == 0) {
				count->weak_count--;
				if (count->weak_count == 0) { delete count; count = nullptr; std::cout << "Counter was destructed" << std::endl; }  //cout нужен только для демонстративности
				delete pointer;
				pointer = nullptr;
				std::cout << "Pointer was destructed" << std::endl; //cout нужен только для демонстративности
			}
		}
	};

	SharedPtr<Resource>& operator=(const SharedPtr<Resource>& rhs) {
		if (this != &rhs) { //Если это не тот же объект
		Reset();
		pointer = rhs.pointer;
		count = rhs.count;
		if (count != nullptr) {
			count->use_count++;
		};
		}

	};

	void Reset() {
		SharedPtr().Swap(*this);
	};

	void Reset(Resource* res) {
		Reset();
		pointer = res->pointer;
		count = res->count;
	};

	void Swap(SharedPtr<Resource>& rhs) {
		std::swap(pointer, rhs.pointer);
		std::swap(count, rhs.count);
	};

	Resource* get() const {
		return pointer;
	};

	Resource& operator*() const {
		return *pointer;
	};

	Resource* operator->() const {
		return pointer;
	};

	long UseCount() const {
		return count->use_count;
	};

private:
	Resource* pointer;
	Counter* count;
};


template<typename Resource>
class WeakPtr

{

public:

	WeakPtr(): pointer(nullptr), count(nullptr){
	};//Создаем новый WeakPtr с пустыми полями

	WeakPtr(const WeakPtr<Resource>& rhs) : pointer(rhs.pointer),count(rhs.count) { //Создается новый WeakPtr, который ссылается на тот же указатель, что и rhs. 
		if (count != nullptr) {//Если rhs имел непустые поля
			count->weak_count++; // Колличество слабых ссылок на него инкрементируется
		}//Иначе мы просто получим еще один пустой WeakPtr
	};

	WeakPtr(const SharedPtr<Resource>& rhs) : pointer(rhs.pointer), count(rhs.count) { //Создается новый WeakPtr, который ссылается на объект, находящийся под контролем rhs. 
		if (count != nullptr) {//Если rhs имел непустые поля
			count->weak_count++;// Колличество слабых ссылок на него инкрементируется
		}//Иначе мы просто получим пустой WeakPtr
	};

	~WeakPtr() {
		if (count != nullptr) { //Проверка нужна, чтоб не удалять уже пустой объект
			if ((--(count->weak_count) == 0) && count->use_count == 0) {
				delete count; count = nullptr; 	std::cout << "Counter was destructed" << std::endl;  //cout нужен только для демонстративности
			}
		}	//Уменьшаем колличество слабых ссылок на объект и удаляем Counter, если это была последняя слабая ссылка и нет сильных ссылок
	};

	WeakPtr<Resource>& operator=(const WeakPtr<Resource>& rhs) {
		if (this !=&rhs) {
			Reset();
			pointer = rhs.pointer;//Теперь присваиваем текущему объекту значение полей переданного 
			count = rhs.count;
			if (count != nullptr) {
				count->weak_count++;//Инкрементируем кол-во слабых ссылок на него
			}
			return *this;
		}
	};

	WeakPtr<Resource>& operator=(const SharedPtr<Resource>& rhs) {//Аналогичные действия
		Reset();
		pointer = rhs.pointer;
		count = rhs.count;
		if (count != nullptr) {
			count->weak_count++;
		}
		return *this;
	};

	void Reset() {//Меняем поля текущего объекта с полями временного. В следствии чего у текущего останутся значения по умолчанию, а временный разрушится и вызовет деструктор. 
		WeakPtr().Swap(*this);
	};

	void Swap(WeakPtr<Resource>& rhs) {//Никогда не бросит исключение 
		std::swap(pointer, rhs.pointer);
		std::swap(count, rhs.count);
	};

	long UseCount() const {
		return count->use_count;
	}

	bool Expired() const {//Проверяет, был ли удален объект, на который ссылался SharedPtr
		return count->use_count == 0;
	};

	SharedPtr<Resource> Lock() const {
		if (Expired()) {//Если элемент уже был удален - вернет пустой SharedPtr
			return SharedPtr<Resource>();
		}
		try { //Для многопоточных программ
			SharedPtr<Resource> tmp(pointer); // Иначе создаст новый SharedPtr, ссылающийся на этот объект
			count->use_count++;
			tmp.count =count;
			return tmp;
		}
		catch (std::exception&) {
			return SharedPtr<Resource>();
		}
	};
private:
	Resource* pointer;
	Counter* count;
};
int main()
{
	int* a = new int(10);
	SharedPtr<int> sp(a); //Конструктор, принимающий сырой указатель
	SharedPtr<int> s_sp(sp);//Конструктор копирования SharedPtr
	WeakPtr<int> wp = sp;//Оператор присваивания с параметром SharedPtr
	WeakPtr<int> s_wp = wp;//Оператор присваивания с параметром WeakPtr
	WeakPtr<int> t_wp(s_wp);//Конструктор копирования WeakPtr
	std::cout << sp.get() << " * " << s_wp.Lock().get() << std::endl;//Методы Lock и get.
	if (t_wp.Expired()) {
		std::cout << "Pointer was deleted" << std::endl;
	} else std::cout << "Pointer was not deleted" << std::endl;
	std::cout << "Use count before weak reset: " << wp.UseCount();
	wp.Reset(); //Методы Reset для SharedPtr и WeakPtr. Они внутри себя вызывают Swap;
	std::cout << std::endl << "Use count after weak reset: " << s_sp.UseCount();
	sp.Reset();
	std::cout << std::endl <<  "Use count after shared reset: " << s_sp.UseCount() << std::endl;
	return 0;
};

