// AtomicTests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <iostream>

#include "Spinlock.h"

struct Object
{
	int data = 1337;
	Spinlock lock_;
};

int main()
{
	Object obj;
	int data = 1337;

	//std::thread t1([&] { while (true) { obj.lock_.Lock(); std::cout << "t1pre:" << obj.data << std::endl; obj.data = -1; std::cout << "t1:" << obj.data << std::endl; obj.lock_.Unlock(); }});
	//std::thread t2([&] { while (true) { obj.lock_.Lock(); std::cout << "t2pre:" << obj.data << std::endl; obj.data = 99999; std::cout << "t2:" << obj.data << std::endl;  obj.lock_.Unlock(); }});

	std::thread t1([&] { while (true) { SpinlockGuard guard(obj.lock_); std::cout << "t1pre:" << obj.data << std::endl; obj.data = -1; std::cout << "t1:" << obj.data << std::endl; }});
	std::thread t2([&] { while (true) { SpinlockGuard guard(obj.lock_); std::cout << "t2pre:" << obj.data << std::endl; obj.data = 99999; std::cout << "t2:" << obj.data << std::endl; }});

	t1.detach();
	t2.detach();

	while (true){};

    std::cout << "Hello World!\n"; 
}