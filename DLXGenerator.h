#pragma once
#include "DLXNode.h"
#include <vector>

using namespace std;

class DLXGenerator {
public:
    //Create column heads linked with list head, and return column heads
    vector<ColumnHead*> createColumnHeads(DLXNode* listHead, int length);

    //Append one line of elements from matrix to orthogonal list
    void appendLine(vector<ColumnHead*> columnHeads, vector<int> elementSubscripts, int rowIndex);
};

