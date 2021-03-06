// Sudoku_Solver.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Sudoku_Solver.h"
#include <ctime>
using namespace std;

int main()
{
	Sudoku sudoku;
	thread inspectorThread(threadFunction1, std::ref(sudoku));
	inspectorThread.detach();
	sudoku.solve();
	cout << "\nRuntime - " << clock() / 1000.0 << endl;
	system("pause");
    return 0;
}

