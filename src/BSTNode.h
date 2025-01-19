#ifndef BSTNODE_H
#define BSTNODE_H
#include "Task.h"

class BSTNode{
public:
    Task task;
    BSTNode* left;
    BSTNode* right;
    BSTNode();
    BSTNode(Task t);
};

#endif