// Copyright [2023] <Copyright Justvb&LitchiHotpot>
#include "DLXSolver.h"
// et only one solution
bool DLXSolver::solveWithOneAnswer
(DLXNode *listHead, vector<CommonNode*>& solution, int depth) {
    if (listHead->rightNode == listHead) {
        // Solution found
        return true;
    }

    // Select column with least one's
    ColumnHead* columnHead = selectColumn(listHead);
    cover(columnHead);

    bool solutionFound = false;
    // Usage: return type

    // Loop rows with one in column below columnHead
    for (DLXNode* node = columnHead->downNode;
    node != columnHead; node = node->downNode) {
        solution.push_back((CommonNode*)node);
        // Add temporary tempSolution node

        for (DLXNode* node2 = node->rightNode; node2
        != node; node2 = node2->rightNode) {
            cover(((CommonNode*)node2)->columnHead);
        }

        depth++;
        solutionFound = solveWithOneAnswer
        (listHead, solution, depth);
        // Enter next recursion level
        depth--;

        for (DLXNode* node2 = node->leftNode; node2
        != node; node2 = node2->leftNode) {
            uncover(((CommonNode*)node2)->columnHead);
        }

        if (solutionFound) {
            // Solution found, jump out loop
            break;
        }

        solution.pop_back();
        // Delete temporary tempSolution node
    }
    uncover(columnHead);

    return solutionFound;
}

// Get all solutions
void DLXSolver:: solveWithAllAnswers(DLXNode *listHead, vector<CommonNode*>
& tempSolution, vector<vector<CommonNode*>>& lastSolution, int depth) {
    if (listHead->rightNode == listHead) {
        // One solution found
        lastSolution.push_back(tempSolution);
        return;
    }

    ColumnHead* columnHead = selectColumn(listHead);
    cover(columnHead);

    for (DLXNode* node = columnHead->downNode; node
    != columnHead; node = node->downNode) {
        tempSolution.push_back((CommonNode*)node);
        // Add temporary tempSolution node

        for (DLXNode* node2 = node->rightNode;
        node2 != node; node2 = node2->rightNode) {
            cover(((CommonNode*)node2)->columnHead);
        }

        depth++;
        solveWithAllAnswers(listHead, tempSolution, lastSolution, depth);
        // Enter next recursion level
        depth--;

        for (DLXNode* node2 = node->leftNode; node2
        != node; node2 = node2->leftNode) {
            uncover(((CommonNode*)node2)->columnHead);
        }

        tempSolution.pop_back();
        // Delete temporary tempSolution node
    }
    uncover(columnHead);
}

// Get certain amount of answers
void DLXSolver:: solveWithCertainAnswers(DLXNode *listHead, vector
<CommonNode*>& tempSolution, vector<vector<CommonNode*>>& lastSolution,
                                         int answerCount, int depth) {
    if (listHead->rightNode == listHead) {
        // One solution found
        lastSolution.push_back(tempSolution);
        return;
    }

    ColumnHead* columnHead = selectColumn(listHead);
    cover(columnHead);

    for (DLXNode* node = columnHead->downNode; node !=
    columnHead; node = node->downNode) {
        tempSolution.push_back((CommonNode*)node);
        // Add temporary tempSolution node

        for (DLXNode* node2 = node->rightNode;
        node2 != node; node2 = node2->rightNode) {
            cover(((CommonNode*)node2)->columnHead);
        }

        depth++;
        solveWithCertainAnswers(listHead, tempSolution,
        lastSolution, answerCount, depth);
        // Enter next recursion level
        depth--;

        for (DLXNode* node2 = node->leftNode; node2
        != node; node2 = node2->leftNode) {
            uncover(((CommonNode*)node2)->columnHead);
        }

        if (lastSolution.size() == answerCount) {
            // Solution count achieved get out of recursion
            break;
        }

        tempSolution.pop_back();
        // Delete temporary tempSolution node
    }
    uncover(columnHead);
    return;
}

// Cover certain rows
void DLXSolver:: cover(ColumnHead* columnHead) {
    columnHead->rightNode->leftNode = columnHead->leftNode;
    columnHead->leftNode->rightNode = columnHead->rightNode;

    for (DLXNode* tempNode = columnHead->downNode; tempNode !=
    columnHead ; tempNode = tempNode->downNode) {
        for (DLXNode* tempNode2 = tempNode->rightNode;  tempNode2
        != tempNode; tempNode2 = tempNode2->rightNode) {
            tempNode2->downNode->upNode = tempNode2->upNode;
            tempNode2->upNode->downNode = tempNode2->downNode;
            ((CommonNode*)tempNode2)->columnHead->numberOfOne--;
        }
    }
}

// Uncover certain rows
void DLXSolver:: uncover(ColumnHead* columnHead) {
    for (DLXNode* tempNode = columnHead->upNode;
    tempNode != columnHead; tempNode = tempNode->upNode) {
        for (DLXNode* tempNode2 = tempNode->leftNode;
        tempNode2 != tempNode; tempNode2 = tempNode2->leftNode) {
            ((CommonNode*)tempNode2)->columnHead->numberOfOne++;
            tempNode2->upNode->downNode = tempNode2;
            tempNode2->downNode->upNode = tempNode2;
        }
    }

    columnHead->rightNode->leftNode = columnHead;
    columnHead->leftNode->rightNode = columnHead;
}

// Select column with minimum one's
ColumnHead* DLXSolver:: selectColumn(DLXNode* listHead) {
    int min = 100000;
    ColumnHead* selectedHead = NULL;

    for (DLXNode* node = listHead->rightNode;
    node != listHead; node = node->rightNode) {
        ColumnHead* columnHead = (ColumnHead*) node;
        if (columnHead->numberOfOne < min) {
            min = columnHead->numberOfOne;
            selectedHead = columnHead;
        }
    }
    return selectedHead;
}
