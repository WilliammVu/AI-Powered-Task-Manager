#include "TaskTitleBST.h"

TaskTitleBST::TaskTitleBST() : root(nullptr) {}

BSTNode* TaskTitleBST::search(string title){
    BSTNode* current = root;
    while(current){
        if(current->task.title < title){
            current = current->right;
        }
        else if(current->task.title > title){
            current = current->left;
        }
        else{
            return current;
        }
    }
    return nullptr;
}

void TaskTitleBST::insert(BSTNode* newNode){
    if (root == nullptr) {
      root = newNode;
   }
   else {
      BSTNode* current = root;
      while (current) {
         if (newNode->task.title < current->task.title) {
            if (current->left == nullptr) {
               current->left = newNode;
               current = nullptr;
            }
            else {
               current = current->left;
            }
         }
         else {
            if (current->right == nullptr) {
               current->right = newNode;
               current = nullptr;
            }
            else {
               current = current->right;
            }
         }
      }
   }
}

bool TaskTitleBST::insert(Task newTask){
    if(search(newTask.title) != nullptr){
        return false;
    }
    BSTNode* newNode = new BSTNode(newTask);
    insert(newNode);
    return true;
}

bool TaskTitleBST::remove(Task target){
    BSTNode* parent = nullptr;
   BSTNode* current = root;

   while (current) {
      if (current->task.title == target.title) {
         if (current->left == nullptr && current->right == nullptr) {
            if (parent == nullptr) {
               root = nullptr;
            }
            else if (parent->left == current) { 
               parent->left = nullptr;
            }
            else {
               parent->right = nullptr;
            }
            delete current;
            return true;
         }
         else if (current->left && current->right == nullptr) {
            // Remove node with only left child
            if (parent == nullptr) {
               root = current->left;
            }
            else if (parent->left == current) {
               parent->left = current->left;
            }
            else {
               parent->right = current->left;
            }
            delete current;
            return true;
         }
         else if (current->left == nullptr && current->right) {
            // Remove node with only right child
            if (parent == nullptr) {
               root = current->right;
            }
            else if (parent->left == current) {
               parent->left = current->right;
            }
            else {
               parent->right = current->right;
            }
            delete current;
            return true;
         }
         else {
            // Remove node with two children
            BSTNode* successor = current->right;
            while (successor->left) {
               successor = successor->left;
            }
            current->task = successor->task;
            parent = current;

            current = current->right;
            target = successor->task;
         }
      }
      else if (current->task.title < target.title) {
         parent = current;
         current = current->right;
      }
      else {
         parent = current;
         current = current->left;
      }
   }
   return false;
}

void TaskTitleBST::displayInOrder() const{
    int index = 1;
    displayInOrder(root,index);
}

void TaskTitleBST::displayInOrder(BSTNode* current, int& index) const{
    if(current == nullptr) return;

    displayInOrder(current->left,index);

    cout << "[" << index << ']' << endl;
    ++index;
    current->task.display();
    cout << endl << endl;

    displayInOrder(current->right,index);
}

void TaskTitleBST::replace(Task oldTask, Task newTask){
    BSTNode* current = root;
    while(current){
        if(oldTask.title < current->task.title){
            current = current->left;
        }else if(oldTask.title > current->task.title){
            current = current->right;
        }else{
            current->task = newTask;
            return;
        }
    }
}