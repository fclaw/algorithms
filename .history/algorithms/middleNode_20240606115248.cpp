// https://leetcode.com/problems/middle-of-the-linked-list
ListNode* middleNode(ListNode* head) 
{
     auto one_step_ptr = head;
     auto two_step_ptr = head->next;
     while(two_step_ptr != nullptr)
     {
        one_step_ptr = one_step_ptr->next;
        two_step_ptr = two_step_ptr->next != nullptr ? two_step_ptr->next->next : nullptr;
     }
     return one_step_ptr;
}