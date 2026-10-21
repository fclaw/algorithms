/*
───────────────────────────────────────────────────────────────
🧳 UVa 12063 Zeros and Ones, https://onlinejudge.org/external/120/12063.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




// Cache dimension explanation:
// [pos]: The index of the current bit we are inspecting (up to 64).
// [bits_left]: The number of '1' bits we still need to place (up to N/2, max 32).
// [rem]: The running remainder modulo K (up to 100).
ll cache[66][40][102];


/**
 * Recursive function to count valid binary numbers using top-down DP.
 * 
 * @param pos       The index of the last placed '1' bit (0-indexed from right to left).
 * @param bits_left How many more '1' bits need to be placed.
 * @param rem       The current accumulated remainder modulo K.
 * @param N         The total length of the binary string.
 * @param K         The divisor.
 */
ll count_numbers(int pos, int bits_left, int rem, int N, int K) {

  // Base Case: All required '1' bits have been successfully placed.
  if(bits_left == 0) {
    // If the accumulated number is perfectly divisible by K, we found 1 valid combination.
    if(rem == 0) {
      return 1LL;
    } else {
      return 0LL; // Invalid combination (not a multiple of K).
    }
  }

  // Memoization: Return the answer immediately if this exact state was already calculated.
  // Note: ~x is true for any integer except -1. If cache is initialized to -1, this checks if it's computed.
  if(~cache[pos][bits_left][rem]) {
    // Returning cached result to avoid redundant branching (O(1) lookup)
    return cache[pos][bits_left][rem];
  }

  ll counter = 0LL;
  
  // Transition: Loop through all possible lower positions 'i' to place the NEXT '1' bit.
  // This effectively implicitly places '0's in all the skipped bit positions between 'pos' and 'i'.
  for(int i = pos - 1; i >= 0; --i) {
    
    // Optimization Note: If the number of remaining positions available (i + 1) 
    // is strictly less than the number of '1' bits we still need to place (bits_left),
    // it's mathematically impossible to finish. We can safely break the loop early.
    if (i + 1 < bits_left) {
        break; 
    }

    // Calculate the value added by placing a '1' at bit position 'i' (2^i)
    ull num = (1ULL << i);
    
    // Compute the new remainder when adding this bit value
    int next_rem = ((ull)rem + num) % K;
    
    // Recurse to place the next '1' bit, decreasing the required '1' count by 1
    counter += count_numbers(i, bits_left - 1, next_rem, N, K);
  }
  
  // Save the final computed count to the cache for this state and return it
  return (cache[pos][bits_left][rem] = counter);

}


namespace algorithms::onlinejudge::advanced_topics::zeros_and_ones
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
        stdin_read(t_cases);
        while(t_cases--) {
          int N, K;
          stdin_read(N, K);
          ll ans = 0LL;
          if(N % 2 || K == 0) {
            ans = 0LL;
          } else {
            std::memset(cache, -1LL, sizeof cache);
            ans = count_numbers(N - 1, N / 2 - 1, (1ULL << (N - 1)) % K, N, K);
          }
          printf("Case %d: %lld\n", t_case++, ans);
        }
    }
}