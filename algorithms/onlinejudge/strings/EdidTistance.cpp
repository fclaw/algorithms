/*
───────────────────────────────────────────────────────────────
🧳 UVa 13146 Edid Tistance, https://onlinejudge.org/external/131/13146.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



struct State
{
    int steps;
    bool operator < (const State& other) const {
      return steps < other.steps;
    }
};


using v_state = std::vector<State>;
using vv_state = std::vector<v_state>;


State get_min_steps(const std::string& from, const std::string& to, int i, int j, vv_state& cache) {

  if (i == (int)from.size() && 
      j == (int)to.size()) {
    return {0};
  }

  // first string ends 
  // .... _ _ _
  // .... A B C
  // insert operation
  if (i == (int)from.size() && 
      j < (int)to.size()) {
    return {(int)to.size() - j};
  }

  // delete operation
  // .... A B C
  // .... _ _ _
  if (i < (int)from.size() && 
      j == (int)to.size()) {
    return {(int)from.size() - i};
  }

  if (cache[i][j].steps != -1) {
    return cache[i][j];
  }

  State eq_state = {INT_MAX};

  if(from[i] == to[j]) {
    eq_state = get_min_steps(from, to, i + 1, j + 1, cache);
  }

  State prev_insert = get_min_steps(from, to, i, j + 1, cache);
  prev_insert.steps++;

  State prev_delete = get_min_steps(from, to, i + 1, j, cache);
  prev_delete.steps++;

  State prev_replace = get_min_steps(from, to, i + 1, j + 1, cache);
  prev_replace.steps++;

  return cache[i][j] = std::min(eq_state, std::min(prev_replace, std::min(prev_insert, prev_delete)));
}


namespace algorithms::onlinejudge::strings::edid_tistance
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

        int t_cases;
        std::cin >> t_cases;
        std::cin.ignore();
        while(t_cases--) {
          std::string first, second;
          std::getline(std::cin, first);
          std::getline(std::cin, second);
          vv_state cache(first.size() + 1, v_state(second.size() + 1, State{-1}));
          std::cout << get_min_steps(first, second, 0, 0, cache).steps << std::endl;
        }
    }
}