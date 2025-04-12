#ifndef PROCESS_MANAGEMENT_HPP
#define PROCESS_MANAGEMENT_HPP

#include "Task.hpp"
#include <queue>
#include <memory>
#include <semaphore.h>
#include <mutex>
#include <atomic>

/*
std::unique_ptr<int[]> arr = std::make_unique<int[]>(size);
std::unique_ptr<int[]> arr1 = std::move(arr);

move(var_name) => moves the ownership to other
pros of this way to allocate mem:
	-> ownership belongs to only one ptr at any instance
	-> memory is free only one time by any one
	-> scope limited (auto free mem if out of scope)
*/
class ProcessManagement {
private:
	// std::queue<std::unique_ptr<Task>> taskQueue;

	// making shared memory queue
	// shared memory: memory block that shared to different process through a pointer
	struct SharedMemory {
		std::atomic<int> size; // one can access at a time
		char tasks[1000][256];
		int front;
		int rear;
		void printSharedMemory() {
			std::cout << size.load() << std::endl;
			std::cout << front << std::endl;
			std::cout << rear << std::endl;
		}
	};
	SharedMemory* sharedMem;
	int shmFd;
	const char* SHM_NAME = "/my_queue";

	sem_t* itemsSemaphore;
	sem_t* empty_Semaphore;
	std::mutex queueLock;

public:
	ProcessManagement();
	~ProcessManagement();
	bool submitToQueue(std::unique_ptr<Task> task);
	void executeTasks();
};

#endif