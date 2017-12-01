#ifndef __threads_queue_h__
#define __threads_queue_h__
#include <mutex>
#include <thread>
#include <condition_variable>

struct Node
{
	int number;
	Node* next;
};

class MyQueue
{
private:
	Node* head;
	Node* tail;
	std::mutex myMutex;
	std::condition_variable condVar;
	bool _var = false;

public:
	MyQueue() : head(NULL), tail(NULL) {};
	~MyQueue();
	void add(int);
	void printToLogFile();
	void deleteNode();
	//for multi-threading
	void bar();
	void foo();
};

#endif __threads_queue_h__
