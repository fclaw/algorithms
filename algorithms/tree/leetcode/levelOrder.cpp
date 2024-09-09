#include <vector>
#include <queue>

namespace algorithms::tree::leetcode::level_order
{

    /**
     * https://leetcode.com/problems/binary-tree-level-order-traversal
     * Given the root of a binary tree, return the level order traversal of its nodes' values. 
     * (i.e., from left to right, level by level) */
    std::vector<std::vector<int>> levelOrder(TreeNode* root)
    {
        if(root == nullptr)
          return {};
        else 
        {
            std::vector<std::vector<int>> ans;
            std::queue<std::pair<TreeNode*, int>> q;
            q.push({root, 0});
            while(!q.empty())
            {
                auto v = q.front();
                q.pop();
                if(ans.begin() + v.second == ans.end())
                    ans.push_back({});

                ans[v.second].push_back(v.first->val);
                if(v.first->left != nullptr) q.push({v.first->left, v.second + 1});
                if(v.first->right != nullptr) q.push({v.first->right, v.second + 1});
            }
            return ans;
        }
    }
}