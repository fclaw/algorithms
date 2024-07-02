#include "list.cpp"

namespace algorithms::linkedlist
{
    // https://leetcode.com/problems/linked-list-cycle
    /*
    To check if a linked list has a cycle, you can use Floyd's Tortoise and Hare algorithm, which is a two-pointer technique. 
    This approach involves using two pointers that traverse the list at different speeds. 
    If there is a cycle, the faster pointer will eventually meet the slower pointer
    */
    bool hasCycle(ListNode *head) 
    {
        auto one_step_ptr = head;
        auto two_step_ptr = head->next;
        auto isCycle = false;
        while(two_step_ptr != nullptr)
        {
            if(one_step_ptr == two_step_ptr)
            {
                isCycle = true;
                break;
            }
            one_step_ptr = one_step_ptr->next;
            two_step_ptr = two_step_ptr->next != nullptr ? two_step_ptr->next->next : nullptr;
        }

        return isCycle;
    }
}