/*
───────────────────────────────────────────────────────────────
🧳 UVa 122 Trees on the level, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "tools/tree.cpp"
#include <bits/stdc++.h>


namespace tree = algorithms::onlinejudge::graph::tools::tree;


enum PathPiece { L, R };

using v_pp = std::vector<PathPiece>;
using path_map = std::multimap<int, v_pp>; 


void parse_input(
  const std::string& s, 
  bool& root_found, 
  bool& is_invalid,
  int& root,
  path_map& result_map) {
  size_t pos = 0;
  while((pos = s.find('(', pos)) != std::string::npos) {
   // Find the matching closing parenthesis
   size_t end_pos = s.find(')', pos);
   // Extract the content inside the parentheses, e.g., "382,RLLLRL" or ""
   std::string content = s.substr(pos + 1, end_pos - (pos + 1));
   // Move the search position past the closing parenthesis for the next iteration
   pos = end_pos + 1;
   if(content.empty()) break;

   // Find the comma that separates the number and the path
   size_t comma_pos = content.find(',');
   int value = std::stoi(content.substr(0, comma_pos));
   std::string path_str = content.substr(comma_pos + 1);
   // if root e.g. 1,
   if(path_str.empty()) {
     if(!root_found) {
       result_map.insert({value, {}});
       root_found = true;
       root = value;
     } else { is_invalid = true; break; }
   } else {
     if(value == root) 
     { is_invalid = true; break; }
     // Convert the path string into a vector of enums
     v_pp path_vector;
     for(char c : path_str) {
       if(c == 'L') {
         path_vector.push_back(L);
        } else if(c == 'R') {
         path_vector.push_back(R);
        }
     }
     result_map.insert({value, path_vector}); 
    }
  }
}

std::string do_levelorder(tree::Tree<>* tree) { 

    std::string levelorder;
    bool is_node_empty = false;
    std::queue<tree::Tree<>*> queue;
    queue.push(tree);
    while(!queue.empty()) {
      tree::Tree<>* root = queue.front(); queue.pop();
      if(root->left) queue.push(root->left);
      if(root->right) queue.push(root->right);
      int val = root->val;
      if(val != std::numeric_limits<int>::max())
        levelorder += std::to_string(val) + " ";
      else { is_node_empty = true; break; }
    }

    if(!is_node_empty) levelorder.pop_back();
    return !is_node_empty ? levelorder : "not complete";
}

namespace algorithms::onlinejudge::graph::tree_recovery_3
{
    /** https://onlinejudge.org/external/1/122.pdf */
    bool add_node(tree::Tree<>* root, int val, size_t i, const v_pp& path) {
      if(i == path.size()) {
        if(root->val == tree::def<>) {
          root->val = val;
          return true;
        } else return false;
      }

      if(path[i] == L) {
        if(!(root->left))
          root->left = new tree::Tree<>();
        return add_node(root->left, val, i + 1, path);  
      }

      if(path[i] == R) {
        if(!(root->right))
          root->right = new tree::Tree<>();
        return add_node(root->right, val, i + 1, path);
      }

      return false;
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
        path_map nodes;
        bool is_invalid = false;
        bool root_found = false;
        int root = -1;
        while(while_read(s)) {
          if(s == "()") {
            if(!is_invalid && root_found) {
              bool can_build = true;
              tree::Tree<>* tree = new tree::Tree<>();
              for(auto& n : nodes) {
                bool res = add_node(tree, n.first, 0, n.second);
                if(!res) { can_build = false; break; }
              }
            
              if(can_build) {
                std::cout << do_levelorder(tree) << std::endl;
              } else printf("not complete\n");
            } else printf("not complete\n");
           
            nodes.clear();
            is_invalid = false;
            root_found = false;
            root = -1;
          } else {
            parse_input(s, root_found, is_invalid, root, nodes);
          }
        }
    }
}