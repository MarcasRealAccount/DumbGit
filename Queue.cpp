#include <mutex>
#include <thread>
#include <deque>
#include <iostream>

struct Data
{
	std::string str;
};

void workerThread(std::deque<Data>& datas, std::mutex& datasMutex, bool& alive)
{
	while (alive)
	{
		while (alive && datas.empty())
		{
			using namespace std::chrono_literals;
			std::this_thread::sleep_for(10ms);
		}

		if (!alive)
			return;

		Data data;
		{
			std::lock_guard<std::mutex> guard{ datasMutex };
			data = datas.back();
			datas.pop_back();
		}

		std::cout << data.str;
	}
}

int main()
{
	std::deque<Data> datas;
	std::mutex datasMutex;
	bool alive = true;

	std::thread thread{ &workerThread, std::ref(datas), std::ref(datasMutex), std::ref(alive) };

	for (std::size_t i = 0; i < 10; ++i)
	{
		using namespace std::chrono_literals;
		datas.push_front(Data{ std::to_string(i) + " Nices\n" });
		std::this_thread::sleep_for(50ms);
	}

	{
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(1s);
	}

	alive = false;
	thread.join();
}