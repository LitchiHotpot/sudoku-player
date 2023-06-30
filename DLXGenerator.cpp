#include "DLXGenerator.h"

//Create column heads linked with list head, and return column heads
vector<ColumnHead*> DLXGenerator:: createColumnHeads(DLXNode* listHead, int length){
    vector<ColumnHead*> columnHeads;
    columnHeads.resize(length);
    DLXNode* lastNode = listHead;

    for (int i = 0; i < length; ++i) {
        ColumnHead* columnHead = new ColumnHead(i);
        lastNode->appendRightNode(columnHead);
        columnHeads[i] = columnHead;
        lastNode = columnHead;
    }

    lastNode->appendRightNode(listHead);
    return columnHeads;
}

//Append one line of elements from matrix to orthogonal list
void DLXGenerator:: appendLine(vector<ColumnHead*> columnHeads, vector<int> elementSubscripts, int rowIndex){
    CommonNode* lastHorizontalNode = NULL;
    CommonNode* firstHorizontalNode = NULL;

    for (unsigned int i = 0; i < elementSubscripts.size(); ++i) {
        int subscript = elementSubscripts[i];
        ColumnHead* columnHead = columnHeads[subscript];
        CommonNode* currentNode = new CommonNode(rowIndex, columnHead);
        DLXNode *lastVerticalNode = columnHead->upNode;

        //Link vertical nodes
        lastVerticalNode->appendDownNode(currentNode);
        currentNode->appendDownNode(columnHead);

        //Link horizontal nodes
        if (i == 0) {
            firstHorizontalNode = currentNode;
            lastHorizontalNode = currentNode;
        } else {
            lastHorizontalNode->appendRightNode(currentNode);
            lastHorizontalNode = currentNode;
        }

        currentNode->columnIndex = columnHead->columnIndex;
        columnHead->numberOfOne++;
    }
    lastHorizontalNode->appendRightNode(firstHorizontalNode);
}