 /*
 ─────────────────────────────────────────────────────────────── 
 🧳 UVa 12347 Binary Search Tree, rt: s
 ───────────────────────────────────────────────────────────────
 */

#include "../debug.h"
#include "../../aux.h"
#include "tools/tree.cpp"
#include <bits/stdc++.h>



namespace tree = algorithms::onlinejudge::graph::tools::tree;


using vi = std::vector<int>;

void build_bst(int key, tree::Tree<>* bst) {
  if(bst->val == tree::def<>) {
    bst->val = key;
    return;
  }

  if(bst->val > key) {
    if(!(bst->left)) bst->left = new tree::Tree<>();
    build_bst(key, bst->left);
  } else if(bst->val < key) {
    if(!(bst->right)) bst->right = new tree::Tree<>();
    build_bst(key, bst->right);
  }
}

void do_postorder(tree::Tree<>* bst) {
  if(bst == nullptr) return;

  do_postorder(bst->left);
  do_postorder(bst->right);
  std::cout << bst->val << std::endl;
}

namespace algorithms::onlinejudge::graph::bst
{
    /** https://onlinejudge.org/external/123/12347.pdf */
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
        
        int key;  
        vi keys;  
        tree::Tree<>* bst = new tree::Tree<>();  
        while(while_read(key)) keys.push_back(key);
        for(int k : keys) build_bst(k, bst);
        do_postorder(bst);
    }
}