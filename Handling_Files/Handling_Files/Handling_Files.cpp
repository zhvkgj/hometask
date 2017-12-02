// Handling_Files.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

std::vector <std::string> myFiles;

void assignFile(std::string fileName)
{
	std::ifstream fin(fileName.c_str(), std::ios::trunc);
	if (!fin.is_open()) std::cerr << "File cant be created!\n";
	else myFiles.push_back(fileName);
	fin.close();
}

void deleteFile(std::string fileName)
{
	if (remove(fileName.c_str())) std::cerr << "Error!\n";
	else std::cout << fileName << " was deleted!\n";
}

void pushBackString(std::string fileName, std::string myStr)
{
	std::ofstream fout(fileName.c_str(), std::ios::ate);
	if (!fout.is_open()) std::cerr << "File cant be opened!\n";
	else fout << "\n" << myStr;
	fout.close();
}

void popBackString(std::string fileName)
{
	int sizeStr;
	std::ifstream fin(fileName.c_str());
	if (!fin.is_open()) std::cerr << "File cant be opened!\n";
	else
	{
		std::string tempStr;
		while (getline(fin, tempStr))
			sizeStr = tempStr.length();
	}
	fin.close();
	std::ofstream fout(fileName.c_str());
	fout.seekp(-sizeStr, std::ios::end);
	for (int i = 0; i != sizeStr; i++)
		fout << " ";
	fout.close();
}

void printFile(std::string fileName)
{
	std::string tempStr;
	std::ifstream fin(fileName.c_str());
	if (!fin.is_open()) std::cerr << "File cant be opened!\n";
	else
	{
		while (getline(fin, tempStr))
			std::cout << tempStr << '\n';
	}
	fin.close();
}



int main()
{
	assignFile("test.txt");
	system("pause");
    return 0;
}

