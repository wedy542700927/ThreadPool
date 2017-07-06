#ifndef _THREADPOOL_H
#define _THREADPOOL_H
#include <iostream>
#include <queue>
#include <pthread.h>
using namespace std;
class Task;
class ThreadPool
{
private:
	int thread_num;
	static queue<Task*> task_queue;
	static bool shutdown;
	static pthread_mutex_t mutex;
	static pthread_cond_t condition;
	pthread_t* pthread_ids;
public:
	ThreadPool(int);
	static void* threadFunc(void*);
	void addTask(Task*);
	void joinAll();
	~ThreadPool();
};
#endif
