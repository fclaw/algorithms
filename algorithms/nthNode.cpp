#include "list.cpp"

// https://leetcode.com/problems/remove-nth-node-from-end-of-list
// Given the head of a linked list, remove the nth node from the end of the list and return its head
ListNode* removeNthFromEnd(ListNode* head, int n)
{
    if(head == nullptr || head->next == nullptr)
       return nullptr;

     auto first = head;
     int i = n;

     while(first->next != nullptr && i > 0)
     {
       first = first->next;
       i--;
     };

    if(i > 0)
    {
       auto second = head;
       while(i-- > 0)
          second = second->next;
       head = second;   
    }
    else if(first == nullptr)
      head->next = nullptr;  
    else 
    {
       auto second = head;
       first = first->next;
       while(first != nullptr)
       {
           second = second->next;
           first = first->next;
       };

       auto tmp = second->next;
       second->next = tmp->next;
    }

    return head;
}
