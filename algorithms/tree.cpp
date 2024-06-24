 #pragma once
 #include <iostream>
 #include <string>

 struct TreeNode 
 {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    static void printTree(const std::string& prefix, const TreeNode* node, bool isLeft)
    {
        if( node != nullptr )
        {
            std::cout << prefix;

            std::cout << (isLeft ? "├──" : "└──" );

            // print the value of the node
            std::cout << node->val << std::endl;

            // enter the next tree level - left and right branch
            printTree( prefix + (isLeft ? "│   " : "    "), node->left, true);
            printTree( prefix + (isLeft ? "│   " : "    "), node->right, false);
        }
}
 };