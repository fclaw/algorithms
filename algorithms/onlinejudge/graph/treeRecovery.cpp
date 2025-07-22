/*
───────────────────────────────────────────────────────────────
🧳 UVa 536 Tree Recovery, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


struct Tree
{
    int node;
    char label;
    Tree* left = nullptr; 
    Tree* right = nullptr;
    Tree(int node, char label) {
      this->node = node;
      this->label = label;
    }
};


namespace algorithms::onlinejudge::graph::tree_recovery
{
    /** https://onlinejudge.org/external/5/536.pdf */
    std::string preorder_s, inorder_s; 
    Tree* restore_from_preorder_inorder(int& pos, const std::string& inorder) {

      if(pos >= (int)preorder_s.size()) return nullptr;

      if(inorder.size() == 1) {
        return new Tree(pos++, inorder.front());
      } else {
        char label = preorder_s[pos];
        Tree* tree = new Tree(pos, label);
        size_t root_pos = inorder.find(label);
        pos++;
        auto left = inorder.substr(0, root_pos);
        if(!left.empty()) tree->left = restore_from_preorder_inorder(pos, left);
        auto right = inorder.substr(root_pos + 1, inorder.size());
        if(!right.empty()) tree->right = restore_from_preorder_inorder(pos, right);
        return tree;
      }

    }
    void do_postorder(Tree* tree, std::string& tree_s) {

       if(tree == nullptr) return;

       do_postorder(tree->left, tree_s);
       do_postorder(tree->right, tree_s);

       char label = tree->label;
       tree_s.push_back(label);
    }
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value())
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }  
        while(while_read(preorder_s, inorder_s)) {
          int pos = 0;
          Tree* tree = restore_from_preorder_inorder(pos, inorder_s);
          std::string tree_s;
          do_postorder(tree, tree_s);
          std::cout << tree_s << std::endl;
        }
    }
}