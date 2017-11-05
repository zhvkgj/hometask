#ifndef __SUDOKU_SOLVER_H__
#define __SUDOKU_SOLVER_H__
#include <string>
#include <fstream>

class Sudoku
{
private:
	int table[9][9];
	bool isSolved = false;

public:
	Sudoku()
	{
		std::ifstream fin("test_args.txt");
		std::string tempStr;
		for (int i = 0; i < 9; i++)
		{
			std::getline(fin, tempStr);
			for (int j = 0; j < 9; j++)
			{
				table[i][j] = (int)(tempStr[j] - '0');
			}
			tempStr.clear();
		}
		fin.close();
	}

};

#endif __SUDOKU_SOLVER_H__
