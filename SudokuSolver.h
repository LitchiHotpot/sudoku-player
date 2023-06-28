#pragma once
#include "DLXGenerator.h"
#include "DLXSolver.h"
#include <vector>

#pragma once

using namespace std;

class SudokuSolver {
public:
    vector<vector<int>> elementSubscriptss; //One set of element stands for one number's info

    //将数独转换为正交列表
    void transformToList(vector<int>& sudokuArray, DLXNode *listHead);

    //调用DLXSolver的solve（）来求解一个数独，将解决方案转换为数组
    bool solveSudoku(DLXNode *listHead, vector<int>& sudoku, vector<int> &answer);

    void solveWithAllAnswers(DLXNode *listHead, vector<int>& sudoku, vector<vector<int>>& answers);
    //用不同的答案解决一个数独
    void solveWithMultiAnswers(DLXNode* listHead, vector<int>& sudoku, vector<vector<int>>& answers, int answerCount);

    //将dlx解决方案转换为数独答案
    void solutionToAnswer(vector<CommonNode*>& solution, vector<int>& answer);

    int indexToRow(int index, int rowLength);

    int indexToColumn(int index, int columnLenghth);

    void appendOneSubscript(vector<vector<int>>& subscriptss, int index, int value);

    int getValue(int index);

    CommonNode* getRowHead(CommonNode* node);
};



