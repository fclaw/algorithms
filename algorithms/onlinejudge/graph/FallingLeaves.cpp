 /*
 ─────────────────────────────────────────────────────────────── 
 🧳 UVa 699 The Falling Leaves, rt: s
 ───────────────────────────────────────────────────────────────
 */

#include "../debug.h"
#include "../../aux.h"
#include "tools/tree.cpp"
#include <bits/stdc++.h>



namespace tree = algorithms::onlinejudge::graph::tools::tree;

constexpr int empty = -1;

int val;

void build_tree(tree::Tree<>* root) {
  while_read(val);
  if(val != empty) {
    root->left = new tree::Tree<>(val);
    build_tree(root->left);
  }
  while_read(val);
  if(val != empty) {
    root->right = new tree::Tree<>(val);
    build_tree(root->right);
  }
}

void count_leaves(
  int shift_x_axis,
  tree::Tree<>* tree,
  std::map<int, int>& heaps) {
  
  if(tree == nullptr) return;

  heaps[shift_x_axis] += tree->val;
  count_leaves(shift_x_axis - 1, tree->left, heaps);
  count_leaves(shift_x_axis + 1, tree->right, heaps);
}


namespace algorithms::onlinejudge::graph::falling_leaves
{
    /** https://onlinejudge.org/external/6/699.pdf */
    int t_cases = 1;
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
        
        while(while_read(val) && val != empty) {
  
          tree::Tree<>* tree = new tree::Tree<>(val);
          build_tree(tree);
          std::map<int, int> heaps;
          count_leaves(0, tree, heaps);
          std::string ans;
          for(auto& h : heaps) {
            ans += std::to_string(h.second) + " ";
          }
          ans.pop_back();
          printf("Case %d:\n%s\n\n", t_cases++, ans.c_str());
        }
    }
}