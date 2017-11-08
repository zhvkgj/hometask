// Regular_search.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <regex>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	cmatch result;
	regex regular("(https?://)?www\\.[\\da-z\\.-]+");
	string str;
	ifstream fin("url_search.txt");
	while (getline(fin, str))
	{
		fin >> str;
	}
	cout << str;
	if (regex_search(str.c_str(), result, regular))
	{
		ofstream fout("url_matches.txt", std::ios::trunc);
		for (size_t i = 0; i < result.size(); i++)
			//have some question about i++
			fout << result[i++]<< '\n';
		fout.close();
	}
	fin.close();
	system("pause");
    return 0;
}

