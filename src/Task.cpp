#include <Task.h>
Task::Task(std::string name, void* data)
{
	this->name = name;
	this->data = data;
}
Task::~Task(){}
