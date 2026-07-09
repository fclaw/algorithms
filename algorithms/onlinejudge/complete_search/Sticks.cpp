/*
───────────────────────────────────────────────────────────────
🧳 UVa 307 Sticks, https://onlinejudge.org/external/3/307.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




using vi = std::vector<int>;


const int MAX_HEIGHT = 50 * 60;


bool is_feasible(const vi& splinters, std::unordered_map<int, int>& pool, int curr_height, int target_height, int rem_splinters) {

  if(rem_splinters == 0) {
    return curr_height == 0;
  }

  for(int splinter : splinters) {
    if(pool.at(splinter) > 0) {
      int new_curr_height = curr_height + splinter;
      if(new_curr_height <= target_height) {

        if(new_curr_height == target_height) {
          new_curr_height = 0;
        }

        pool[splinter]--;

        if(is_feasible(splinters, pool, new_curr_height, target_height, rem_splinters - 1)) {
          pool[splinter]++;
          return true; // We found a path!
        }

        pool[splinter]++;

        // ====================================================================
        // --- THE GOLDEN PRUNING RULES ---
        // ====================================================================
        // PRUNING RULE 1: If the first piece we tried on a blank stick failed,
        // then this entire branching path is a dead end.
        if (curr_height == 0) {
          return false; 
        }

        // PRUNING RULE 2: If a piece that perfectly completed the current stick 
        // failed, trying smaller pieces to complete it is guaranteed to fail.
        if (new_curr_height == target_height) {
          return false;
        }
        // ====================================================================
      }
    }
  }
  return false;
}

namespace algorithms::onlinejudge::complete_search::sticks
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
          vi splinters(N);
          int max_height = 0;
          std::unordered_map<int, int> pool;
          for(int i = 0; i < N; ++i) {
            std::cin >> splinters[i];
            max_height += splinters[i];
            pool[splinters[i]]++;
          }

          // Bitset of size MAX_HEIGHT (max possible sum)
          // reached[h] will be 1 if height h is possible
          std::bitset<MAX_HEIGHT> reached;
          reached[0] = 1; // Base case: sum of 0 is possible

          for(int spl : splinters) {
            // Shift all current possible sums left by 'x' 
            // and merge them with a single bitwise OR operation!
            reached |= (reached << spl);
          }

          std::sort(splinters.begin(), splinters.end(), std::greater<int>());
          int ans = -1;
          int bound = std::min(max_height, MAX_HEIGHT);
          int start = splinters.front(); 
          for(int candidate = start; candidate <= bound; ++candidate) {
            if(reached[candidate]) {

              // --- THE GOLDEN PRUNING RULE ---
              // If the candidate doesn't evenly divide the total sum, 
              // it is mathematically impossible. Skip it instantly!
              if (max_height % candidate != 0) {
                continue;
              }

              std::unordered_map<int, int> loc_pool = pool;
              int rem_splinters = (int)splinters.size();
              if(is_feasible(splinters, loc_pool, 0, candidate, rem_splinters)) {
                ans = candidate;
                goto exit;
              }
            }
          }
          exit: std::cout << ans << std::endl;
        }
    }
}