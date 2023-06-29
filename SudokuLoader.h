#pragma once
#include "math.h"
#include <fstream>
#include <vector>

using namespace std;

class SudokuLoader {
public:
    //将文件中的所有数独加载到向量中
    vector<vector<int>> loadFromFile(fstream& file);

    //将集中的数独保存到文件中
    void writeToFile(vector<vector<int>>& sudokuSet, fstream& file);
};