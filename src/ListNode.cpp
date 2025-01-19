#include "ListNode.h"

ListNode::ListNode() : previous(nullptr),next(nullptr),task() {}

ListNode::ListNode(Task t) : previous(nullptr),next(nullptr),task(t) {}