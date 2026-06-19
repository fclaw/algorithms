/*
───────────────────────────────────────────────────────────────
🧳 UVa 164 String Computer, https://onlinejudge.org/external/1/164.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



enum Action { INSERT, DELETE, CHANGE };

char actionToChar(Action a) {
  switch (a) {
    case INSERT: 
      return 'I'; // Or '+' if the problem asks for symbols
    case DELETE: 
      return 'D'; // Or '-' if the problem asks for symbols
    case CHANGE: 
      return 'C'; // Or 'M' (Mismatch) or 'R' (Replace) depending on the problem
  }
  return '\0';
}


struct State
{
    int steps;
    std::vector<std::tuple<int, char, Action>> instructions;
    bool operator < (const State& other) const {
      return steps < other.steps;
    }
};



using v_state = std::vector<State>;
using vv_state = std::vector<v_state>;


State get_instruction_sequence(const std::string& from, const std::string& to, int i, int j, vv_state& cache) {

  if (i == (int)from.size() && 
      j == (int)to.size()) {
    return {0, {}};
  }

  // first string ends 
  // .... _ _ _
  // .... A B C
  // insert operation
  if (i == (int)from.size() && 
      j < (int)to.size()) { 
    std::vector<std::tuple<int, char, Action>> ins;
    // Iterate BACKWARD so rbegin() processes them FORWARD
    for (int k = (int)to.size() - 1; k >= j; k--) {
      ins.push_back(std::make_tuple(i, to[k], INSERT));
    }
    return {(int)to.size() - j, ins};
  }

  // delete operation
  // .... A B C
  // .... _ _ _
  if (i < (int)from.size() && 
      j == (int)to.size()) {
    std::vector<std::tuple<int, char, Action>> ins;
    // Iterate BACKWARD so rbegin() processes them FORWARD
    for (int k = (int)from.size() - 1; k >= i; k--) {
      ins.push_back(std::make_tuple(k, from[k], DELETE)); 
    }
    return {(int)from.size() - i, ins};
  }

  if (cache[i][j].steps != -1) {
    return cache[i][j];
  }

  State state = {INT_MAX, {}};
     
  if(from[i] == to[j]) {
    state = get_instruction_sequence(from, to, i + 1, j + 1, cache);
  }

  State prev = get_instruction_sequence(from, to, i, j + 1, cache);
  prev.instructions.push_back(std::make_tuple(i, to[j], INSERT));
  prev.steps++;
  state = std::min(state, prev);

  prev = get_instruction_sequence(from, to, i + 1, j, cache);
  prev.instructions.push_back(std::make_tuple(i, from[i], DELETE));
  prev.steps++;
  state = std::min(state, prev);

  prev = get_instruction_sequence(from, to, i + 1, j + 1, cache);
  prev.instructions.push_back(std::make_tuple(i, to[j], CHANGE));
  prev.steps++;
  state = std::min(state, prev);

  return cache[i][j] = state;
}


namespace algorithms::onlinejudge::strings::string_computer
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

        std::string from, to;
        while(std::cin >> from && from != "#") {
          std::cin >> to;
          vv_state cache(from.size() + 1, v_state(to.size() + 1, State{-1, {}})); 
          State state = get_instruction_sequence(from, to, 0, 0, cache);
          std::string seq;
          int adj = 0; // Tracks the changing length of the string
          for(auto it = state.instructions.rbegin(); it != state.instructions.rend(); ++it) {
             auto val = *it;
             int original_i = std::get<0>(val);
             char c = std::get<1>(val);
             Action a = std::get<2>(val);

             // Calculate the TRUE dynamic index
             int true_index = original_i + 1 + adj;


             // Update the shift for future operations
             if (a == INSERT) adj++;
             if (a == DELETE) adj--;
             // CHANGE does not affect the shift

             std::string s_pos = std::to_string(true_index);
             if (true_index < 10) {
               s_pos = "0" + s_pos;
             }
             std::string instruction = std::string(1, actionToChar(a)) + std::string(1, c)  + s_pos;
             seq += instruction;
          }
          seq += "E";
          std::cout << seq << std::endl;
        }
    }
}