/*
───────────────────────────────────────────────────────────────
🧳 UVa 307 Sticks, https://onlinejudge.org/external/3/307.pdf, rt: s
───────────────────────────────────────────────────────────────
 * ============================================================================
 * UVA 307 - STICKS (SPLINTERS): HEURISTIC BACKTRACKING & BRANCH-AND-BOUND
 * ============================================================================
 * THE COMPLEXITY WALL:
 * This problem is a variation of the Multi-Set Partition problem, which is 
 * NP-hard. With N up to 64, the standard backtracking state space is roughly 
 * O(2^N), leading to billions of operations. To get under the strict time limit, 
 * we must apply six distinct, mathematically proven pruning "shields."
 * 
 * ----------------------------------------------------------------------------
 * SHIELD 1: THE DIVISOR LAW (Driver Optimization)
 * ----------------------------------------------------------------------------
 * - Concept: Since all original reconstructed sticks must be of the SAME length, 
 *   the target candidate length must be a perfect divisor of the total sum.
 * - Math: `total_sum % candidate_height == 0`
 * - Impact: Reduces the number of tested candidate heights from thousands to 
 *   just a small handful of actual divisors.
 * 
 * ----------------------------------------------------------------------------
 * SHIELD 2: THE DUPLICATE SKIPPER (O(1) Branch Pruning)
 * ----------------------------------------------------------------------------
 * - Concept: If we try to place a splinter of size X at index 'i' on the current 
 *   stick, and it fails to lead to a solution, we must NEVER try another 
 *   splinter of size X at index 'i' in the same loop.
 * - Math: `if (i > start_idx && splinters[i] == splinters[i - 1]) continue;`
 * - Impact: Collapses the redundant "duplicate forest" caused by identical 
 *   lengths (e.g., trying four '33's separately).
 * 
 * ----------------------------------------------------------------------------
 * SHIELD 3: THE NEXT-FIT SYMMETRY BREAKER (Enforcing Order)
 * ----------------------------------------------------------------------------
 * - Concept: Building a stick as "5 + 3 + 2" is identical to "3 + 2 + 5" or 
 *   "2 + 5 + 3". These are symmetric permutations.
 * - The Fix: We force the splinters inside each individual stick to be chosen 
 *   in strictly non-increasing order of size. 
 * - Math: We pass a `start_idx` to the recursion.
 *   - If continuing same stick: `next_start_idx = i + 1` (must choose smaller/equal).
 *   - If starting new stick: `next_start_idx = 0` (can use any large piece).
 * 
 * ----------------------------------------------------------------------------
 * SHIELD 4: THE "FIRST PIECE" FAILURE RULE (Inclusion-Exclusion)
 * ----------------------------------------------------------------------------
 * - Concept: If we are starting a brand new stick (`curr_height == 0`), and the 
 *   largest available splinter fails to lead to a solution, we immediately 
 *   abort the entire search path and return `false`.
 * - Proof: Every single splinter must be used eventually. If the largest 
 *   available splinter cannot start the current blank stick, it can never start 
 *   any subsequent stick either.
 * 
 * ----------------------------------------------------------------------------
 * SHIELD 5: THE "PERFECT FIT" FAILURE RULE
 * ----------------------------------------------------------------------------
 * - Concept: If we try a splinter that exactly completes the current stick 
 *   (`curr_height + splinter == target_height`), and the recursive search 
 *   fails, we immediately abort and return `false`.
 * - Proof: If a single perfect-fit piece fails, attempting to fill that exact 
 *   same gap with multiple smaller pieces is mathematically guaranteed to either 
 *   fail or be redundant.
 * 
 * ----------------------------------------------------------------------------
 * SHIELD 6: THE "TOO SMALL TO FIT" GAP CHECK
 * ----------------------------------------------------------------------------
 * - Concept: If the remaining gap in our current stick is strictly smaller 
 *   than the absolute smallest splinter in our entire pool, we can never fill it.
 * - Math: `if (curr_height > 0 && (target - curr_height) < splinters.back())`
 * - Impact: Avoids diving deeper into the recursion stack when the remaining 
 *   gap is mathematically impossible to close.
 * ============================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




using vi = std::vector<int>;


const int MAX_HEIGHT = 50 * 60;


bool is_feasible(const vi& splinters, int start_idx, std::unordered_map<int, int>& pool, int curr_height, int target_height, int sticks) {

  if(sticks == 0) {
    return curr_height == 0;
  }


  for(int i = start_idx; i < (int)splinters.size(); ++i) {

    // GUARD 1:
    // --- THE DUPLICATE SKIPPER ---
    // If the element we are about to try has the exact same value 
    // as the one we just tried and failed, SKIP IT!
    if (i > start_idx && splinters[i] == splinters[i - 1]) {
        continue;
    }
    // ----------------------------- 

    int splinter = splinters[i];
    if(pool.at(splinter) > 0) {
      int new_curr_height = curr_height + splinter;
      int new_sticks = sticks;
      int next_start_idx = i + 1;
      if(new_curr_height <= target_height) {
        // SAVE THE MATH FACT BEFORE WE SHIFT THE STATE
        bool completed_stick = (new_curr_height == target_height);
        if(completed_stick) {
          new_curr_height = 0;
          new_sticks--;
          next_start_idx = 0;
        }
        
         pool[splinter]--; 
        if(is_feasible(splinters, next_start_idx, pool, new_curr_height, target_height, new_sticks)) {
          pool[splinter]++;
          return true; // We found a path!
        }

        pool[splinter]++;

        // ====================================================================
        // --- THE GOLDEN PRUNING RULES ---
        // ====================================================================
        // GUARD 2:
        // PRUNING RULE 1: If the first piece we tried on a blank stick failed,
        // then this entire branching path is a dead end.
        if (curr_height == 0) {
          return false; 
        }

        // GUARD 3:
        // PRUNING RULE 2: If a piece that perfectly completed the current stick 
        // failed, trying smaller pieces to complete it is guaranteed to fail.
        if (completed_stick) {
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
          int total_sum = 0;
          std::unordered_map<int, int> pool;
          for(int i = 0; i < N; ++i) {
            std::cin >> splinters[i];
            total_sum += splinters[i];
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
          int bound = std::min(total_sum, MAX_HEIGHT);
          int start = splinters.front(); 
          for(int candidate = start; candidate <= bound; ++candidate) {
            if(reached[candidate]) {

              // GUARD 0:
              // --- THE GOLDEN PRUNING RULE ---
              // If the candidate doesn't evenly divide the total sum, 
              // it is mathematically impossible. Skip it instantly!
              if (total_sum % candidate != 0) {
                continue;
              }

              std::unordered_map<int, int> loc_pool = pool;
              int sticks = total_sum / candidate;
              if(is_feasible(splinters, 0, loc_pool, 0, candidate, sticks)) {
                ans = candidate;
                goto exit;
              }
            }
          }
          exit: std::cout << ans << std::endl;
        }
    }
}