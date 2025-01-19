#include "TaskList.h"

TaskList::TaskList() : head(nullptr) , tail(nullptr) {}

void TaskList::prepend(ListNode* newNode){
    if(head == nullptr){
        head = newNode;
        tail = newNode;
    }
    else{
        newNode->next = head;
        head->previous = newNode;
        head = newNode;
    }
}

void TaskList::prepend(Task t){
    ListNode* newNode = new ListNode(t);
    prepend(newNode);
}

void TaskList::append(ListNode* newNode){
    if(head==nullptr){
        head = newNode;
        tail = newNode;
    }
    else{
        newNode->previous = tail;
        tail->next = newNode;
        tail = newNode;
    }
}

void TaskList::append(Task t){
    ListNode* newNode = new ListNode(t);
    append(newNode);
}

ListNode* TaskList::search(Task t) const{
    ListNode* current = head;
    while(current){
        if(current->task.title == t.title || current->task.date == t.date){
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void TaskList::remove(ListNode* target){
    ListNode* predecessor = target->previous;
    ListNode* successor = target->next;
    if(successor){
        successor->previous = predecessor;
    }
    if(predecessor){
        predecessor->next = successor;
    }
    if(target == head){
        head = successor;
    }
    if(target == tail){
        tail = predecessor;
    }
    delete target;
}

Task TaskList::remove(int index){
    //assumes index <= the number of nodes
    //the fifth node corresponds to index = 5
    ListNode* current = head;
    int i = 1;
    while(i < index){
        current = current->next;
        ++i;
    }
    Task temp = current->task;
    remove(current);
    return temp;
}

void TaskList::insertAfter(ListNode* current, ListNode* newNode){
    if(head == nullptr){
        head = newNode;
        tail = newNode;
    }
    else if(current == tail){
        newNode->previous = tail;
        tail->next = newNode;
        tail = newNode;
    }
    else{
        ListNode* successor = current->next;
        newNode->next = successor;
        newNode->previous = current;
        current->next = newNode;
        successor->previous = newNode;
    }
}

void TaskList::insertAfter(Task newTask,int index){
    ListNode* current = head;
    int i = 1;
    while(i < index){
        current = current->next;
        ++i;
    }
    ListNode* newNode = new ListNode(newTask);
    insertAfter(current, newNode);
}

void TaskList::swap(pair<ListNode*,ListNode*> pair){
    std::swap(pair.first->task , pair.second->task);
}

void TaskList::swap(int index1 , int index2){
    //assumes index1 and index2 are valid.
    //checking index1 and index2 is done in TaskManager class
    int index = 1;
    ListNode* current = head;
    ListNode* node1, *node2;
    while(index <= max(index1,index2)){
        if(index == index1){
            node1 = current;
        }
        else if(index == index2){
            node2 = current;
        }
        current = current->next;
        ++index;
    }
    pair<ListNode*,ListNode*> p(node1, node2);
    swap(p);
}

Task TaskList::at(int index){
    //checking whether index is valid is done in TaskManager class
    int i = 1;
    ListNode* current = head;
    while(current && i < index){
        ++i;
        current = current->next;
    }
    return current->task;
}

Task TaskList::edit(int index){
    Task newTask;
    int i = 1;
    ListNode* current = head;
    while(current && i < index){
        ++i;
        current = current->next;
    }
    current->task.editTask();
    newTask = current->task;
    return newTask;
}

void TaskList::display() const{
    ListNode* current = head;
    int index = 1;
    while(current){
        cout << '[' << index << ']' << endl;
        current->task.display();
        cout << endl << endl;
        ++index;
        current = current->next;
    }
}

void TaskList::replace(Task newTask, int index){
    int i = 1;
    ListNode* current = head;
    while(current && i < index){
        current = current->next;
        ++i;
    }
    current->task = newTask;
}