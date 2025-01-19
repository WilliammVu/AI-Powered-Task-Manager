#ifndef TASK_H
#define TASK_H

#include "Date.h"
using namespace std;

class Task{
public:
    string title;
    string description;
    Date date;

    Task();
    Task(string t, string des, Date dat);
    Task(const Task&);
    void createTask();
    void editTask();
    void display() const;
};

#endif