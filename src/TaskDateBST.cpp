#include "TaskDateBST.h"

TaskDateBST::TaskDateBST() : root(nullptr) {}

BSTNode* TaskDateBST::search(Date date){
    BSTNode* current = root;
    while(current){
        if(current->task.date < date){
            current = current->right;
        }
        else if(current->task.date > date){
            current = current->left;
        }
        else{
            return current;
        }
    }
    return nullptr;
}

void TaskDateBST::insert(BSTNode* newNode){
    if (root == nullptr) {
      root = newNode;
   }
   else {
      BSTNode* current = root;
      while (current) {
         if (newNode->task.date < current->task.date) {
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

bool TaskDateBST::insert(Task newTask){
    if(search(newTask.date) != nullptr){
        return false;
    }
    BSTNode* newNode = new BSTNode(newTask);
    insert(newNode);
    return true;
}

bool TaskDateBST::remove(Task target){
    BSTNode* parent = nullptr;
   BSTNode* current = root;

   while (current) {
      if (current->task.date == target.date) {
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
      else if (current->task.date < target.date) {
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

void TaskDateBST::displayInOrder() const{
    int index = 1;
    displayInOrder(root,index);
}

void TaskDateBST::displayInOrder(BSTNode* current, int& index) const{
    if(current == nullptr) return;

    displayInOrder(current->left,index);

    cout << "[" << index << ']' << endl;
    current->task.display();
    cout << endl << endl;

    ++index;

    displayInOrder(current->right,index);
}

void TaskDateBST::replace(Task oldTask, Task newTask){
    BSTNode* current = root;
    while(current){
        if(oldTask.date < current->task.date){
            current = current->left;
        }else if(oldTask.date > current->task.date){
            current = current->right;
        }else{
            current->task = newTask;
            return;
        }
    }
}