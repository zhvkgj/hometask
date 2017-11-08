#ifndef __SUDOKU_SOLVER_H__
#define __SUDOKU_SOLVER_H__
#include <string>
#include <fstream>
#include <iostream>
#include <thread>
#include <chrono> //for sleep_for(usec)

const int SIZE = 9;
const int MAX_DIGIT = 9;

class Sudoku
{
private:
	int table[SIZE][SIZE];
	bool	isSolved = false;
	bool	canBeSolved = true;

public:
	// field game constructor 
	//	 read Sudoku from file "test_args.txt"
	Sudoku()
	{
		std::ifstream fin("test_args.txt");
		std::string tempStr;
		for (int i = 0; i < SIZE; i++)
		{
			std::getline(fin, tempStr);
			for (int j = 0; j < SIZE; j++)
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

	//write the solution to the file "test_result.txt"
	void printSolution()
	{
		std::ofstream fout("test_result.txt", std::ios::trunc);
		std::string tempStr;
		for (int i = 0; i < SIZE; i++) 
		{
			for (int j = 0; j < SIZE; j++) 
			{
				tempStr.push_back(table[i][j] + '0');
			}
			fout << tempStr <<'\n';
			tempStr.clear();
		}
		fout.close();
	}

	// check for matches of current number in current row, colomn and square
	//	 return true if match is found 
	//		return false if match is not found
	bool checkAvailability(int number, int row, int colomn)
	{
		for (int i = 0; i < SIZE; i++)
		{
			//check for match in row
			if (i != colomn && table[row][i] == number) return true;
			//check for match in colomn
			if (i != row && table[i][colomn] == number) return true;
		}

		// check for match in square
		// initilization begining of square sides
		int firstSide = (row / 3) * 3;
		int secondSide = (colomn / 3) * 3;
		for (int i = secondSide; i < (secondSide + 3); i++)
		{
			for (int j = firstSide; j < (firstSide + 3); j++)
			{
				if (i != colomn && j != row && table[j][i] == number) return true;
			}
		}

		return false;
	}

	// working in own thread and waiting signal from 
	//	 condition_variable object about solution
	void solutionInspector()
	{
		// printing Calculating
		//   while other thread is searching solution 
		while (isSolved == false & canBeSolved == true) 
		{
			std::cout << "Calculating...\n";
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
			system("cls");
		}
		if (isSolved)
		{
			std::cout << "Solved!\n" <<"Runtime - " << clock() / 1000.0 << '\n';
			std::cout << "Check solution in test_result.txt !\n";
			printSolution();
		}
		else std::cout << "No solution!\n";
	}

	void solveSearching(int firstIndex, int secondIndex)
	{
		//this condition means that all sudoku are filled
		//  i.e. solved
		if (firstIndex == 9 && secondIndex == 0)
		{
			isSolved = true;
			return;
		}
		
		//this means that current cell is empty
		if (table[firstIndex][secondIndex] == 0)
		{
			for (int i = 1; i <= MAX_DIGIT; i++)
			{
				if (!checkAvailability(i, firstIndex, secondIndex))
				{
					table[firstIndex][secondIndex] = i;
					// if not end of row
					if (secondIndex != (SIZE - 1))
						solveSearching(firstIndex, secondIndex + 1);
					// else go to the new row
					else solveSearching(firstIndex + 1, secondIndex - SIZE + 1);
					//if we have solution we should exit recursion
					if (isSolved) return;

					table[firstIndex][secondIndex] = 0;
				}
			}

		}
		// this means that current cells is not empty
		else
		{
			// if not end of row
			if (secondIndex != (SIZE - 1))
				solveSearching(firstIndex, secondIndex + 1);
			// else go to the new row
			else solveSearching(firstIndex + 1, secondIndex - SIZE + 1);
		}
	}

	void solve()
	{
		solveSearching(0, 0);
		// if sudoku is solved
		if (isSolved) return;
		// if sudoku is not solved
		//   we should stop solutionInspector thread
		else canBeSolved = false;
	}
	
};

void threadFunction1(Sudoku &sud)
{
	sud.solutionInspector();
}

#endif __SUDOKU_SOLVER_H__
