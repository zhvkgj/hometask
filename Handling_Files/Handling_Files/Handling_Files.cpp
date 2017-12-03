// Handling_Files.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

std::vector <std::string, bool> myFiles;

//complete
void assignFile(std::string fileName)
{
	std::ofstream fout(fileName.c_str(), std::ios_base::trunc);
	if (!fout.is_open()) std::cerr << "File cant be created!\n";
	else myFiles.push_back(fileName);
	fout.close();
}

//complete
void deleteFile(std::string fileName)
{
	if (remove(fileName.c_str())) std::cerr << "Error!\n";
	else std::cout << fileName << " was deleted!\n";
	for (int i = 0; i < myFiles.size(); i++)
	{
		if (myFiles[i] == fileName)
			myFiles.erase(myFiles.begin()+i);
	}
}

//complete
void pushBackString(std::string fileName, std::string myStr)
{
	for (int i = 0; i < myFiles.size(); i++)
	{
		if (myFiles[i] == fileName)
		{
			std::ifstream fin(fileName.c_str());
			if (!fin.is_open()) std::cerr << "File cant be opened!\n";
			else 
			{
				if (fin.get() != EOF)
				{
					fin.close();
					std::ofstream fout(fileName.c_str(), ios_base::app);
					fout << "\n" << myStr;
					fout.close();
				}
				else
				{
					fin.close();
					std::ofstream fout(fileName.c_str(), ios_base::app);
					fout << myStr;
					fout.close();
				}
			}
		}
	}
}

//complete
void popBackString(std::string fileName)
{
	for (int i = 0; i < myFiles.size(); i++)
	{
		if (myFiles[i] == fileName)
		{
			std::vector <std::string> buffer;
			std::ifstream fin(fileName.c_str());
			if (!fin.is_open()) std::cerr << "File cant be opened!\n";
			else
			{
				std::string tempStr;
				while (getline(fin, tempStr))
					buffer.push_back(tempStr);
				buffer.resize(buffer.size() - 1);
				fin.close();
				std::ofstream fout(fileName.c_str(), std::ios_base::trunc);
				for (int i = 0; i < buffer.size(); i++)
				{
					fout << buffer[i] << "\n";
				}
				fout.close();
				std::cout << "String \"" << tempStr << "\" was deleted!\n";
			}
		}
	}
}

//complete
void printFile(std::string fileName)
{
	bool k = false;
	for (int i = 0; i < myFiles.size(); i++)
	{
		if (myFiles[i] == fileName)
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
			k = true;
		}
	}
	if (!k) std::cerr << "File did not found!\n";
}

int main()
{
	assignFile("test.txt");
	pushBackString("test.txt", "Hello!");
	assignFile("test1.txt");
	cout << myFiles[0] << endl;
	cout << myFiles.size() << endl;
	pushBackString("test1.txt", "Hello world!");
	pushBackString("test1.txt", "Hello world!");
	deleteFile("test.txt");
	cout << myFiles[0] << endl;
	cout << myFiles.size() << endl;
	printFile("test1.txt");
	popBackString("test1.txt");
	printFile("test1.txt");
	system("pause");
    return 0;
}

