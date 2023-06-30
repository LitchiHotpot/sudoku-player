// Copyright [2023] <Copyright Justvb&LitchiHotpot>
#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "SudokuSolver.h"
#include "SudokuGenerator.h"
#include "SudokuLoader.h"
using namespace std;

// 数独以vector<int>形式构建，如果需要生成多个数独，则用二维向量vector<vector<int>>

// ===================生成========================
// 在生成之前，需要构造生成器SudokuGenerator
// 对于generateSudoku方法，其输入参数为生成数独的个数，返回一个二维向量
// 对于generatePuzzles方法，其输入参数为(生成谜题个数,挖空数量),返回一个二维向量,其中挖空用0代替
// 挖空已经实现保证唯一解,如果挖空太多导致无法生成唯一解,会输出ERROR(这部分还要重写,目前思路是丢弃这一个终局)

// ===================解密========================
// 解密之前需要初始化解密器solver和DLX节点,代码如下
// SudokuSolver solver;
// DLXNode* listHead = new DLXNode();
// 之后可以调用solver的solveSudoku方法
// 输入参数DLXNode *listHead, vector<int>& sudoku, vector<int> &answer
// 第二个参数为求解的数独,第三个参数为生成的数独答案

// TODO(over)
// 测试(代码规范和覆盖率)
// 覆盖率可能很低,之后进行冗余代码删除

int main(int argc, char * argv[]) {
    if (argv[1][1] == 'h') {
        cout << "Welcome to use the DLX Sudoku program. The instructions of the program are as follows:" << endl;
        cout << "-c Generate Sudoku end to file" << endl << "-s Read the file and solve Sudoku" << endl;
        cout << "-n Generate Sudoku questions with a unique solution" << endl << "-m Specify the difficulty of the question" << endl;
        cout << "-r Formulate the number of questions to be hollowed out" << endl << "-u Generate a unique solution to the question  (negligible)" << endl;
    }
    else if (argv[1][1] == 'c') {
        // 生成不重复的数独终局至文件 -c n
        int sudoku_count;
        sudoku_count = atoi(argv[2]);
        SudokuGenerator generator;
        SudokuLoader loader;
        fstream sudokusFile;
        sudokusFile.open("sudokuEnd.txt", ios::out);
        vector<vector<int>> sudokus;
        sudokus = generator.generateSudokus(sudoku_count);
        loader.writeToFile(sudokus, sudokusFile);
        sudokusFile.close();
        cout << "Generate Ends Finished!" << endl;
    }
    else if (argv[1][1] == 's') {
        // 求解路径为path的文件中的数独问题至文件 -s n

        SudokuGenerator generator;
        SudokuLoader loader;

        fstream puzzleFile;
        puzzleFile.open(argv[2], ios::in);
        // -------------------------------------------------
        vector<vector<int>> sudokuSet = loader.loadFromFile(puzzleFile);
        int sudokuCount = sudokuSet.size();
        cout << sudokuCount << " sudokus solved!" << endl;
        // Solve sudokus
        vector<vector<int>> answers;
        answers.resize(sudokuCount);

        for (unsigned int j = 0; j < sudokuSet.size(); ++j) {
            SudokuSolver solver = SudokuSolver();
            DLXNode* listHead = new DLXNode();
            vector<int> answer;
            if (solver.solveSudoku(listHead, sudokuSet[j], answer)) {
                // Answer got correctly
                answers[j] = answer;
            }
            else {
                cout << "No solution for sudoku No." << j + 1 << endl;
            }
        }

        // Save solution to file
        fstream solutionFile;
        solutionFile.open("sudoku.txt", ios::out);
        if (answers.size() == 0) {
            cout << "No solutions for all sudokus" << endl;
        }
        else {
            loader.writeToFile(answers, solutionFile);
        }
        solutionFile.close();
        // -------------------------------------------------
        puzzleFile.close();
        cout << "Finished!" << endl;
    }
    else if (argv[1][1] == 'n') {
        int sudoku_count;
        sudoku_count = atoi(argv[2]);
        if (argc <= 3) {
            // 生成n个数独谜题,保证具有唯一解,难度随机
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<int> dis(20, 55);
            int fill_count = dis(gen);
            SudokuGenerator generator;
            SudokuLoader loader;
            fstream sudokusFile;
            sudokusFile.open("sudokuPuzzles.txt", ios::out);
            vector<vector<int>> sudokus;
            sudokus = generator.generatePuzzles
            (sudoku_count, fill_count);
            loader.writeToFile(sudokus, sudokusFile);
            sudokusFile.close();
        }
        else {
            if (argv[3][1] == 'm') {
                // 指定难度
                int min_tab, max_tab;
                switch (atoi(argv[4])) {
                    case 1:
                        min_tab = 20;
                        max_tab = 30;
                        break;
                    case 2:
                        min_tab = 30;
                        max_tab = 45;
                        break;
                    case 3:
                        min_tab = 45;
                        max_tab = 55;
                        break;
                    default:
                        string diffc_error = "Difficulty " +
                        string(argv[4]) + " not exist, please check!";
                        throw invalid_argument(diffc_error);
                }
                random_device rd;
                mt19937 gen(rd());
                uniform_int_distribution<int> dis(min_tab, max_tab);
                int fill_count = dis(gen);
                SudokuGenerator generator;
                SudokuLoader loader;
                fstream sudokusFile;
                sudokusFile.open("sudokuPuzzles.txt", ios::out);
                vector<vector<int>> sudokus;
                sudokus = generator.generatePuzzles(sudoku_count, fill_count);
                loader.writeToFile(sudokus, sudokusFile);
                sudokusFile.close();
            }
            else if (argv[3][1] == 'r') {
                int min_tab = int(argv[4][0]-'0')*10+int(argv[4][1]-'0');
                int max_tab = int(argv[4][3]-'0')*10+int(argv[4][4]-'0');
                random_device rd;
                mt19937 gen(rd());
                uniform_int_distribution<int> dis(min_tab, max_tab);
                int fill_count = dis(gen);
                SudokuGenerator generator;
                SudokuLoader loader;
                fstream sudokusFile;
                sudokusFile.open("sudokuPuzzles.txt", ios::out);
                vector<vector<int>> sudokus;
                sudokus = generator.generatePuzzles(sudoku_count, fill_count);
                loader.writeToFile(sudokus, sudokusFile);
                sudokusFile.close();
            }
            else {
                string inst_error = "Instruction " +
                string(argv[3]) + " not exist, please check!";
                throw invalid_argument(inst_error);
            }
        }
        cout << "Generate Puzzles Finished!" << endl;
    }
    else {
        string inst_error = "Instruction " + string(argv[1])+
        " not exist, please check!";
        throw invalid_argument(inst_error);
    }
}

