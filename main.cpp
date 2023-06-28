#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include "SudokuSolver.h"
#include "SudokuGenerator.h"
using namespace std;


int main() {
    SudokuSolver solver;
    DLXNode* listHead = new DLXNode();
    vector<vector<int>> sudokus;
    vector<int> answers;
    SudokuGenerator generator;
    sudokus=generator.generatePuzzles(10,70);

    for (auto& row : sudokus) {
        int k=0;
        vector<vector<int>> answers;
        SudokuSolver solver;
        DLXNode* listHead = new DLXNode();
        solver.solveWithAllAnswers(listHead, row, answers);
        cout<<answers.size()<<endl;
        for (auto& element : row) {
            cout<<element;
            k++;
            if(k==9){
                cout<<endl;
                k=0;
            }
        }

    }
}

