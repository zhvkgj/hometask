// Atomic_with_lambda.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Atomic_with_lambda.h"
using namespace std;

int main()
{
	MyAtomic<int> foo = 0;
	foo.exchange(2);
	cout << foo.load() << endl;
	cout << "Multiply by two... ";
	foo.atomicShell(0);
	cout << "Absolute value... ";
	foo.atomicShell(1);
	cout << "To the second pow... ";
	foo.atomicShell(2, 2);
	system("pause");
	return 0;
}