#include "ProcessManagement.hpp"
#include <iostream>
#include <cstring>
#include <sys/wait.h>
#include "../encryptDecrypt/Cryption.hpp"
#include <unistd.h>
#include <sys/mman.h>
#include <atomic>
#include <sys/fcntl.h>
#include <semaphore.h>

ProcessManagement::ProcessManagement() {
	itemsSemaphore = sem_open("/items_semaphore", O_CREAT, 0666, 0);
	if (itemsSemaphore == SEM_FAILED) {
		perror("sem_open itemsSemaphore");
		exit(1);
	}

	empty_Semaphore = sem_open("/empty_slots_semaphore", O_CREAT, 0666, 1000);
	if (empty_Semaphore == SEM_FAILED) {
		perror("sem_open empty_Semaphore");
		exit(1);
	}

	shmFd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
	if (shmFd == -1) {
		perror("shm_open");
		exit(1);
	}

	if (ftruncate(shmFd, sizeof(SharedMemory)) == -1) {
		perror("ftruncate");
		exit(1);
	}

	sharedMem = static_cast<SharedMemory*> (mmap(nullptr, sizeof(SharedMemory), PROT_READ | PROT_WRITE, MAP_SHARED, shmFd, 0));
	if (sharedMem == MAP_FAILED) {
		perror("mmap");
		exit(1);
	}

	sharedMem->front = 0;
	sharedMem->rear = 0;
	sharedMem->size.store(0);
}

ProcessManagement::~ProcessManagement() {
	munmap(sharedMem, sizeof(SharedMemory));
	shm_unlink(SHM_NAME);

	sem_close(itemsSemaphore);
	sem_close(empty_Semaphore);

	sem_unlink("/items_semaphore");
	sem_unlink("/empty_slots_semaphore");
}

bool ProcessManagement::submitToQueue(std::unique_ptr<Task> task) {
	// singlethreaded
	// taskQueue.push(std::move(task));
	// return true;

	// multithreaded
	sem_wait(empty_Semaphore);
	std::unique_lock<std::mutex> lock(queueLock);

	if (sharedMem->size.load() >= 1000) {
		return false;
	}
	strcpy(sharedMem->tasks[sharedMem->rear], task->toString().c_str());
	sharedMem->rear = (sharedMem->rear + 1) % 1000;
	sharedMem->size.fetch_add(1);
	lock.unlock();
	sem_post(itemsSemaphore);

	int pid = fork();
	if (pid < 0) {
		return false;
	}
	else if (pid > 0) {
		std::cout << "Parent: waiting for child " << pid << std::endl;
		int status;
		waitpid(pid, &status, 0); //ensure waitpid() is called in the parent to wait for child to complete.
	}

	else {
		std::cout << "Entering the child process" << std::endl;
		executeTasks();
		std::cout << "Exiting the child process" << std::endl;
		exit(0);
	}
	return true;
}

void ProcessManagement::executeTasks() {
	// singleThreaded
	// while (!taskQueue.empty()) {
	// 	std::unique_ptr<Task> taskToExecute = std::move(taskQueue.front());
	// 	taskQueue.pop();
	// 	std::cout << "Executing task: " << taskToExecute->toString() << std::endl;

	// 	executeCryption(taskToExecute->toString());
	// }

	// multiThreaded
	sem_wait(itemsSemaphore);
	std::unique_lock<std::mutex> lock(queueLock);
	char taskStr[256];
	strcpy(taskStr, sharedMem->tasks[sharedMem->front]);

	sharedMem->front = (sharedMem->front + 1) % 1000;
	sharedMem->size.fetch_sub(1);
	lock.unlock();
	sem_post(empty_Semaphore);
	std::cout << "Executing child process" << std::flush;
	executeCryption(taskStr);
}