#ifndef TASKDATEBST_H
#define TASKDATEBST_H

#include "BSTNode.h"

//does not support duplicates
class TaskDateBST{
private:
    BSTNode* root;
public:
    TaskDateBST();
    BSTNode* search(Date date);
    //returns true if newTask does not exist yet in the tree
    bool insert(Task newTask);
    //returns true if newTask exists and is removed
    bool remove(Task target);
    void displayInOrder() const;
    void replace(Task oldTask, Task newTask);
private:
    void insert(BSTNode* newNode);
    void displayInOrder(BSTNode* current, int& index) const;
};

#endif