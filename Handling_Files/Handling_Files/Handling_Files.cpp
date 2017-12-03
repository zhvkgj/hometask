#include "Handling_Files.h"
using namespace std;
void Files::assignFile(std::string fileName)
{
	std::ofstream fout(fileName.c_str(), std::ios_base::trunc);
	if (!fout.is_open()) std::cerr << "File cant be created!\n";
	else
	{
		myFiles.push_back(std::make_pair(fileName, true));
		fout.close();
	}
}

void Files::deleteFile(int numOfFile)
{
	while (!get<1>(myFiles[numOfFile]))
	{
		std::cout << "Thread "<< std::this_thread::get_id() <<" waiting for permission to delete...\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		system("cls");
	}
	if (remove(get<0>(myFiles[numOfFile]).c_str())) std::cerr << "Error!\n";
	else
	{
		std::cout << get<0>(myFiles[numOfFile]) << " was deleted!\n";
		myFiles.erase(myFiles.begin() + numOfFile);
	}
}

void Files::pushBackString(int numOfFile, std::string myStr)
{
	while (!get<1>(myFiles[numOfFile]))
	{
		std::cout << "Thread " << std::this_thread::get_id() << " waiting for permission to add string...\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		system("cls");
	}
	std::ifstream fin(get<0>(myFiles[numOfFile]).c_str());
	if (!fin.is_open()) std::cerr << "File cant be opened!\n";
	else
	{
		if (fin.get() != EOF)
		{
			fin.close();
			std::ofstream fout(get<0>(myFiles[numOfFile]).c_str(), ios_base::app);
			fout << "\n" << myStr;
			fout.close();
		}
		else
		{
			fin.close();
			std::ofstream fout(get<0>(myFiles[numOfFile]).c_str(), ios_base::app);
			fout << myStr;
			fout.close();
		}
	}
}

void Files::popBackString(int numOfFile)
{
	while (!get<1>(myFiles[numOfFile]))
	{
		std::cout << "Thread " << std::this_thread::get_id() << " waiting for permission to delete string...\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		system("cls");
	}
	std::vector <std::string> buffer;
	std::ifstream fin(get<0>(myFiles[numOfFile]).c_str());
	if (!fin.is_open()) std::cerr << "File cant be opened!\n";
	else
	{
		std::string tempStr;
		while (getline(fin, tempStr))
			buffer.push_back(tempStr);
		buffer.resize(buffer.size() - 1);
		fin.close();
		std::ofstream fout(get<0>(myFiles[numOfFile]).c_str(), std::ios_base::trunc);
		for (int i = 0; i < buffer.size(); i++)
		{
			fout << buffer[i] << "\n";
		}
		fout.close();
		std::cout << "String \"" << tempStr << "\" was deleted!\n";
	}
}

void Files::printFile(int numOfFile)
{
	while (!get<1>(myFiles[numOfFile]))
	{
		std::cout << "Thread " << std::this_thread::get_id() << " waiting for permission to print...\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		system("cls");
	}
	std::string tempStr;
	std::ifstream fin(get<0>(myFiles[numOfFile]).c_str());
	if (!fin.is_open()) std::cerr << "File cant be opened!\n";
	else
	{
		while (getline(fin, tempStr))
			std::cout << tempStr << '\n';
		fin.close();
	}	
}

int Files::getCountOfFiles()
{
	return myFiles.size();
}

std::string Files::getNameOfFile(int k)
{
	return get<0>(myFiles[k]);
}

void assignFileByThread(Files& files, std::string tempStr)
{
	files.assignFile(tempStr);
}

void deleteFileByThread(Files& files, int numOfFile)
{
	files.deleteFile(numOfFile);
}

void pushBackStringByThread(Files& files, int numOfFile, std::string tempStr)
{
	files.pushBackString(numOfFile, tempStr);
}

void popBackStringByThread(Files& files, int numOfFile)
{
	files.popBackString(numOfFile);
}

void printFileByThread(Files& files, int numOfFile)
{
	files.printFile(numOfFile);
}
