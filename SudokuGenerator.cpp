#include "SudokuGenerator.h"
#include <random>
#define sudokuSize 81

vector<int> sequence = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81};
vector<int> core1 = {1,2,3,4,5,6,7,8,9};
vector<vector<int>> SudokuGenerator:: generateSudokus(int sudokuCount) {
    vector<vector<int>> answers;
    vector<int> answer;
    vector<int> originalSudoku;
    originalSudoku.assign(sudokuSize, 0);
    for(int j=0;j<sudokuCount;j++) {
        for (int i = 0; i < 3; i++) {
            random_device rd;
            mt19937 gen(rd());
            shuffle(core1.begin(), core1.end(), gen);
            for(int j=0;j<3;j++){
                copy(core1.begin()+j*3, core1.begin()+(j*3+3), originalSudoku.begin() +i*30+j*9);
            }
        }
        DLXGenerator generator = DLXGenerator();
        DLXNode *listHead = new DLXNode();
        SudokuSolver solver = SudokuSolver();
        solver.solveSudoku(listHead, originalSudoku, answer);
        answers.push_back(answer);
    }
    return answers;
}

vector<vector<int>> SudokuGenerator::generatePuzzles(int sudokuCount,int fillPuzzle){
    random_device rd;
    mt19937 gen(rd());
    shuffle(sequence.begin(), sequence.end(), gen);
    vector<vector<int>> answers;
    int j=0,answer_index=0;
    answers= generateSudokus(sudokuCount);
    for(vector<int> answer:answers){
        j=0;
        for(int i=0;i<fillPuzzle;i++){
            int tmp=answer[sequence[j]];
            answers[answer_index][sequence[j]]=0;
            if(isAnswerUnique(answers[answer_index])){
                j++;
            }
            else {
                answers[answer_index][sequence[j]]=tmp;
                j++;
                i--;
            }
            if(j>=81){
                throw invalid_argument("There are too many spaces to guarantee the only solution, please retry!");
            }
        }
        random_device rd;
        mt19937 gen(rd());
        shuffle(sequence.begin(), sequence.end(), gen);
        answer_index++;
    }
    return answers;
}

bool SudokuGenerator::isAnswerUnique(vector<int> &sudoku){
    vector<vector<int>> tmp;
    SudokuSolver solver;
    DLXNode* listHead = new DLXNode();
    solver.solveWithAllAnswers(listHead, sudoku, tmp);
    if(tmp.size()==1)
        return true;
    else
        return false;
}