#include "stdafx.h"
#include "message_loop.h"

message_loop::~message_loop()
{
	shutdown();
}

void message_loop::startup()
{
	std::unique_lock<std::mutex> ul(tasks_queue_mutex);
	if (is_running == false)
	{
		can_run = true;
		messages_dequeuer = std::thread(&message_loop::MessagesDequeuer, this);
		is_running = true;
	}
}

void message_loop::shutdown()
{
	std::unique_lock<std::mutex> ul(tasks_queue_mutex);
	if (is_running == true)
	{
		can_run = false;
		ul.unlock();
		cv.notify_one();
		messages_dequeuer.join();
	}
	while (tasks_queue.size() > 0)
		tasks_queue.pop();
	is_running = false;
}

void message_loop::post_task(std::shared_ptr<std::packaged_task<void()>> pt)
{
	message new_task;
	new_task.start_time = std::chrono::system_clock::now();
	new_task.task_pointer = pt;

	std::unique_lock<std::mutex> ul(tasks_queue_mutex);
	tasks_queue.push(new_task);
	cv.notify_one();
}

void message_loop::post_delayed(std::shared_ptr<std::packaged_task<void()>> pt, std::chrono::milliseconds delay)
{
	message new_task;
	new_task.start_time = std::chrono::system_clock::now() + delay;
	new_task.task_pointer = pt;

	std::unique_lock<std::mutex> ul(tasks_queue_mutex);
	tasks_queue.push(new_task);
	cv.notify_one();
}

void message_loop::MessagesDequeuer()
{
	std::shared_ptr<std::packaged_task<void()>> task;
	std::chrono::system_clock::time_point  awake_point;
	while (true)
	{
		std::unique_lock<std::mutex> queue_ul(tasks_queue_mutex);

		if (can_run == false) return;

		awake_point = std::chrono::system_clock::time_point::max();
		//if the task queue is not empty
		if (!tasks_queue.empty())
			awake_point= tasks_queue.top().start_time;

		//waiting until awake_point || notify received
		cv.wait_until(queue_ul, awake_point);

		//if notified by shutdown
		if (can_run == false)
			return;

		//if not notified by a "spuria" notification and the first queue task is executable
		if (!tasks_queue.empty() && tasks_queue.top().start_time <= std::chrono::system_clock::now())
		{
			task = tasks_queue.top().task_pointer;
			tasks_queue.pop();
			queue_ul.unlock();
			(*task)();
		}
		else //spuria notification
			continue;
	}
}
