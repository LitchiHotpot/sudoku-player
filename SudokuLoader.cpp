#include "SudokuLoader.h"
#include <sstream>
#include <stdlib.h>

#define sudokuSize 81
#define sudokuLength 9

//将指定文件中的所有数独加载到向量中
vector<vector<int>> SudokuLoader::loadFromFile(fstream& file){
    vector<vector<int>> sudokuSet;
    stringstream buffer;
    string content = "";
    buffer << file.rdbuf(); //读取文件中的所有内容
    content = buffer.str();
    //删除空格、回车
    unsigned int i = 0;
    while(i < content.size()) {
        if (content[i] == ' ' || content[i] == '\n') {
            content.erase(i, 1);
            continue;
        }
        i++;
    }
    //分组
    for (unsigned int j = 0, k = 0; j < content.size(); ++j) {
        int sudokuIndex = j / sudokuSize;
        
        if (j % sudokuSize == 0) { //重排
            vector<int> newSudoku;
            newSudoku.resize(sudokuSize);
            k = 0;
            sudokuSet.push_back(newSudoku);
        }

        sudokuSet[sudokuIndex][k++] = content[j] - '0';
    }
    return sudokuSet;
}
//将集中的数独保存到文件
void SudokuLoader::writeToFile(vector<vector<int>>& sudokuSet, fstream& file){
	int sudokuCount = sudokuSet.size();
	//char content[sudokuCount * (19 * 9 + 2)];
    for (unsigned int i = 0; i < sudokuCount; ++i) { //Sudoku set
        char content[19 * 9 + 2 + 9];
        int contentIndex = 0;

        for (unsigned int j = 0, k = 0; j < sudokuSize; ++j, ++k) { //One sudoku
            if (k != 0){
                content[contentIndex] = ' ';
                contentIndex++;
            }
            content[contentIndex] = sudokuSet[i][j] + '0';
            contentIndex++;

            if (k == sudokuLength - 1) {
                content[contentIndex] = '\n';
                contentIndex++;
                k = -1;
            }
        }
        content[contentIndex] = '\n';
        contentIndex++;

        content[contentIndex] = '\0';
        file << content;
    }
}