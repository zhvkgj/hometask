// Depth-First_Search.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <mutex>
#include <thread>

class derevo {
	std::mutex mutex;
	std::vector <std::vector <int> > vec_table;
	std::vector <int> visited; // массив, в котором хранится информация о посещении вершины во время обхода
	int size;
public:
	derevo() {}
	void resize() {
		vec_table.resize(size);
		for (int i = 0; i < size; ++i)
			vec_table[i].resize(size);
		visited.resize(size);
	}
	void set_size(int size_) {
		size = size_;
		resize();
	}

	int get_size()
	{
		return size;
	}

	void set_derevo(int size_) {
		set_size(size_);
		for (int j = 0; j < size; j++)
			for (int i = 0; i < size; i++) {
				std::cout << "Click 1 if you want to set the branch from vertex " << j << " to " << i << std::endl;
				std::cin >> vec_table[j][i];
			}
		for (int i = 0; i < size; i++)
			visited[i] = 0;
		clear_excess();
	}
	// функция убирающая петли в графе и делающая его ориентированным
	void clear_excess() {
		for (int j = 0; j < size; j++)
			for (int i = 0; i < size; i++)
				if (i == j) vec_table[j][i] = 0;

		for (int j = 0; j < size; j++)
			for (int i = 0; i < size; i++)
				if (vec_table[j][i] = 1) vec_table[i][j] = -1;
	}
	//функция обхода в глубину
	void do_dfs() {
		for (int i = 0; i < size; i++) {
			dfs(i);
		}
	}
	//обход в глубину
	void dfs(int i) {
		std::cout << "[thread] id = " << std::this_thread::get_id() << std::endl;
		mutex.lock();
		visited[i] = true;
		mutex.unlock();
		for (int k = 0; k < size; k++)
			if (vec_table[i][k] != 0 && visited[k] == 0)
				dfs(k);
	}

};

void threadFunction(derevo &tree, int numberHalf)
{
	if (numberHalf == 1)
	{
		for (int i = 0; i < (tree.get_size() / 2); i++) tree.dfs(i);
	}
	else
	{
		for (int j = (tree.get_size() / 2); j < tree.get_size(); j++) tree.dfs(j);
	}
}

int main() {
	derevo Tree;
	Tree.set_derevo(6);
	std::thread first(threadFunction, &Tree, 1);
	std::thread second(threadFunction, &Tree,2);

	first.join();
	second.join();
	
	system("pause");
	return 0;
}