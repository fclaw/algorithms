/*
───────────────────────────────────────────────────────────────
🧳 UVa 1251 Repeated Substitution with Sed, https://onlinejudge.org/external/12/1251.pdf, rt: s
───────────────────────────────────────────────────────────────
*/


#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>

 

using ss = std::pair<std::string, std::string>;
using vss = std::vector<ss>;



std::string apply_sed(const std::string& origin, const std::string& replace_word, const std::string& replace_by) {
  std::string modified = origin;
  // Find the first occurrence of the substring
  size_t pos = modified.find(replace_word);

  // Iterate through the string and replace all occurrences
  while (pos != std::string::npos) {
    // Replace the substring with the specified string
    modified.replace(pos, replace_word.length(), replace_by);

    // Find the next occurrence of the substring
    pos = modified.find(replace_word, pos + replace_by.length());
  }

  return modified;
}

struct State
{
    /**
     * 1. str (Current Intermediate String)
     * ------------------------------------
     * The string generated after applying a sequence of Sed substitutions.
     * Starts at initial string gamma (γ), and goal is to reach delta (δ).
     */
    std::string str;

    /**
     * 2. substitutions (Cost / Distance g(n))
     * ---------------------------------------
     * The number of Sed replacement commands executed so far.
     * This is an unweighted BFS where each Sed command costs +1 step.
     */
    int substitutions;
};



int min_substitution_required(const std::string& source, const std::string& target, const vss& substitutes) {

    std::queue<State> queue;
    std::unordered_set<std::string> visited;
    // init
    queue.push({source, 0});
    visited.insert(source);

    int min_substitution = -1;

    while(!queue.empty()) {
       State state = queue.front(); queue.pop();
       auto curr_str = state.str;
       int substitution_so_far = state.substitutions;

       if(curr_str == target) {
          min_substitution = substitution_so_far;
          break;
       }

       // pruning
       if(curr_str.length() > 
          target.length()) {
         continue;
       }

       for(auto t : substitutes) {
         auto replace_word = t.first;
         auto replace_by = t.second;
         auto new_str = apply_sed(curr_str, replace_word, replace_by);
         if(!visited.count(new_str)) {
           visited.insert(new_str);
           queue.push({new_str, 1 + substitution_so_far});
         }
       }
    }
     
    return min_substitution;
}

namespace algorithms::onlinejudge::advanced_topics::sed
{

    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value()) {
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }
        }

        int N;
        while(std::cin >> N && N) {
          vss substitutes(N);
          std::string replace_word, replace_by;
          for(int i = 0; i < N; ++i) {
            std::cin >> replace_word >> replace_by;
            substitutes[i] = {replace_word, replace_by};
          }
          std::string source, target;
          std::cin >> source >> target;
          printf("%d\n", min_substitution_required(source, target, substitutes));
        }
    }
}
