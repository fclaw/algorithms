/*
───────────────────────────────────────────────────────────────
🧳 UVa 531 Compromise, https://onlinejudge.org/external/5/531.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vs = std::vector<std::string>;


struct State 
{
    int length;
    vs lcs;
    bool operator < (const State& other) const {
      return length < other.length;
    }
};

using v_state = std::vector<State>;
using vv_state = std::vector<v_state>;


State find_lcs(const vs& first, const vs& second, int i, int j, vv_state& cache) {

  if(i == (int)first.size() || 
     j == (int)second.size()) {
    return {0, {}};
  }

  if(~cache[i][j].length) {
    return cache[i][j];
  }

  State state = {0, {}};
  
  if(first[i] == second[j]) {
    State prev = find_lcs(first, second, i + 1, j + 1, cache);
    prev.lcs.push_back(first[i]);
    prev.length += 1;
    state = std::max(state, prev);
  }

  State i_state = find_lcs(first, second, i + 1, j, cache);
  State j_state = find_lcs(first, second, i, j + 1, cache);

  return cache[i][j] = std::max(state, std::max(i_state, j_state));
}


namespace algorithms::onlinejudge::strings::compromise
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

        std::string word;
        vs first, second;
        while(!std::cin.eof()) {
          first.clear();
          second.clear();
          while(std::cin >> word && word != "#") {
            first.push_back(word);
          }
          while(std::cin >> word && word != "#") {
            second.push_back(word);
          }
          vv_state cache(first.size(), v_state(second.size(), {-1, {}}));
          State state = find_lcs(first, second, 0, 0, cache);
          if(state.length > 0) {
            vs lcs = state.lcs;
            for(int i = (int)lcs.size() - 1; i >= 0; --i) {
              std::cout << lcs[i];
              if(i != 0) {
                std::cout << " ";
              }
            }
            std::cout << std::endl;
          }
        }
    }
}