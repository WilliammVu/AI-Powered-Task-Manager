#include "Task.h"

Task::Task() : title(""), description(""), date(Date()) {}

Task::Task(string t, string des, Date dat) : title(t) , description(des) , date(dat) {}

Task::Task(const Task& temp) :
title(temp.title), description(temp.description), date(temp.date) {}

void Task::createTask(){
    string input;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter task title: ";
        getline(cin,input);
        title = input;

        cout << "Enter task description: ";
        getline(cin,input);
        description = input;

        date.createDate();
}

void Task::editTask(){
    string input;

    do{
        cout << "To edit title, enter \"yes\" or \"no\": ";
        cin >> input;
        for(char& c : input)c = tolower(c);
        if(input != "yes"  &&  input != "no"){
            cerr << "\nInvalid input, try again\n\n";
            continue;
        }else break;
    }while(true);
    if(input == "yes"){
        cout << "Enter new title: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin , title);
    }

    do{
        cout << "To edit description, enter \"yes\" or \"no\": ";
        cin >> input;
        for(char& c : input)c = tolower(c);
        if(input != "yes"  &&  input != "no"){
            cerr << "\nInvalid input, try again\n\n";
            continue;
        }else break;
    }while(true);
    if(input == "yes"){
        cout << "Enter new description: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin , description);
    }

    do{
        cout << "To edit date, enter \"yes\" or \"no\": ";
        cin >> input;
        for(char& c : input)c = tolower(c);
        if(input != "yes"  &&  input != "no"){
            cerr << "\nInvalid input, try again\n\n";
            continue;
        }else break;
    }while(true);
    if(input == "yes"){
        cout << "Current date: ";
        date.display(); 
        cout << endl;
        date.createDate();
    }
}

void Task::display() const{
    cout << title << endl;
    cout << "Description:" << endl << description << endl;
    cout << "Date:" << endl; date.display();
}