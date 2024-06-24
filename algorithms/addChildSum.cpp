#include "tree.cpp"

namespace algorithms::tree
{
    void addChildSum(TreeNode* node)
    {
        if(node == nullptr)
          return;

        int sum = 0; 

        addChildSum(node->left);
        addChildSum(node->right);
       
        if(node->left != nullptr)
          sum += node->left->val;

        if(node->right != nullptr)
          sum += node->right->val;  

        node->val += sum;
    }
}

