#include "TaskManager.h"

void printNewLines(int n){
    for(int i=0;i<n;++i){
        cout << endl;
    }
}

int main(){
    TaskManager manager;
    cout << "Welcome to the Task Management System!" << endl << endl;
    cout << "Info: Duplicate Tasks are not accepted." << endl;
    cout << "      The Task List is 1-indexed," << endl;
    cout << "      so the index of the first task is 1, not 0" << endl << endl;
    cout << "To get started, let's create your first task." << endl;
    cout << "Press enter to get started" << endl << endl;
    Task firstTask;
    firstTask.createTask();
    manager.append(firstTask);
    printNewLines(3);

    bool runProgram = true;
    while(runProgram){
        manager.display(); printNewLines(2);

        cout << "Enter any key to open options: " << endl;
        string openOptions;
        cin >> openOptions; cout << endl;

        cout << "Options:" << endl;
        cout << "Ask your AI personal assistant Using Natural Language [1]" << endl;
        cout << "Add Task to Beginning [2]" << endl;
        cout << "Add Task to End [3]" << endl;
        cout << "Add Task Somewhere Else Inside the List [4]" << endl;
        cout << "Remove a Task [5]" << endl;
        cout << "Swap Two Tasks [6]" << endl;
        cout << "Edit a Task [7]" << endl;
        cout << "Search for a Task by Date [8]" << endl;
        cout << "Search for a Task by Title [9]" << endl;
        cout << "View Tasks in Chronological Order [10]" << endl;
        cout << "View Tasks in Alphabetical Order [11]" << endl;
        cout << "Undo Previous insert/remove/swap/edit Command [12]" << endl;
        cout << "Exit Program [13]" << endl;

        int input;

        do{
            cout << "ENTER HERE (1-13): ";
            cin >> input;
            if(!validate_cin()){
                cerr << "ERROR: INVALID INPUT, TRY AGAIN" << endl;
                continue;
            }
            if(input < 1  ||  input > 13){
                cerr << "Invalid number, please try again" << endl;
                continue;
            }
            break;
        }while(true);

        switch(input){
            case 1: {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string naturalLanguageQuery;
                //Natural Language Processing to create, delete, or edit an existing task
                cout << "Hello! I'm here to help you manage your tasks and keep up with your important deadlines! How can I assist you?" << endl;
                cout << "Message your assistant: ";
                while(true){
                    getline(cin, naturalLanguageQuery);
                    if(naturalLanguageQuery.length() > 250){
                        cout << "\nYou have exceeded your character limit. Try again\n\n";
                        continue;
                    }
                    break;
                }

                ofstream outputFile("transfer.txt", ios::out | ios::trunc);
                if(!outputFile){
                    cerr << "ERROR: Wrong file name/path for the transfer file" << endl;
                    break;
                }

                //not sure if this could just be outputFile << naturalLanguageQuery
                stringstream ss(naturalLanguageQuery);
                string word;
                while(ss >> word){
                    outputFile << word << ' ';
                }
                outputFile.close();

                //run python script 'NLP.py'
                system("python3 NLP.py");
                
                
                string operation, taskNumber, title, description, month,day,year,hour,minute,AmPm;
                ifstream jsonInfo("transfer.txt");
                if(!jsonInfo){
                    cerr << "\nIncorrect input file name/path\n\n";
                }
                getline(jsonInfo,operation);
                getline(jsonInfo,taskNumber);
                getline(jsonInfo,title);
                getline(jsonInfo,description);
                getline(jsonInfo,month);
                getline(jsonInfo,day);
                getline(jsonInfo,year);
                getline(jsonInfo,hour);
                getline(jsonInfo,minute);
                getline(jsonInfo,AmPm);

                 
                if(operation == "create"){
                    Task newTask;
                    newTask.title = title; newTask.description = description;

                    Date newDate;
                    if(month == "null" || day == "null" || year == "null" || hour == "null" || minute == "null" || AmPm =="null"){
                        cout << "\nSorry, I couln't decipher your date info since some info was missing.\n\n";
                        newDate.createDate();
                    }else{
                        bool am = (AmPm == "AM") ? true : false;
                        newDate = Date(stoi(month),stoi(day),stoi(year),stoi(hour),stoi(minute),stoi(AmPm));
                    } newTask.date = newDate;

                    if(taskNumber != "null"){
                        int tNum = stoi(taskNumber);
                        if(tNum < 1 || tNum > manager.length()){
                            manager.append(newTask);
                        }else{
                            manager.insertAfter(newTask,tNum);
                        }
                    }
                    else{
                        manager.append(newTask);
                    }
                    cout << "\nYour new task has been added! Let me know if you require any further assitance.\n\n";
                }
                else if(operation == "remove"){
                    int taskNum;
                    if(taskNumber == "null"){
                        cout << "The task number could not be deciphered, please enter: ";
                        cin >> taskNum;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }else taskNum = stoi(taskNumber);
                    
                    cout << endl;
                    while(taskNum < 1 || taskNum > manager.length()){
                        cerr << "Out-of-bounds task number, try again: ";
                        cin >> taskNum;
                    } cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    manager.remove(taskNum);
                    cout << "\nYour task removal request has been completed!\n\n";
                }
                else{
                    cerr << "\nYour input could not be interpreted; unclear/unsupported task operation\n\n";
                }
                
                break;
            }
            case 2: {
                //Task insertion at list start
                Task newTask;
                newTask.createTask();
                manager.prepend(newTask);
                break;
            }
            case 3: {
                //Task insertion at list end
                Task newTask;
                newTask.createTask();
                manager.append(newTask);
                break;
            }
            case 4: {
                //Task insertion after a certain index
                int index;
                while(true){
                    cout << "After which index will the task be inserted? ";
                    cin >> index;
                    if(!validate_cin()){
                        cerr << "Enter a valid number, Try again" << endl;
                        continue;
                    }
                    if(index < 1  ||  index > manager.length()){
                        cerr << "Invalid index, Try again" << endl;
                        continue;
                    }
                    break;
                }

                Task newTask;
                newTask.createTask();
                manager.insertAfter(newTask, index);
                break;
            }
            case 5: {
                //Task Removal
                if(manager.length() == 0){
                    cerr << "Task manager is empty, cannot remove task" << endl;
                    break;
                }
                int index;
                do{
                    cout << "Enter the task number for removal: ";
                    cin >> index;
                    if(!validate_cin()){
                        cerr << "Enter a valid number, Try again" << endl;
                        continue;
                    }
                    if(index < 1  ||  index > manager.length()){
                        cerr << "Invalid index, Try again" << endl;
                        continue;
                    }
                    break;
                }while(true);

                manager.remove(index);
                if(manager.length() == 0){
                    cout << "The manager is now empty. You must now create a task" << endl;
                    Task newTask;
                    newTask.createTask();
                    manager.prepend(newTask);
                }
                break;
            }
            case 6: {
                //Swap two tasks
                int index1, index2;
                while(true){
                    cout << "Enter index #1: ";
                    cin >> index1;
                    if(!validate_cin()){
                        cerr << "Enter input as integers. Try again." << endl;
                        continue;
                    }
                    if(index1 < 1  ||  index1 > manager.length()){
                        cerr << "invalid task number, try again" << endl;
                        continue;
                    }
                    break;
                }
                while(true){
                    cout << "Enter index #2: ";
                    cin >> index2;
                    if(!validate_cin()){
                        cerr << "Enter input as integers. Try again." << endl;
                        continue;
                    }
                    if(index2 < 1  ||  index2 > manager.length()){
                        cerr << "invalid task number, try again" << endl;
                        continue;
                    }
                    break;
                }
                manager.swap(index1 , index2);
                break;
            }
            case 7: {
                //edit a task
                int index;
                while(true){
                    cout << "Enter the index of the task you wish to edit: ";
                    cin >> index;
                    if(!validate_cin()){
                        cerr << "ERROR: Please enter a number" << endl;
                        continue;
                    }
                    if(index < 1  ||  index > manager.length()){
                        cerr << "Invalid task number, try again" << endl;
                        continue;
                    }
                    break;
                }
                manager.edit(index);
                break;
            }
            case 8: {
                //search for a task by date
                Date d;
                d.createDate();
                Task* t = manager.search(d);
                if(t == nullptr){
                    cerr << "No task with this date exists" << endl;
                }else{
                    printNewLines(5);
                    t->display();
                    printNewLines(2);
                    string exitInput;
                    cout << "Enter any key to exit task view: ";
                    cin >> exitInput;
                }
                break;
            }
            case 9: {
                //search for a task by title
                string s;
                cout << "Enter task title for search: ";

                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                getline(cin,s);
                if(s.back() == '\n'){
                    s.pop_back();
                }
                cout << "FOR DEBUGGING PURPOSES (end one NL): " << s << endl;
                Task* t = manager.search(s);

                if(t == nullptr){
                    cerr << "No task with this title exists" << endl;
                    string contInput;
                    cout << "Enter any key to continue: ";
                    cin >> contInput;
                }
                else{
                    printNewLines(5);
                    t->display();
                    printNewLines(2);
                    string exitInput;
                    cout << "Enter any key to exit task view: ";
                    cin >> exitInput;
                }
                break;
            }
            case 10: {
                //Display dates chronologically
                printNewLines(2);
                manager.displayByDate();
                string exitInput;
                cout << "Enter any key to exit chronological view: ";
                cin >> exitInput;
                break;
            }
            case 11: {
                //Display dates alphabetically
                printNewLines(2);
                manager.displayByTitle();
                string exitInput;
                cout << "Enter any key to exit alphabetical view: ";
                cin >> exitInput;
                break;
            }
            case 12: {
                //Undo Command
                manager.undo();
                break;
            }
            case 13: {
                //exit program;
                runProgram = false;
                break;
            }
            default: {
                //this will not occur since input validation was conducted before
                cerr << endl << "An Error Occurred" << endl;
                break;
            }
        }
        printNewLines(3);
    }
    
    cout << "Program Finished";
    printNewLines(5);
    return 0;
}