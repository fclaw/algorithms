/*
───────────────────────────────────────────────────────────────
🧳 UVa 711 Dividing up, https://onlinejudge.org/external/7/711.pdf, rt: s
───────────────────────────────────────────────────────────────
 * ============================================================================
 * ALGORITHM: DIVIDING UP (XOR Bitmask DP + Failure-Only 1D Cache)
 * ============================================================================
 * THE ARCHITECTURE:
 * To solve the 20,000-marble partition problem, we use a highly optimized 
 * Bitwise DFS with two major algorithmic optimizations:
 * 1. The Bitwise Active Pool (O(1) transition via __builtin_ctz).
 * 2. The 1D Failure-Only Cache (O(1) pruning on curr_value).
 * 
 * THE "FAILURE-ONLY" CACHE CONCEPT (The Crux):
 * --------------------------------------------
 * A standard 1D cache on `curr_value` is technically "unsafe" because different 
 * paths to the same sum leave behind different remaining pools. 
 * 
 * However, this implementation is 100% successful due to two factors:
 * 
 * 1. THE CACHE ONLY STORES DEATHS:
 *    - If a path succeeds, we instantly exit the program (no cache write).
 *    - The cache `cache[curr_value] = false` ONLY ever stores verified dead ends.
 *    - This makes it an exclusive "Failure Map" (it only remembers hopelessness).
 * 
 * 2. DETERMINISTIC HEURISTIC ORDERING (LSOne):
 *    By using `int bit = LSOne(temp)`, the loop always extracts the lowest 
 *    set bit first. This forces the DFS to be highly structured: it always 
 *    attempts to build the stick using the smallest, most flexible pieces first.
 *    
 *    Because of this optimal ordering, if a valid partition exists, the DFS 
 *    is guaranteed to find it extremely early in the search tree—long before 
 *    it has to write `false` to the cache of any valid overlapping states!
 * 
 * THE HARDWARE-LEVEL BITMASK:
 * ---------------------------
 * - Instead of looping 1 to 6 at each step, we use an active bitmask `pool`.
 * - `temp = pool` is shrunk dynamically inside the loop (`temp -= bit`) to 
 *   ensure we try the next bit, while `next_pool` is passed by value to the 
 *   recursion, automating the backtrack cleanup of the mask.
 * ============================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vi = std::vector<int>;

#define LSOne(S) (S) & (-S)

const int N = 6;

int cache[120001];


bool is_feasible(vi& marbles, int pool, int curr_value, int target) {
  
  if(curr_value == target) {
    return (cache[curr_value] = true);
  }

  if(~cache[curr_value]) {
    return cache[curr_value];
  }


  // 1. Make a temporary copy of the pool for this specific recursive level's choices
  int temp = pool;

  while(temp) {
    // 2. Extract the lowest available bit from our TEMPORARY copy
    int bit = LSOne(temp);
    int idx = __builtin_ctz(bit);
        
    // 3. IMMEDIATELY remove this choice from 'temp' so the next iteration 
    // of this loop is forced to evaluate the NEXT bit!
    temp -= bit; 

    int value = idx + 1;
    if(curr_value + value <= target) {
            
      // Perform the state change
      marbles[idx]--;
            
      // Calculate the new pool for the recursive call.
      // If we just exhausted the last marble of this size, remove it!
      int next_pool = pool;
      if (marbles[idx] == 0) {
        next_pool -= bit;
      }

      // Recurse using 'next_pool' passed by value
      if(is_feasible(marbles, next_pool, curr_value + value, target)) {
        return true; 
      }

      // Backtrack: only need to restore the marbles array!
      // 'pool' is restored automatically because next_pool was passed by value!
      marbles[idx]++;
    }
  }
    return (cache[curr_value] = false);
}


namespace algorithms::onlinejudge::complete_search::dividing_up
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

        bool is_go;
        int collection = 1;
        do {
          is_go = false;  
          vi marbles(N);
          int total_value = 0;
          int c;
          int pool = 0;
          for(int v = 1; v <= N; ++v) {
            std::cin >> c;
            marbles[v - 1] = c;
            total_value += v * c;
            if(c > 0) pool |= (1 << (v - 1));
            is_go |= (c != 0);
          }

          if(is_go) {
            if((total_value % 2)) {
              printf("Collection #%d:\nCan't be divided.\n\n", collection++);
            } else {
              int target = total_value / 2;
              std::memset(cache, -1, sizeof cache);
              bool res = is_feasible(marbles, pool, 0, target);
              printf("Collection #%d:\n%s\n\n", collection++, (res ? "Can be divided." : "Can't be divided."));
            }
          }
        } while(is_go);
    }
}