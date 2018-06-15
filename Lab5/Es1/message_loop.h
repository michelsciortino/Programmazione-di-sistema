#pragma once
#include <memory>
#include <future>
#include <queue>
#include <mutex>
#include <thread>
#include <vector>

class message {
public:
	std::shared_ptr<std::packaged_task<void()>> task_pointer;
	std::chrono::system_clock::time_point start_time;
};

class message_loop
{
	class message_comparator {
	public:
		bool operator()(const message& m1, const message& m2) {
			return (m1.start_time > m2.start_time);
		}
	};

private:
	std::thread messages_dequeuer;
	std::priority_queue<message,std::vector<message>,message_comparator> tasks_queue;
	std::mutex tasks_queue_mutex;
	std::condition_variable cv;
	bool is_running = false;
	bool can_run = false;

	void MessagesDequeuer();

public:
	~message_loop();
	void startup();
	void shutdown();
	void post_task(std::shared_ptr< std::packaged_task<void()> > pt);
	void post_delayed(std::shared_ptr< std::packaged_task<void()> > pt, std::chrono::milliseconds delay);
};

