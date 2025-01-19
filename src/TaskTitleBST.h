#ifndef TASKTITLEBST_H
#define TASKTITLEBST_H

#include "BSTNode.h"

//does not support duplicates
class TaskTitleBST{
private:
    BSTNode* root;
public:
    TaskTitleBST();
    BSTNode* search(string title);
    bool insert(Task newTask);
    //returns true if newTask does not exist yet in the tree
    bool remove(Task target);
    //returns true if newTask exists and is removed
    void displayInOrder() const;
    void replace(Task oldTask, Task newTask);
private:
    void insert(BSTNode* newNode);
    void displayInOrder(BSTNode* current, int& index) const;
};

#endif