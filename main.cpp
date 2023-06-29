#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include "SudokuSolver.h"
#include "SudokuGenerator.h"
using namespace std;

//数独以vector<int>形式构建，如果需要生成多个数独，则用二维向量vector<vector<int>>

//===================生成========================
//在生成之前，需要构造生成器SudokuGenerator
//对于generateSudoku方法，其输入参数为生成数独的个数，返回一个二维向量
//对于generatePuzzles方法，其输入参数为(生成谜题个数,挖空数量),返回一个二维向量,其中挖空用0代替
//挖空已经实现保证唯一解,如果挖空太多导致无法生成唯一解,会输出ERROR(这部分还要重写,目前思路是丢弃这一个终局)

//===================解密========================
//解密之前需要初始化解密器solver和DLX节点,代码如下
//SudokuSolver solver;
//DLXNode* listHead = new DLXNode();
//之后可以调用solver的solveSudoku方法
//输入参数DLXNode *listHead, vector<int>& sudoku, vector<int> &answer
//第二个参数为求解的数独,第三个参数为生成的数独答案

//TODO
//文件读写
//主函数命令行实现
//测试(代码规范和覆盖率)
//覆盖率可能很低,之后进行冗余代码删除

void solvePuzzle(fstream& puzzleFile){
    SudokuSolver solver;
    DLXNode* listHead = new DLXNode();
    vector<vector<int>> sudokus;
    vector<int> answers;
    SudokuGenerator generator;
    sudokus=generator.generatePuzzles(10,70);

    SudokuLoader loader = SudokuLoader();
    vector<vector<int>> sudokuSet = loader.loadFromFile(puzzleFile);
	int sudokuCount = sudokuSet.size();

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
        
    fstream solutionFile;
    solutionFile.open("sudoku.txt", ios::out);
    if (answers.size() == 0) {cout << "无解" << endl;
    }
    else {loader.writeToFile(answers, solutionFile);
    }
    solutionFile.close();   
    }
}

