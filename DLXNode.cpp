// Copyright [2023] <Copyright Justvb&LitchiHotpot>
#include "DLXNode.h"
#include <iostream>

void DLXNode:: appendLeftNode(DLXNode* tempNode) {
    this->leftNode = tempNode;
    tempNode->rightNode = this;
}

void DLXNode:: appendRightNode(DLXNode* tempNode) {
    this->rightNode = tempNode;
    tempNode->leftNode = this;
}

void DLXNode:: appendUpNode(DLXNode* tempNode) {
    this->upNode = tempNode;
    tempNode->downNode = this;
}

void DLXNode:: appendDownNode(DLXNode* tempNode) {
    this->downNode = tempNode;
    tempNode->upNode = this;
}
