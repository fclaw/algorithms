/*
───────────────────────────────────────────────────────────────
🧳 UVa 536 Tree Recovery, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "tools/tree.cpp"
#include <bits/stdc++.h>


namespace tree = algorithms::onlinejudge::graph::tools::tree;



// --- A helper to read the next token, skipping whitespace ---
// This is the key to handling the multi-line, spaced-out input.
bool get_next_token(std::istream& in, std::string& token) {
    char c;
    token = {};

    // Skip all leading whitespace
    while (in.get(c) && isspace(c));
    
    // If we hit the end of the file, return false.
    if (in.eof()) return false;

    // Check what we found.
    if (c == '(' || c == ')') {
        token += c; // It's a parenthesis.
    } else if (c == '-' || isdigit(c)) {
        // It's the start of a number.
        token += c;
        // Keep reading digits.
        while (in.peek() != ')' && in.peek() != '(' && !isspace(in.peek())) {
            in.get(c);
            token += c;
        }
    } else {
        // Should not happen with valid input.
        return false;
    }
    return true;
}


// --- The Recursive Parser ---
tree::Tree<>* build_tree() {
    std::string token;
    
    // 1. Every tree expression must start with '('.
    get_next_token(std::cin, token);
    if (token != "(") {
        // This should not happen with valid input, but it's a good error check.
        // It's possible we just read a number (the target sum), so we need to put it back.
        // A more robust solution would have a global tokenizer.
        // For now, let's assume we are perfectly positioned to read a '('.
    }

    // 2. See what's inside the parentheses.
    get_next_token(std::cin, token);
    
    // Case A: An empty tree "()"
    if (token == ")") {
        return nullptr;
    }

    // Case B: A non-empty tree "(value left right)"
    // The token must be a number.
    int value = std::stoi(token);
    tree::Tree<>* node = new tree::Tree<>(value);

    // Recursively build the left and right children.
    node->left = build_tree();
    node->right = build_tree();
    
    // Consume the final closing parenthesis.
    get_next_token(std::cin, token); // This should read the ')'
    
    return node;
}


namespace algorithms::onlinejudge::graph::tree_summing
{
    /** https://onlinejudge.org/external/1/112.pdf */
    int target;
    bool is_finished;
    bool backtrack(tree::Tree<>* tree, int acc) {
      
      if(tree == nullptr) 
        return false;

      if(is_finished) return true;

      if(!(tree->left) && 
         !(tree->right)) {
        if(acc + tree->val == target) {
          is_finished = true;
          return true;  
        }
        return false;
      }

      bool can_reach_target = false;
      if(tree->left) {
        can_reach_target |= backtrack(tree->left, acc + tree->val);
      }

      if(tree->right) {
        can_reach_target |= backtrack(tree->right, acc + tree->val);
      }

      return can_reach_target;
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

        while(while_read(target)) {
          is_finished = false;  
          tree::Tree<>* tree = build_tree();
          std::cout << (backtrack(tree, 0) ? "yes" : "no") << std::endl;
        }
    }
}