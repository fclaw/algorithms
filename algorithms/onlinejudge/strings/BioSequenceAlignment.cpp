/*
───────────────────────────────────────────────────────────────
🧳 UVa 1192 Searching Sequence Database in Molecular Biology, https://onlinejudge.org/external/11/1192.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



int MATCH = 5;
int MISMATCH = -4;
int GAP = -7;


struct State
{
    int score;
    bool operator < (const State& other) const {
      return score < other.score;
    }
};

std::ostream& operator << (std::ostream& out, const State& state) {
    return out << "{ score: " << state.score << " } ";
}


using v_state = std::vector<State>;
using vv_state = std::vector<v_state>;


State get_max_score(const std::string& from, const std::string& to, int i, int j, vv_state& cache) {

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
    return {GAP * ((int)to.size() - j)};
  }

  // delete operation
  // .... A B C
  // .... _ _ _
  if (i < (int)from.size() && 
      j == (int)to.size()) {
    return {GAP * ((int)from.size() - i)};
  }

  if (~cache[i][j].score) {
    return cache[i][j];
  }

  State match = {INT_MIN};

  if(from[i] == to[j]) {
    match = get_max_score(from, to, i + 1, j + 1, cache);
    match.score += MATCH;
  }

  State gap_from = get_max_score(from, to, i, j + 1, cache);
  gap_from.score += GAP;

  State gap_to = get_max_score(from, to, i + 1, j, cache);
  gap_to.score += GAP;

  State mismatch = get_max_score(from, to, i + 1, j + 1, cache);
  mismatch.score += MISMATCH;

  return cache[i][j] = std::max(match, std::max(gap_from, std::max(gap_to, mismatch)));
}


namespace algorithms::onlinejudge::strings::bio_sequence_alignment
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

        std::string pattern;
        std::vector<std::string> samples; 

        // --- READ BLOCK ---
        std::string label, seq;
        while (std::cin >> label) {
          // Check for the FASTA-like header marker
          if (label[0] == '>') {
            std::cin >> seq;
            if (label == ">query") {
              pattern = seq;
            } else {
              samples.push_back(seq);
            }
          }
        }
        
        int max_score = INT_MIN;
        std::vector<std::string> similar_seqs;
        for(auto sample : samples) {
          vv_state cache(pattern.size() + 1, v_state(sample.size() + 1, State{-1}));
          int score = get_max_score(pattern, sample, 0, 0, cache).score;
          if(score > max_score) {
            max_score = score;
            similar_seqs.clear();
            similar_seqs.push_back(sample);
          } else if (score == max_score) {
             similar_seqs.push_back(sample);
          }
        }

        // --- PE-PROOF OUTPUT BLOCK ---
        std::cout << "The query sequence is:\n" << pattern << "\n\n";
        std::cout << "The most similar sequences are:\n\n";

        for (size_t i = 0; i < similar_seqs.size(); ++i) {
          std::cout << similar_seqs[i] << "\n";
          std::cout << "The similarity score is: " << max_score;
            
          // Only print a double newline if there is another sequence coming!
          if (i + 1 < similar_seqs.size()) {
            std::cout << "\n\n";
          } else {
            std::cout << "\n"; // Clean EOF with a single newline
          }
        }
    }
}