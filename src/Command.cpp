#include "Command.h"

InsertCommand::InsertCommand(int i, int* s, TaskList* l, TaskDateBST* dt, TaskTitleBST* tt) : 
index(i) , size(s) , list(l) , dateTree(dt) , titleTree(tt) {}

void InsertCommand::undo(){
    //to undo this insert command, the inserted task should be removed
    if(*size == 0) return;
    Task removedTask = list->remove(index);
    dateTree->remove(removedTask);
    titleTree->remove(removedTask);
    --(*size);
}



RemoveCommand::RemoveCommand(Task t, int i, int* s, TaskList* l, TaskDateBST* dt, TaskTitleBST* tt) : 
removedTask(t) , index(i) , size(s) , list(l) , dateTree(dt) , titleTree(tt) {}

void RemoveCommand::undo(){
    //to undo this remove command, the removed task should be inserted
    if(index == 0){
        list->prepend(removedTask);
    }else if(index == *size){
        list->append(removedTask);
    }else{
        list->insertAfter(removedTask , index);
    }
    dateTree->insert(removedTask);
    titleTree->insert(removedTask);
    ++(*size);
}



EditCommand::EditCommand(Task pt, Task ct, int i, TaskList* l, TaskDateBST* dt, TaskTitleBST* tt) : 
previousTask(pt) , currentTask(ct) , index(i) , list(l) , dateTree(dt) , titleTree(tt) {}

void EditCommand::undo(){
    list->replace(previousTask , index);
    dateTree->replace(currentTask , previousTask);
    titleTree->replace(currentTask , previousTask);
}



SwapCommand::SwapCommand(int i1, int i2, TaskList* l) : 
index1(i1) , index2(i2) , list(l) {}

void SwapCommand::undo(){
    list->swap(index1 , index2);
}
