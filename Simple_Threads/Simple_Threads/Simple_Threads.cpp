// Simple_Threads.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//Первая и задача
#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <functional>
using namespace std;

vector <vector <int> > table = 
{
	{ 1, 3, 2, 5 },
	{ 10, 4, 6, 15 },
	{ 3, 2, 0, 12 },
	{ 29, 58, 13, 11 }
};

void sort_my_table(vector <int> & row) {
	sort(row.begin(), row.end());
}

int main()
{	
	for (int i = 0; i < table.size(); i++) {
		std::thread thread(sort_my_table, std::ref(table[i]));
		thread.join();
	}
	
	for (int i = 0; i < table.size(); i++) {
		int m = 0;
		for (int k = 0; k < table[i].size(); k++) {
			m++;
			cout << table[i][k] << ' ';
			if (m == table.size()) cout << endl;
		}
	}
	system("pause");
    return 0;
}

