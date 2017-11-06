#ifndef __SUDOKU_SOLVER_H__
#define __SUDOKU_SOLVER_H__
#include <string>
#include <fstream>
#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <chrono> //for sleep_for(usec)

const int SIZE = 9;
const int MAX_DIGIT = 9;

class Sudoku
{
private:
	int table[SIZE][SIZE];
	bool	isSolved = false;
	bool	canBeSolve = true;
	//mutex	myMutex;
	//condition_variable threadSignal;
	//bool predicate ()
	//{
	//	return !isSolved;
	//}

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
				if (table[i][j] == ' ') tempStr.push_back(' ');
				else tempStr.push_back(table[i][j] + '0');
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
			if (table[row][i] == number) return true;
			//check for match in colomn
			if (table[i][colomn] == number) return true;
		}

		// check for match in square
		// initilization begining of square sides
		int firstSide = (row / 3) * 3;
		int secondSide = (colomn / 3) * 3;
		for (int i = secondSide; i < (secondSide + 3); i++)
		{
			for (int j = firstSide; j < (firstSide + 3); j++)
			{
				if (table[j][i] == number) return true;
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
		while (true) 
		{
			//std::unique_lock <mutex> ulm (myMutex);
			//threadSignal.wait(ulm, predicate);
			if (isSolved) return;
			if (!canBeSolve)
			{
				std::cout << "Unsolvable!\n";
				return;
			}
			std::cout << "Calculating...\n";
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
			system("cls");
		}

		std::cout << "Solved!\n";
		printSolution();
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
			for (int i = 1; i < MAX_DIGIT; i++)
			{
				table[firstIndex][secondIndex] = i;
				if (!checkAvailability(i, firstIndex, secondIndex))
				{
					// if not end of row
					if (secondIndex != SIZE - 1)
						solveSearching(firstIndex, secondIndex + 1);
					// else go to the new row
					else solveSearching(firstIndex + 1, secondIndex - SIZE + 1);
				}
				table[firstIndex][secondIndex] = 0;
			}

		}
		// this means that current cells is not empty
		else
		{
			// if not end of row
			if (secondIndex != SIZE - 1)
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
		canBeSolve = false;
		return;
	}
	//add timer in .cpp
	
};

void threadFunction1(Sudoku &sud)
{
	sud.solutionInspector();
}
void threadFunction2(Sudoku &sud)
{
	sud.solve();
}

#endif __SUDOKU_SOLVER_H__
