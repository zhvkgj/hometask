// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Atomic_Vector.h"
using namespace std;

int main()
{
	AtomicVector <int> vec(5);
	for (size_t i = 0; i < vec.capacity();i++)
		vec.push_back(i);
	for (size_t i : vec)
		cout << vec[i]<< endl;
	AtomicVector <int> vec1(5);
	for (int i = 0; i < vec1.capacity(); i++)
		vec1.push_back(i+2);
	for (int i = 0; i< vec1.size();i++)
		cout << vec1[i] << endl;
	swap(vec, vec1);
	for (int i = 0; i < vec1.size(); i++)
		cout << vec1[i] << endl;
	system("pause");
    return 0;
}

