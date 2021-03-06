// Merge_sort_multi_threads.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <thread>
#include <vector>


void merge(std::vector<int>& vec, int left, int mid, int right)
{
	std::vector<int> first_arr(vec.begin() + left, vec.begin() + mid + 1);
	std::vector<int> second_arr(vec.begin() + mid + 1, vec.begin() + right + 1);

	int a = 0;
	int b = 0;
	int i = left;
	while (a < first_arr.size() && b < second_arr.size())
	{
		if (first_arr[a] < second_arr[b])
			vec[i++] = first_arr[a++];
		else
			vec[i++] = second_arr[b++];
	}

	// слияние левых кусочков
	while (a < first_arr.size())
		vec[i++] = first_arr[a++];
	while (b < second_arr.size())
		vec[i++] = second_arr[b++];
}

void merge_sort(std::vector<int>& vec, int start, int end)
{
	if (start >= end)
		return;

	int mid = start + (end - start) / 2;

	//запускаем по потоку на каждую часть и сортируем
	std::thread first(merge_sort, std::ref(vec), start, mid);
	std::thread second(merge_sort, std::ref(vec), mid + 1, end);
	first.join();
	second.join();

	//слияние частей
	merge(vec, start, mid, end);
	std::cout << "Sorting...\n";
}


int main()
{
	int a[] = { 10, 4, 2, 5, 9, 7, 1, 3, 15, 20 };
	std::vector<int> vec(a, a + 10);
	merge_sort(vec, 0, 9);
	for (int i = 0; i < 9; i++)
		std::cout << vec[i] << "\n";
	std::cout << "Complete!\n";
	system("pause");
	return 0;
}
