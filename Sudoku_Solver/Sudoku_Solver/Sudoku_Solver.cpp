// Sudoku_Solver.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Sudoku_Solver.h"
using namespace std;

int main()
{
	Sudoku sudoku;
	thread solutionThread(threadFunction1, std::ref(sudoku));
	thread inspectorThread(threadFunction1, std::ref(sudoku));

	solutionThread.join();
	inspectorThread.join();
	
	system("pause");
    return 0;
}

