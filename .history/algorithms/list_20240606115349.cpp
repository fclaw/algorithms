#include <ios>

struct ListNode 
{
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
  public:
    void print()
    {
        auto ptr = this;
        do
        {
            std::cout << ptr->val << (ptr->next == nullptr ? " " : " -> ");
            ptr = ptr->next;
            
        }while(ptr != nullptr);
    }
};