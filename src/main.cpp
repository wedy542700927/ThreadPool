#include <Task.h>
#include <ThreadPool.h>
class MyTask: public Task
{
public:
	MyTask(string name, void* data):Task(name, data){};
	void run()
	{
	}
	~MyTask(){};
};

int main()
{
	MyTask* myTask= new MyTask("task",NULL);
	ThreadPool pool(10);
	for (int i = 0; i < 1000; i++)
	{
		pool.addTask(myTask);
	}
	pool.joinAll();
	delete(myTask);
	return 0;
}
