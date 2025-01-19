#ifndef LISTNODE_H
#define LISTNODE_H

#include "Task.h"

class ListNode{
public:
    Task task;
    ListNode* previous;
    ListNode* next;
    ListNode();
    ListNode(Task);
};

#endif