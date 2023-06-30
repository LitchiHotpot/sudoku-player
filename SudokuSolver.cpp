#include "SudokuSolver.h"

#define sudokuLength 9
#define sudokuSize 81

// 调用DLXSolver的solve（）来求解一个数独，将解决方案转换为数组
bool SudokuSolver::solveSudoku(DLXNode *listHead,
vector<int> &sudoku, vector<int> &answer) {
    transformToList(sudoku, listHead);
    DLXSolver dlxSolver = DLXSolver();
    vector<CommonNode*> solution;
    dlxSolver.solveWithOneAnswer(listHead, solution, 0); //得到DLX答案

    if (solution.size() != sudokuSize ) { //没有得到解决方案
        return false;
    }

    solutionToAnswer(solution, answer);
    // 得到答案
    return true;
}

void SudokuSolver::solveWithAllAnswers(DLXNode *listHead, vector<int>& sudoku, vector<vector<int>>& answers) {
    transformToList(sudoku, listHead);
    DLXSolver dlxSolver = DLXSolver();
    vector<CommonNode*> tempSolution;
    vector<vector<CommonNode*>> lastSolution;
    tempSolution.reserve(sudokuSize);
    lastSolution.reserve(sudokuSize);
    dlxSolver.solveWithAllAnswers(listHead, tempSolution, lastSolution, 0);
    answers.resize(lastSolution.size());
    for (int i = 0; i < answers.size(); ++i) {
        vector<int> answer;
        solutionToAnswer(lastSolution[i], answer);
        answers[i] = answer;
    }
}

//  Transform dlx solution into sudoku answer
void SudokuSolver::solutionToAnswer(vector<CommonNode*>
& solution, vector<int>& answer) {
    answer.resize(sudokuSize);
    DLXNode* lastNode = NULL;
    int solutionIndex;
    int value;
    int rowIndex;

    for (unsigned int i = 0; i < sudokuSize; ++i) { //One row info represents one value with location
        CommonNode* rowHead = getRowHead(solution[i]);
        solutionIndex = rowHead->columnIndex; //First element infers location
        value = getValue(rowHead->rightNode->columnIndex); //Second element infers value
        answer[solutionIndex] = value;
    }
}

// 将数独转换为正交列表
void SudokuSolver::transformToList(vector<int>
& sudokuArray, DLXNode *listHead) {
    // Get the subscripts of ones
    for (unsigned int j = 0; j < sudokuArray.size(); ++j) {
        int value = sudokuArray[j];
        if (value == 0){ //Zero means value not accessible, all elements possibilities must be considered
            for (int i = 0; i < sudokuLength; ++i) {
                appendOneSubscript(elementSubscriptss, j, i + 1);
            }
            continue;
        } else {
            appendOneSubscript(elementSubscriptss, j, value);
        }
    }

    //Create DLX model
    DLXGenerator dlxGenerator = DLXGenerator();
    vector<ColumnHead*> columnHeads;
    columnHeads = dlxGenerator.createColumnHeads(listHead, sudokuSize * 4);
    unsigned int i;
    for (i = 0; i < elementSubscriptss.size(); ++i) {
        dlxGenerator.appendLine(columnHeads, elementSubscriptss[i], i);
    }
}

int SudokuSolver::indexToRow(int index, int rowLength) {
    return index / rowLength;
}

int SudokuSolver::indexToColumn(int index, int columnLenghth) {
    return index % columnLenghth;
}

// 添加一个元素的信息下标
void SudokuSolver::appendOneSubscript(vector<vector<int>>& elementSubscriptss, int index, int value) {
    int row = indexToRow(index, sudokuLength);
    int column = indexToColumn(index, sudokuLength);
    int block = (row / 3) * 3 + column / 3;
    int rowInfo = sudokuSize + (row * sudokuLength + value - 1); //-1 for index, same as below
    int columnInfo = sudokuSize * 2 + (column * sudokuLength + value - 1);
    int blockInfo = sudokuSize * 3 + (block * sudokuLength + value - 1);

    vector<int>elementSubscripts = {index, rowInfo, columnInfo, blockInfo}; //Add infos
    elementSubscriptss.push_back(elementSubscripts);
}

// 根据正交列表索引获取值
inline int SudokuSolver::getValue(int index) {
    return (((index - sudokuSize) % sudokuLength) + 1);
}

CommonNode * SudokuSolver::getRowHead(CommonNode * node)
{
    int columnIndex = node->columnIndex;
    if (columnIndex <= 80) {
        return node;
    } else if (columnIndex >= 81 && columnIndex <= 161) {
        return (CommonNode*)(node->leftNode);
    } else if (columnIndex >= 162 && columnIndex <= 242) {
        return (CommonNode*)(node->leftNode->leftNode);
    } else if (columnIndex >= 243 && columnIndex <= 323) {
        return (CommonNode*)(node->leftNode->leftNode->leftNode);
    } else {
        std::cout << "SudokuSolver::getRowHead(): Column index out of bound." << endl;
    }
    return nullptr;
}
