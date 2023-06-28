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
    sudokus=generator.generateSudokus(10);

    for (auto& row : sudokus) {
        int k=0;
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

