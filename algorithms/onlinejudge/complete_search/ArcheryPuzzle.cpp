/*
───────────────────────────────────────────────────────────────
🧳 UVa 12840 The Archery Puzzle, https://onlinejudge.org/external/128/12840.pdf, rt: s
───────────────────────────────────────────────────────────────
 * ============================================================================
 * ALGORITHM: THE ARCHERY PUZZLE (Branch & Bound Backtracking)
 * ============================================================================
 * THE GOAL:
 * Find the MINIMUM number of arrows (elements) that sum exactly to S.
 * If there is a tie, choose the lexicographically largest sequence.
 * 
 * THE BRANCH & BOUND PRUNING (The TLE Savior):
 * --------------------------------------------
 *  if (!best_scores.empty() && curr_scores.size() > best_scores.size()) {
 *      return;
 *  }
 * 
 * Why this is mandatory:
 * 1. Backtracking is inherently exponential (O(N^S)).
 * 2. Because we want to MINIMIZE the number of arrows, our current best solution 
 *    (`best_scores`) acts as an upper "bound" on the depth of the search tree.
 * 3. If we have already found a valid solution of size B, and our current 
 *    tentative path (`curr_scores`) has already reached a size > B, we can 
 *    instantly abort (prune) this entire branch. 
 *    
 *    Even if we find a valid sum deeper down, it will require at least B + 1 
 *    arrows, which is strictly worse than our current best.
 * 
 * THE LEXICOGRAPHICAL PRO-TIP (Sorting Descending):
 * -------------------------------------------------
 * If we sort the `scores` array in DESCENDING order (largest arrows first):
 * 1. The very first valid solution of size L we find is mathematically 
 *    guaranteed to be the lexicographically largest one.
 * 2. This allows us to tighten the pruning condition from '>' to '>=':
 *         if (!best_scores.empty() && curr_scores.size() >= best_scores.size())
 * 
 *    By changing this to '>=', the moment we reach the same depth as our 
 *    current best, we abort. This prevents searching for alternative 
 *    same-sized paths, cutting the search space in half again!
 * ============================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vi = std::vector<int>;


vi best_scores;


void backtrack(const vi& scores, int pos, int total, vi& curr_scores, int& curr_total) {
    
  if(!best_scores.empty() && 
      curr_scores.size() >
      best_scores.size()) {
    return;
  }

  if(curr_total == total) {
    if(best_scores.empty()) {
      best_scores = curr_scores;
    } else if(best_scores.size() > curr_scores.size()) {
      best_scores = curr_scores;
    } else {
      best_scores = std::max(best_scores, curr_scores);
    }
    return;
  }

  for(int i = pos; i < (int)scores.size(); ++i) {
    if(curr_total + scores[i] > total) continue;
    curr_scores.push_back(scores[i]);
    curr_total += scores[i];
    backtrack(scores, pos, total, curr_scores, curr_total);
    curr_scores.pop_back();
    curr_total -= scores[i];
  }
}


namespace algorithms::onlinejudge::complete_search::archery_puzzle
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

        int t_cases, t_case = 1;
        std::cin >> t_cases;
        while(t_cases--) {
          best_scores.clear();
          int N, total_score;
          std::cin >> N >> total_score;
          vi scores(N);
          for(int i = 0; i < N; ++i) {
            std::cin >> scores[i];
          }

          std::sort(scores.begin(), scores.end(), std::greater<int>());
          vi curr_scores;
          int curr_total = 0;
          backtrack(scores, 0, total_score, curr_scores, curr_total);

          if(best_scores.empty()) {
            printf("Case %d: impossible\n", t_case++);
          } else {
            std::string str_scores;
            int S = (int)best_scores.size();
            for(int i = 0; i < S; ++i) {
              str_scores += std::to_string(best_scores[i]);
              if(i < S - 1) {
                str_scores += " ";
              }
            }

            printf("Case %d: [%d] %s\n", t_case++, S, str_scores.c_str());
          }
        }
    }
}