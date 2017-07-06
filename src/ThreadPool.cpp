#include <ThreadPool.h>
#include <Task.h>
bool ThreadPool::shutdown = false;
pthread_mutex_t ThreadPool::mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t ThreadPool::condition = PTHREAD_COND_INITIALIZER;
queue<Task*> ThreadPool::task_queue;
ThreadPool::ThreadPool(int num)
{
	thread_num = num;
	pthread_ids = new pthread_t[thread_num];
	for (int i = 0; i < num; i++)
	{
		pthread_create(pthread_ids + i, NULL, threadFunc, NULL);
	}
}
void* ThreadPool::threadFunc(void* threadData)
{
	pthread_t pthread_id = pthread_self();
	while (!shutdown)
	{
		pthread_mutex_lock(&mutex);
		while (task_queue.size() == 0 && !shutdown)
		{
			pthread_cond_wait(&condition, &mutex);//先释放锁，然后阻塞
			//在唤醒线程到重新加锁中间，共享数据(task_queue, shutdown)可能发生变化，需要重新判断，所以利用循环解决
		}
		if (task_queue.size() > 0)
		{
			Task* task = task_queue.front();
			task_queue.pop();
			cout<<"thread id: "<<pthread_id<<" run"<<endl;
			pthread_mutex_unlock(&mutex);
			task->run();
		}
		else pthread_mutex_unlock(&mutex);
	}
	return (void*)0;
}
void ThreadPool::addTask(Task* task)
{
	pthread_mutex_lock(&mutex);
	task_queue.push(task);
	pthread_mutex_unlock(&mutex);
	pthread_cond_signal(&condition);
}
void ThreadPool::joinAll()
{
	while (!shutdown)
	{
		if (task_queue.size() == 0)
		{
			shutdown = true;
			pthread_cond_broadcast(&condition);
			for (int i = 0; i < thread_num; i++)
			{
				pthread_join(pthread_ids[i], NULL);
				cout<<"thread id: "<<pthread_ids[i]<<" exit"<<endl;
			}
		}
	}
}
ThreadPool::~ThreadPool()
{
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&condition);
	delete(pthread_ids);
}
