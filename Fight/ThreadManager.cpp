#include "ThreadManager.h"



ThreadManager::ThreadManager()
{
}


ThreadManager::~ThreadManager()
{
	for (std::thread * thread : n_threads)
	{
		thread->join();
	}
}

void ThreadManager::addThread(const std::function <void(World*)>& f, World * world)
{
	n_threads.push_back(new std::thread(f, world));
}