/*
───────────────────────────────────────────────────────────────
🧳 UVa 11782 Optimal Cut, rt: s
───────────────────────────────────────────────────────────────
// dp[node_id][k]
vector<vector<int>> dp;

void solve(Tree* u) {
    if (u == nullptr) return;

    // Post-order traversal: solve for children first
    solve(u->left);
    solve(u->right);

    // --- DP Calculation for node u ---
    
    // Case 1: The cut in u's subtree includes u itself.
    // This is a valid cut of size 1 for the subtree.
    dp[u->id][1] = u->w;

    // Case 2: The cut is formed by combining cuts from the children.
    if (u->left && u->right) {
      for(int k_left = 1; k_left <= K; ++k_left) {
        int k_right = K - k_left;
        // Combine a k_left-node cut from the left 
        // and a k_right-node cut from the right
        dp[u->id][k_left + k_right] = 
          std::max(dp[u->id][k_left + k_right],
                   dp[u->left->id][k_left] + 
                   dp[u->right->id][k_right]);
      }
    }
    // (Also handle cases where only one child exists)
}

// Initial call:
// solve(root);
// The final answer is max(dp[root][k] for k from 1 to K)

*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vvvi = std::vector<vvi>;
using ll = long long;

constexpr int inf = 1e5;


struct Tree
{
    int node;
    int w;
    std::array<int, 21> dp = 
      {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
       -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    Tree* left = nullptr; 
    Tree* right = nullptr;
    Tree(int node, int w) {
      this->node = node;
      this->w = w;
    }
};


namespace algorithms::onlinejudge::graph::optimal_cut
{
    /** https://onlinejudge.org/external/117/11782.pdf */
    int t_cases, height, k;
    Tree* restore_from_preorder(int d, int& pos, const vi& weights) {
      int s = (int)weights.size();
      if(pos >= s || d > height) return nullptr;

      Tree* tree = new Tree{pos, weights[pos]};
      pos++;
      // Recursively build the left and right subtrees.
      tree->left = restore_from_preorder(d + 1, pos, weights);
      tree->right = restore_from_preorder(d + 1, pos, weights);
    return tree;

    }
    int do_optimal_cut(Tree* tree, int taken) {   
      if(tree == nullptr) {
        // null tree contributes 0 value, but it is only valid if we
        // also don't need to take any nodes from it.
        return (taken == 0) ? 0 : -inf;
      }
      if(taken == 0) {
        // We are at a real tree but have no budget. Impossible.
        return -inf;
      }

      if(~((tree->dp)[taken])) return (tree->dp)[taken];

      // --- Choice 1: Include node 'root' in the cut. ---
      // The cut stops here for this branch. We use 1 of our k budget.
      // The value is just the weight of root.
      int take_root = tree->w;

      // --- Choice 2: Do NOT include 'root'. Continue the cut in the children. ---
      // We have a budget of 'k' to distribute among the children.
      int skip_root = -inf; // Start with a very small number

      for(int taken_left = 0; taken_left <= taken; ++taken_left) {
        int taken_right = taken - taken_left;
        int left = do_optimal_cut(tree->left, taken_left);
        int right = do_optimal_cut(tree->right, taken_right);
        skip_root = std::max(skip_root, left + right);
      }

      (tree->dp)[taken] = std::max(take_root, skip_root);
      return std::max(take_root, skip_root);
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

        while(while_read(height) && height != -1) {
          while_read(k);
          int nodes = (1 << (height + 1)) - 1; 
          vi weights(nodes);
          for(int i = 0; i < nodes; ++i) {
            while_read(weights[i]);
          }

          int pos = 0;
          Tree* tree = restore_from_preorder(0, pos, weights);
          std::cout << do_optimal_cut(tree, k) << std::endl;
        }
    }
}