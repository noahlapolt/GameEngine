#pragma once
#include <vector>
#include <thread>

#include "World.h"

class ThreadManager
{
public:
	ThreadManager();
	~ThreadManager();

	void addThread(const std::function <void(World*)>& f, World * world);

private:
	std::vector<std::thread*> n_threads;
};

