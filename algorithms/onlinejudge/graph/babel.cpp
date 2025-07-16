/*
 * ───────────────────────────────────────────────────────────────
 * 🧳 UVa 11492 Babel, rt 0.140: s
 * ───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"

#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>
#include <bitset>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <string>



using vi = std::vector<int>;
using vvi = std::vector<vi>;

constexpr int MAX_LETTERS = 27;
constexpr int inf = (int)1e5;
const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

// Represents a state to be explored. It holds the minimum information
// needed to define a "location" in our search and its total cost.
struct State 
{
    int total_length;   // The total cost (path length) to reach this state.
                        // This MUST be the primary key for the priority queue.
    int lang_id;        // Which language are we "in"? (using an int ID is faster)
    char initial_char;  // What was the first letter of the word that got us here?
    // The comparator for the min-priority queue.
    bool operator < (const State& other) const { return total_length > other.total_length; }
};


// Represents a "word bridge" between two languages. This struct
// pre-calculates all the properties of a potential move.
struct EdgeInfo 
{
    int target_language_id; // Where does this bridge lead? (int ID)
    int word_length;        // What is the cost to cross this bridge?
    char initial_char;      // What is the first letter of this bridge's word?
};


namespace algorithms::onlinejudge::graph::babel
{
    /** https://onlinejudge.org/external/114/11492.pdf */
    int words;
    int to_int(char c) { return (int)c - 97; }
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

        while(while_read(words) && words) {
          int next_lang_id = 0;
          std::unordered_map<std::string, int> lang_to_id;
          std::unordered_map<int, std::vector<EdgeInfo>> edgeinfo;
          std::vector<EdgeInfo> setup_words;
          std::string from, to;
          while_read(from, to);

          for(int w = 0; w < words; ++w) {
            std::string lang_1, lang_2, word;
            while_read(lang_1, lang_2, word);
  
            char init_char = word.front();
            int word_length = word.size();
            if(lang_to_id.find(lang_1) == lang_to_id.end())
              lang_to_id[lang_1] = next_lang_id++;
            int lang_1_id = lang_to_id[lang_1];

            if(lang_to_id.find(lang_2) == lang_to_id.end())
              lang_to_id[lang_2] = next_lang_id++;
            int lang_2_id = lang_to_id[lang_2];

            edgeinfo[lang_1_id].push_back({lang_2_id, word_length, init_char});
            edgeinfo[lang_2_id].push_back({lang_1_id, word_length, init_char});

            if(lang_1 == from) setup_words.push_back({lang_2_id, word_length, init_char});
            if(lang_2 == from) setup_words.push_back({lang_1_id, word_length, init_char});

          }

          if(from == to ||
             lang_to_id.find(from) == lang_to_id.end() || 
             lang_to_id.find(to) == lang_to_id.end())
          { printf("impossivel\n"); continue; }

          int V = next_lang_id;
          vvi states(V, vi(MAX_LETTERS, inf));
          std::priority_queue<State> queue;
           
          // multi-source Dijkstra
          for(auto& info : setup_words) {
            int lang_id = info.target_language_id;
            char init_char = info.initial_char;
            int w = info.word_length;
            if(w < states[lang_id][to_int(init_char)]) {
              states[lang_id][to_int(init_char)] = w;
              queue.push({w, lang_id, init_char});
            }
          }

          while(!queue.empty()) {
            State state = queue.top(); queue.pop();
            int lang_id = state.lang_id;
            char init_char = state.initial_char;

            // >>> ESSENTIAL DIJKSTRA'S CHECK <<<
            if (state.total_length > 
                states[lang_id][to_int(init_char)]) {
                continue;
            }

            for(const EdgeInfo& info : edgeinfo[lang_id]) {
              if(info.initial_char != init_char) {
                int total_length = state.total_length + info.word_length;
                int target_lang_id = info.target_language_id;
                int target_init_char = to_int(info.initial_char);
                // Second constraint: cannot return to the start language
                if(target_lang_id == lang_to_id[from]) continue;
                if(total_length < states[target_lang_id][target_init_char]) {
                  states[target_lang_id][target_init_char] = total_length;
                  queue.push({total_length, target_lang_id, info.initial_char});
                }
              }
            }
          }

          int min_length = inf;
          int lang_id_to = lang_to_id[to];
          for(char c : alphabet) {
            min_length = std::min(min_length, states[lang_id_to][to_int(c)]);
          }
          std::cout << (min_length == inf ? "impossivel" : std::to_string(min_length)) << std::endl;
        }  
    }
}