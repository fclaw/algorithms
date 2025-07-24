 /*
 ─────────────────────────────────────────────────────────────── 
 🧳 UVa 839 Not so Mobile, rt: s
 ───────────────────────────────────────────────────────────────
 */

#include "../debug.h"
#include "../../aux.h"
#include "tools/tree.cpp"
#include <bits/stdc++.h>



namespace tree = algorithms::onlinejudge::graph::tools::tree;

// fulcrum: w = 0, w /= 0, r /= 0
// weight: w /= 0, l = r = 0;
struct Node
{
    int w;
    int l;
    int r;
};

struct Input
{
    int w_l;
    int d_l;
    int w_r;
    int d_r;
    Input() {}
};

// Read the five integer members directly from the stream.
// The >> operator will automatically handle whitespace separation.
std::istream& operator >> (std::istream& is, Input& input) {
  return (is >> input.w_l >> input.d_l >> input.w_r >> input.d_r);
}

using v_input = std::vector<Input>;

int is_equilibrium(tree::Tree<Node>* tree) {

  if(!(tree->left) &&
     !(tree->right))
   return (tree->val).w;

  tree::Tree<Node>* left_tree = tree->left;
  tree::Tree<Node>* right_tree = tree->right;

  // fulcrum is imbalanced
  if(!left_tree || !right_tree)
    return tree::def<>;

  int total_left_w = is_equilibrium(left_tree);
  int total_right_w = is_equilibrium(right_tree);

  if(total_left_w != tree::def<> &&
     total_right_w != tree::def<>) {
    int left_w = total_left_w * (tree->val).l;
    int right_w = total_right_w * (tree->val).r;
    if(left_w == right_w) {
      // we are solely concerned with 
      // total weight of left, right
      // and the propagation of it upward
      return total_left_w + total_right_w;
    }
  }
  return tree::def<>;
}


// We still pass the index 'i' by reference to consume the flat vector.
tree::Tree<Node>* build_tree(int& i, const v_input& nodes) {
  if(i >= (int)nodes.size()) return nullptr;

  // Get the definition for the current node from the flat list.
  int Wl = nodes[i].w_l;
  int Dl = nodes[i].d_l;
  int Wr = nodes[i].w_r;
  int Dr = nodes[i].d_r;
  i++; // Consume this line

  // Create the node representing the fulcrum/bar.
  // Its value doesn't matter much, it just holds the children.
  auto root = new tree::Tree<Node>(); 
  root->val.w = tree::def<>;
  // --- Check Left Child ---
  if (Wl == 0) {
    // Left child is a sub-mobile, so we recurse.
    // The distance Dl belongs to this child.
    root->left = build_tree(i, nodes);
    if(root->left) { // Check if recursion was successful
      root->val.l = Dl; // Store distance in the child
    }
  } else {
    // Left child is a direct weight. Create a leaf node.
    root->left = new tree::Tree<Node>({Wl, 0, 0});
  }

  // --- Check Right Child ---
  if(Wr == 0) {
    // Right child is a sub-mobile.
    root->right = build_tree(i, nodes);
    if(root->right) {
      root->val.r = Dr; // Store distance
    }
  } else {
    // Right child is a direct weight.
    root->right = new tree::Tree<Node>({Wr, 0, 0});
  }
  return root;
}

namespace algorithms::onlinejudge::graph::mobile
{
    /** https://onlinejudge.org/external/8/839.pdf */
    int t_cases;
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
        
        while_read(t_cases);
        std::cin.ignore();
        std::cin.ignore();
        while(t_cases--) {
          int idx = 0;
          v_input nodes;
          Input input;
          std::string s;
          while(std::getline(std::cin, s) && !s.empty()) {
            std::stringstream ss(s);
            ss >> input;
            nodes.push_back(input);
          }
          tree::Tree<Node>* tree = build_tree(idx, nodes);
          int ans = is_equilibrium(tree);
          printf("%s\n", (ans != tree::def<> ? "YES" : "NO"));
          if(t_cases) std::cout << std::endl;
        }
    }
}