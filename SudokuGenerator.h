#pragma once
#include <vector>
#include "DLXGenerator.h"
#include "SudokuSolver.h"

using namespace std;

class SudokuGenerator{
public:
    vector<vector<int>> generateSudokus(int sudokuCount);

    vector<vector<int>> generatePuzzles(int sudokuCount,int fillPuzzle);

    bool isAnswerUnique(vector<int> &sudoku);
};



