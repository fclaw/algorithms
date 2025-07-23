/*
───────────────────────────────────────────────────────────────
🧳 UVa 548 Tree, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "tools/tree.cpp"
#include <bits/stdc++.h>


namespace tree = algorithms::onlinejudge::graph::tools::tree;


void backtrack(tree::Tree<>* tree, int acc, int& leaf, int& min_path_value) {
    
    if(tree == nullptr) return;

    if(!(tree->left) && 
        !(tree->right)) {
      acc += tree->val;
      if(acc < min_path_value) {
        leaf = tree->val;
        min_path_value = acc;
      }
      return;
    }

    if(tree->left) {
      backtrack(tree->left, acc + tree->val, leaf, min_path_value);
    }
    if(tree->right) {
      backtrack(tree->right, acc + tree->val, leaf, min_path_value);
    }
  }


namespace algorithms::onlinejudge::graph::tree_recovery_2
{
    /** https://onlinejudge.org/external/5/548.pdf */
    std::string in_order, post_order;
    tree::Tree<>* restore_from_postorder_inorder(size_t& pos, const std::string& inorder) {

      if(pos >= in_order.size()) return nullptr;

      if(inorder.size() == 1) {
        return new tree::Tree<>(pos++, inorder.front() - '0');
      } else {
        char label = post_order[pos];
        int v = label - '0';
        tree::Tree<>* tree = new tree::Tree<>(pos, v);
        size_t root_pos = inorder.find(label);
        pos++;
        auto left = inorder.substr(0, root_pos);
        if(!left.empty()) tree->left = restore_from_postorder_inorder(pos, left);
        auto right = inorder.substr(root_pos + 1, inorder.size() - (root_pos + 1));
        if(!right.empty()) tree->right = restore_from_postorder_inorder(pos, right);
        return tree;
      }

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
        
        std::string s;  
        while(std::getline(std::cin, s)) {
          for(int i = 0; i < (int)s.size(); ++i) {
            if(std::isdigit(s[i])) {
              in_order.push_back(s[i]);
            }
          }
          std::getline(std::cin, s);
          for(int i = 0; i < (int)s.size(); ++i) {
            if(std::isdigit(s[i])) {
              post_order.push_back(s[i]);
            }
          }

          std::reverse(post_order.begin(), post_order.end());
          size_t pos = 0;
          tree::Tree<>* tree = restore_from_postorder_inorder(pos, in_order);
          int leaf = 0;
          int min_path_value = INT32_MAX;
          backtrack(tree, 0, leaf, min_path_value);
          std::cout << leaf << std::endl;
        }
    }
}