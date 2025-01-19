#ifndef TASKLIST_H
#define TASKLIST_H

#include "ListNode.h"

//doubly-linked list
class TaskList{
private:
    ListNode* head;
    ListNode* tail;
public:
    TaskList();
    void prepend(Task);
    void append(Task);
    Task remove(int index);
    void insertAfter(Task newTask, int index);
    void swap(int indexOne, int indexTwo);
    Task at(int index);
    Task edit(int index);
    void display() const;
    void replace(Task, int index);
private:
    //helper functions
    void prepend(ListNode* newNode);
    void append(ListNode* newNode);
    ListNode* search(Task) const;
    void remove(ListNode* target);
    void insertAfter(ListNode* current, ListNode* newNode);
    void swap(pair<ListNode*,ListNode*>);
};

#endif