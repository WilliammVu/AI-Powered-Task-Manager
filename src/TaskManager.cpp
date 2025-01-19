#include "TaskManager.h"

TaskManager::TaskManager() : size(0), list(),commandStack(), titleTree(), dateTree() {}

int TaskManager::length() const{
    return size;
}

bool TaskManager::prepend(Task t){
    if(!dateTree.insert(t)) return false;
    ++size;
    list.prepend(t);
    titleTree.insert(t);
    commandStack.push(new InsertCommand(1, &size, &list, &dateTree, &titleTree));
    return true;
}

bool TaskManager::append(Task t){
    if(!dateTree.insert(t)) return false;

    ++size;
    list.append(t);
    titleTree.insert(t);

    commandStack.push(new InsertCommand(size, &size, &list, &dateTree, &titleTree));

    return true;
}

bool TaskManager::insertAfter(Task t, int index){
    if(dateTree.search(t.date) != nullptr) return false;
    if(index < 1 || index > size) return false;

    list.insertAfter(t , index);
    dateTree.insert(t);
    titleTree.insert(t);
    ++size;

    commandStack.push(new InsertCommand(index, &size, &list, &dateTree, &titleTree));

    return true;
}

bool TaskManager::remove(int index){
    if(index < 1  ||  index > size) return false;

    Task removedTask = list.remove(index);
    dateTree.remove(removedTask);
    titleTree.remove(removedTask);
    --size;

    commandStack.push(new RemoveCommand(removedTask, index-1, &size, &list, &dateTree, & titleTree));

    return true;
}

bool TaskManager::swap(int index1, int index2){
    if(index1 == index2)return false;
    if(index1 < 1  ||  index1 > size) return false;
    if(index2 < 1  ||  index2 > size) return false;

    list.swap(index1,index2);

    commandStack.push(new SwapCommand(index1, index2, &list));

    return true;
}

bool TaskManager::edit(int index){
    if(index < 1  || index > size) return false;

    Task editedTask = list.at(index);

    Task newTask = list.edit(index);
    dateTree.replace(editedTask, newTask);
    titleTree.replace(editedTask, newTask);

    commandStack.push(new EditCommand(editedTask, newTask, index, &list, &dateTree, &titleTree));

    return true;
}

Task* TaskManager::search(Date date){
    if(dateTree.search(date) == nullptr){
        return nullptr;
    }

    Task* t = new Task(dateTree.search(date)->task);
    return t;
}

Task* TaskManager::search(string title){
    if(titleTree.search(title) == nullptr){
        return nullptr;
    }

    Task* t = new Task(titleTree.search(title)->task);
    return t;
}

void TaskManager::display() const{
    list.display();
}

void TaskManager::displayByDate() const{
    dateTree.displayInOrder();
}

void TaskManager::displayByTitle() const{
    titleTree.displayInOrder();
}

void TaskManager::undo(){
    if(commandStack.empty()) return;

    commandStack.top()->undo();
    commandStack.pop();
}