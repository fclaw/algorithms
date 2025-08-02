
 /*
 ─────────────────────────────────────────────────────────────── 
 🧳 UVa 12644 Vocabulary, classic MCBM problem wrapped inside a creative problem statement, rt: s
 ───────────────────────────────────────────────────────────────
 */

#include "../debug.h"
#include "../../aux.h"
#include "tools/mcbm.cpp"
#include <bits/stdc++.h>


namespace mcmb = algorithms::onlinejudge::graph::tools::mcmb;


struct Word
{
    int id;
    // more optimal for performance is to use array for the letters are fixed at 26
    std::unordered_map<char, int> frequency;
};

using v_word = std::vector<Word>;

bool can_bridged(const Word& word, const Word& challenge) {
  const auto& b_freq = challenge.frequency;
  const auto& a_freq = word.frequency;
  for(auto& f : b_freq) {
    int b_cnt = f.second;
    auto it = a_freq.find(f.first);
    if(it == a_freq.end()) return false;
    int a_cnt = it->second;
    if(a_cnt < b_cnt) return false;
  }
  return true;
}

namespace algorithms::onlinejudge::graph::vocabulary
{
    /** https://onlinejudge.org/external/126/12644.pdf */
    // left - the number of words in Jack’s vocabulary
    // right - numberof challenges presented by Jill
    int left, right;
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

        while(while_read(left, right)) {
          std::string w;
          v_word left_words(left);
          v_word right_words(right);
          for(int idx = 0; idx < left; idx++) {
            while_read(w);
            Word word;
            word.id = idx;
            for(int l = 0; l < (int)w.size(); ++l) {
              ++word.frequency[w[l]];
            }
            left_words[idx] = word;
          }
          for(int idx = 0; idx < right; idx++) {
            while_read(w);
            Word word;
            word.id = idx;
            for(int l = 0; l < (int)w.size(); ++l) {
              ++word.frequency[w[l]];
            }
            right_words[idx] = word;
          }

          int L_SIZE = left;
          int R_SIZE = right;
          
          mcmb::vvi graph(L_SIZE);
          for(int i = 0; i < L_SIZE; ++i) {
            for(int j = 0; j < R_SIZE; ++j) {
              auto left = left_words[i];
              auto right = right_words[j];
              // whether an edge can be built
              if(can_bridged(left, right)) {
                graph[i].push_back(j);
              }
            }
          }

          int matched_words = 0;
          mcmb::kuhn kuhn_s(R_SIZE);
          for(int word_id = 0; word_id < L_SIZE; ++word_id) {
            kuhn_s.visited.assign(L_SIZE, false);
            bool is_matched = mcmb::try_kuhn(word_id, graph, kuhn_s);
            if(is_matched) matched_words++;
          }
          std::cout << matched_words << std::endl;
        }  
    }
}