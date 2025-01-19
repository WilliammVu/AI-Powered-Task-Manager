#ifndef COMMAND_H
#define COMMAND_H

#include "TaskList.h"
#include "TaskDateBST.h"
#include "TaskTitleBST.h"

class Command{
public:
    virtual ~Command(){}
    virtual void undo() = 0;
};

class InsertCommand : public Command{
private:
    //the index of the task that has inserted, deleted, or changed
    int index; 
    //pointer to size member of the task manager
    int* size;
    //pointer to list member of the task manager
    TaskList* list;
    //pointer to dateTree member of the task manager
    TaskDateBST* dateTree;
    //pointer to titleTree member of the task manager
    TaskTitleBST* titleTree;
public:
    InsertCommand(int, int*, TaskList*, TaskDateBST*, TaskTitleBST*);
    void undo() override;
};

class RemoveCommand : public Command{
private:
    Task removedTask;
    //the index before the removedTask's index
    int index; 
    int* size;
    TaskList* list;
    TaskDateBST* dateTree;
    TaskTitleBST* titleTree;
public:
    RemoveCommand(Task, int, int*, TaskList*, TaskDateBST*, TaskTitleBST*);
    void undo() override;
};

class EditCommand : public Command{
private:
    //the original task before it was edited
    Task previousTask;
    //the current task that will be switched after undo
    Task currentTask;
    //the index of the task that has been edited
    int index;
    TaskList* list;
    TaskDateBST* dateTree;
    TaskTitleBST* titleTree;
public:
    EditCommand(Task, Task, int, TaskList*, TaskDateBST*, TaskTitleBST*);
    void undo() override;
};

class SwapCommand : public Command{
private:
    int index1;
    int index2;
    TaskList* list;
public:
    SwapCommand(int, int, TaskList*);
    void undo() override;
};

#endif