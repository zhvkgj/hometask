#include "stdafx.h"
#include "Threads_queue.h"
#include <iostream>
#include <fstream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <chrono>
#include <string>

MyQueue::~MyQueue()
{
	Node* tempNode = head;
	while (tempNode != NULL)
	{
		tempNode = head->next;
		delete head;
		head = tempNode;
	}
}

void MyQueue::add(int x)
{
	if (!_var)
	{
		Node* tempNode = new Node;
		tempNode->number = x;
		tempNode->next = NULL;

		if (head != NULL)
		{
			tail->next = tempNode;
			tail = tempNode;
		}
		else head = tail = tempNode;
	}
	else std::cout << "You can not modify queue while it is being printed to file!" << std::endl;
}

void MyQueue::printToLogFile()
{
	std::ofstream logFile;
	std::string tempStr;
	logFile.open("log.txt", std::ios_base::app);
	Node* tempNode = head; 
	while (tempNode != NULL) 
	{
		tempStr = std::to_string(tempNode->number);
		logFile << tempStr << " "; 
		tempNode = tempNode->next;
	}
	logFile << '\n';
	logFile.close();
}

void MyQueue::deleteNode()
{
	if (!_var)
	{
		if (head != NULL)
		{
			Node* tempNode = head;
			head = head->next;
			delete tempNode;
		}
		else std::cout << "Queue is empty!" << std::endl;
	}
	else std::cout << "You can not modify queue while it is being printed to file!" << std::endl;
}

void MyQueue::bar()
{
	while (true)
	{
		char input;
		std::cout << "Input: "; std::cin >> input;
		std::cin.clear();

		if (input == 'y')
		{
			_var = true;
			condVar.notify_one();
		}

		if (input == 'n')
			_var = false;
	}
}

void MyQueue::foo()
{
	while (true)
	{
		std::unique_lock<std::mutex> ulm(myMutex);
		condVar.wait(ulm, [=]() {return _var; });
		printToLogFile();
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}