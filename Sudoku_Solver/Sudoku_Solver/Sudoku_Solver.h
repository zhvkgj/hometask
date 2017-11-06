#ifndef __SUDOKU_SOLVER_H__
#define __SUDOKU_SOLVER_H__
#include <string>
#include <fstream>
#include <iostream>

class Sudoku
{
private:
	int table[9][9];
	bool isSolved = false;

public:
	// field game constructor 
	// reads Sudoku from file "test_args.txt"
	Sudoku()
	{
		std::ifstream fin("test_args.txt");
		std::string tempStr;
		for (int i = 0; i < 9; i++)
		{
			std::getline(fin, tempStr);
			for (int j = 0; j < 9; j++)
			{
				if (tempStr[j] == ' ')
				{
					table[i][j] = (int)0;
				}
				else table[i][j] = (int)(tempStr[j] - '0');
			}
			tempStr.clear();
		}
		fin.close();

	}

	//writes the solution to the file "test_result.txt"
	void printSolution()
	{
		std::ofstream fout("test_result.txt", std::ios::trunc);
		std::string tempStr;
		for (int i = 0; i < 9; i++) 
		{
			for (int j = 0; j < 9; j++) 
			{
				if (table[i][j] == ' ') tempStr.push_back(' ');
				else tempStr.push_back(table[i][j] + '0');
			}
			fout << tempStr <<'\n';
			tempStr.clear();
		}
		fout.close();
	}



};

#endif __SUDOKU_SOLVER_H__
