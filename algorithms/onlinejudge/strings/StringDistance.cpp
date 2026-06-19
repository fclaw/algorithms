/*
───────────────────────────────────────────────────────────────
🧳 UVa 526 String Distance and Transform Process, https://onlinejudge.org/external/5/526.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



enum Action { INSERT, DELETE, REPLACE };

std::string actionToString(Action a) {
  switch (a) {
    case INSERT: 
      return "Insert"; // Or '+' if the problem asks for symbols
    case DELETE: 
      return "Delete"; // Or '-' if the problem asks for symbols
    case REPLACE: 
      return "Replace"; // Or 'M' (Mismatch) or 'R' (Replace) depending on the problem
  }
  return "";
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

  State prev_insert = get_instruction_sequence(from, to, i, j + 1, cache);
  prev_insert.instructions.push_back(std::make_tuple(i, to[j], INSERT));
  prev_insert.steps++;

  State prev_delete = get_instruction_sequence(from, to, i + 1, j, cache);
  prev_delete.instructions.push_back(std::make_tuple(i, from[i], DELETE));
  prev_delete.steps++;

  State prev_replace = get_instruction_sequence(from, to, i + 1, j + 1, cache);
  prev_replace.instructions.push_back(std::make_tuple(i, to[j], REPLACE));
  prev_replace.steps++;

  return cache[i][j] = std::min(state, std::min(prev_replace, std::min(prev_insert, prev_delete)));
}


namespace algorithms::onlinejudge::strings::string_distance
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
        bool is_first = true;
        while(std::getline(std::cin, from)) {
          std::getline(std::cin, to);
          vv_state cache(from.size() + 1, v_state(to.size() + 1, State{-1, {}})); 
          State state = get_instruction_sequence(from, to, 0, 0, cache);
          std::string seq = std::to_string(state.steps) + "\n";
          int adj = 0; // Tracks the changing length of the string
          int bullet_point = 1;
          auto it = state.instructions.rbegin();
          for(; it != state.instructions.rend(); ++it) {
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
             std::string symb =  "," + std::string(1, c);
             if(a == DELETE) symb = "";
             std::string instruction = std::to_string(bullet_point++) + " " + actionToString(a) + " " + s_pos + symb;
             seq += instruction + "\n";
          }
          seq.pop_back();
          if(!is_first) std::cout << std::endl;
          else is_first = false; 
          std::cout << seq << std::endl;
        }
    }
}