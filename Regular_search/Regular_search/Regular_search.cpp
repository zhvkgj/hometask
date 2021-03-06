// Regular_search.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <regex>
#include <iterator>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	string str;
	regex regular("(https?://)?www\\.[\\da-z\\.-]+\\.[a-z\\.]{2,6}([\\/\\w\\.-]*)*\\/?");
	ifstream fin("url_search.txt");
	while (getline(fin, str))
	{
		fin >> str;
	}
	auto strBegin = sregex_iterator(str.begin(), str.end(), regular);
	auto strEnd = sregex_iterator();
	ofstream  fout("url_matches.txt", ios::trunc);
	for (sregex_iterator i = strBegin; i != strEnd; ++i) 
	{
		fout << (*i)[0] << '\n';
	}
	fout.close();
	fin.close();
	system("pause");
    return 0;
}

