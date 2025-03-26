#ifndef PROCESS_MANAGEMENT_HPP
#define PROCESS_MANAGEMENT_HPP

#include "Task.hpp"
#include <queue>
#include <memory>

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
	std::queue<std::unique_ptr<Task>> taskQueue;

public:
	ProcessManagement();
	bool submitToQueue(std::unique_ptr<Task> task);
	void executeTasks();

};

#endif