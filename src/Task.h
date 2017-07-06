#ifndef _TASK_H
#define _TASK_H
#include <iostream>
class Task
{
protected:
	std::string name;
	void* data;
public:
	Task(std::string, void*);
	virtual void run() = 0;
	virtual ~Task();
};
#endif
