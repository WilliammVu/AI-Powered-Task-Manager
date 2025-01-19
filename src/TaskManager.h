#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "Command.h"
#include "TaskList.h"
#include "TaskDateBST.h"
#include "TaskTitleBST.h"

//Duplicate Tasks will not be inserted
class TaskManager{
private:
    int size;
    TaskList list;
    stack<Command*> commandStack;
    //Binary Search Tree sorted by Task dates
    TaskDateBST dateTree;
    //Binary Search Tree sorted by Task Titles
    TaskTitleBST titleTree;
public:
    TaskManager();
    int length() const;
    bool prepend(Task);
    bool append(Task);
    bool insertAfter(Task, int index);
    bool remove(int index);
    bool swap(int index1, int index2);
    bool edit(int index);
    Task* search(Date date);
    Task* search(string title);
    void display() const; //list
    void displayByDate() const; //dateTree
    void displayByTitle() const; //titleTree
    void undo();
};

#endif