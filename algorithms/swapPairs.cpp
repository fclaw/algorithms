#include "list.cpp"

// https://leetcode.com/problems/swap-nodes-in-pairs 
// Given a linked list, swap every two adjacent nodes and return its head. 
// You must solve the problem without modifying the values in the list's nodes (i.e., only nodes themselves may be changed.)
// Use a dummy node to handle edge cases easily (like when the list length is odd).
// Use pointers to keep track of the previous node (prev), the current node (first), and the next node (second).
ListNode* swapPairs(ListNode* head) 
{
    ListNode* dummy = new ListNode();
    dummy->next = head;

    auto prev = dummy;
    auto first = head;

    while(first != nullptr && 
          first->next != nullptr)
    {
        //init
        auto second = first->next;

        // swap
        auto tmp = second->next;
        prev->next = second;
        second->next = first;
        first->next = tmp;

        // next
        prev = first;
        first = tmp;
    }

    return dummy->next;
}