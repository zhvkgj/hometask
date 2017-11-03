// My_Atomic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "My_Atomic.h"

int main()
{
	MyAtomic<int> value(15);
	value.store(10);
	std::cout << value.load() << std::endl;
	std::cout << value++.load() << std::endl;
	++value;
	std::cout << value.load() << std::endl;
	system("pause");
	return 0;
}

