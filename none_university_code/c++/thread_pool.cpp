//#include "pch.h"
#include <condition_variable>
#include <functional>
#include <iostream>
#include <future>
#include <vector>
#include <thread>
#include <queue>

class SimpleThreadPool
{
public:

	explicit SimpleThreadPool(std::size_t threadCount);

	~SimpleThreadPool();

	SimpleThreadPool(const SimpleThreadPool&) = delete;
	SimpleThreadPool& operator=(const SimpleThreadPool&) = delete;

	template <typename Fnc_T>
	auto Post(Fnc_T task)->std::future<decltype(task())>;
	void WorkOn();

	void Destroy();
private:

	size_t m_threadCount;

	std::vector<std::thread> threads;

	std::queue<std::function<void()>> tasks;

	std::condition_variable condition;

	std::mutex mut;

	bool stop;
};




SimpleThreadPool::SimpleThreadPool(std::size_t threadCount)
{
	for (size_t i = 0; i < threadCount; ++i)
		threads.emplace_back(std::thread(&SimpleThreadPool::WorkOn, this));
}

SimpleThreadPool::~SimpleThreadPool()
{
	Destroy();
}

template <typename Fnc_T>
auto SimpleThreadPool::Post(Fnc_T task)->std::future<decltype(task())>
{
	auto wrapper = std::make_shared<std::packaged_task<decltype(task()) ()>>(std::move(task));

	{
		std::unique_lock<std::mutex> lock{ mut };
		tasks.emplace([=] {
			(*wrapper)();
		});
	}

	condition.notify_one();
	return wrapper->get_future();
}

void SimpleThreadPool::WorkOn()
{
	while (true)
	{
		std::function<void()> task; task;

		{
			std::unique_lock<std::mutex> lock{ mut };

			condition.wait(lock, [=] { return stop || !tasks.empty(); });

			if (stop && tasks.empty())
				break;

			task = std::move(tasks.front());
			tasks.pop();
		}

		task();
	}

}

void SimpleThreadPool::Destroy()
{
	{
		std::unique_lock<std::mutex> lock{ mut };
		stop = true;
	}

	condition.notify_all();

	for (std::thread &thread : threads)
		thread.join();
}
