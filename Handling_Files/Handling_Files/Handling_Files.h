#ifndef __handling_files_h__
#define __handling_files_h__
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <thread>
#include <utility>
#include <chrono>

class Files
{
private:
	std::vector <std::pair<std::string, bool>> myFiles;
	bool access = true;

public:
	Files() = default;

	void assignFile(std::string);

	void deleteFile(int);

	void pushBackString(int, std::string);
	
	void popBackString(int);

	void printFile(int);

	int getCountOfFiles();

	std::string getNameOfFile(int);
};

void assignFileByThread(Files&, std::string);

void deleteFileByThread(Files&, int);

void pushBackStringByThread(Files&, int, std::string);

void popBackStringByThread(Files&, int);

void printFileByThread(Files&, int);

#endif __handling_files_h__