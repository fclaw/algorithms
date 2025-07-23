/*
───────────────────────────────────────────────────────────────
🧳 UVa 548 Tree, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "tools/tree.cpp"
#include <bits/stdc++.h>


using vi = std::vector<int>;


namespace tree = algorithms::onlinejudge::graph::tools::tree;


void backtrack(tree::Tree<>* tree, int acc, int& leaf, int& min_path_value) {
    
    if(tree == nullptr) return;

    if(!(tree->left) && 
        !(tree->right)) {
      acc += tree->val;
      if(acc < min_path_value) {
        leaf = tree->val;
        min_path_value = acc;
      } else if(acc == min_path_value) {
        leaf = std::min(leaf, tree->val);
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
    vi inorder, postorder;
    std::unordered_map<int, int> inorder_positions;
    tree::Tree<>* restore_tree(size_t root_start, size_t l, size_t r) {

      if(l >= r) return nullptr;

      int root_label = postorder[root_start];
      tree::Tree<>* tree = new tree::Tree<>(root_label, root_start);

      size_t m = inorder_positions.at(root_label);
      size_t right_size = r - m - 1;
      tree->left = restore_tree(root_start - right_size - 1, l, m);
      tree->right = restore_tree(root_start - 1, m + 1, r);
      return tree;
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
          int v;
          inorder_positions.clear();
          inorder.clear();
          postorder.clear();
          std::stringstream ss_in(s);
          while(ss_in >> v) { inorder.push_back(v); }

          std::getline(std::cin, s);
          std::stringstream ss_post(s);
          while(ss_post >> v) { postorder.push_back(v); }

          // Pre-compute inorder positions for O(1) lookups
          for (int i = 0; i < (int)inorder.size(); ++i) {
            inorder_positions[inorder[i]] = i;
          }

          tree::Tree<>* tree = restore_tree(postorder.size() - 1, 0, inorder.size());
          int leaf = 0;
          int min_path_value = INT32_MAX;
          backtrack(tree, 0, leaf, min_path_value);
          std::cout << leaf << std::endl;
        }
    }
}