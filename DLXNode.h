#pragma once
#include <iostream>
using namespace std;
//DLXNode的结构见论文: "Dancing Links" by Donald Knuth
class DLXNode {
public:
    DLXNode* leftNode = NULL;
    DLXNode* rightNode = NULL;
    DLXNode* upNode = NULL;
    DLXNode* downNode = NULL;
    int columnIndex = -1;

    DLXNode(): leftNode(this), rightNode(this), upNode(this), downNode(this) {}

    void appendLeftNode(DLXNode* tempNode);
    void appendRightNode(DLXNode* tempNode);
    void appendUpNode(DLXNode* tempNode);
    void appendDownNode(DLXNode* tempNode);
};

//列头，管理数独的一整列
class ColumnHead: public DLXNode {
public:
    int numberOfOne = 0;

    ColumnHead(int columnIndex) {
        this->columnIndex = columnIndex;
    }
};

//包含列头的common node
class CommonNode: public DLXNode {
public:
    int rowIndex;
    ColumnHead* columnHead = NULL;

    CommonNode(int rowIndex, ColumnHead *columnHead) : rowIndex(rowIndex), columnHead(columnHead) {}
};

