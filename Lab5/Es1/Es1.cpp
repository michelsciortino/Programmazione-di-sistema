// Es1.cpp: definisce il punto di ingresso dell'applicazione console.
//

#include "stdafx.h"
#include "message_loop.h"
#include <iostream>
#include <memory>


typedef std::packaged_task<void()> task;
int main() {
	message_loop ml;
	ml.startup();
	

	for (int i = 0; i < 10; i++) {
		auto t1 = std::make_shared< task >([]()
		{
			std::cout << "second message\n";
			throw 1;
		});
		auto t3 = std::make_shared< task >([]()
		{
			std::cout << "third message\n";
		});
		auto t2 = std::make_shared< task >([&ml, t3]()
		{
			std::cout << "first message\n";
			ml.post_delayed(t3, std::chrono::milliseconds(1500));
		});

		ml.post_delayed(t1, std::chrono::milliseconds(1000));
		ml.post_task(t2);

		auto f1 = t1->get_future();
		try
		{
			f1.get();
		}
		catch (...) {
			std::cout << "Exception caught in t1\n";
		}
	}


	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	ml.shutdown();
}