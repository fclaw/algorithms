/*
───────────────────────────────────────────────────────────────
🧳 UVa 12416 Excessive Space Remover, rt: s
───────────────────────────────────────────────────────────────
 *
 * --- Analysis: From String Simulation to a Logarithmic Formula ---
 *
 * The problem describes a process of repeatedly applying a "replace all" action, where
 * every occurrence of two consecutive spaces ("  ") is replaced by a single space (" ").
 * We need to find the total number of actions required until no more changes can be made.
 *
 * A direct simulation of the string replacement would be too slow and complex. The key
 * is to find a mathematical pattern in the process.
 *
 *
 * ### Step 1: Analyze a Single Block of Spaces ###
 *
 * Let's consider a block of `S` consecutive spaces.
 *   - After 1 action, `S` spaces become `ceil(S / 2.0)` spaces.
 *   - After 2 actions, they become `ceil(ceil(S / 2.0) / 2.0)` spaces.
 *
 * This is a process of repeatedly taking the ceiling of a division by two. The number
 * of times this must be done until the result is 1 is the definition of the
 * ceiling of the base-2 logarithm: `ceil(log₂(S))`.
 *
 *
 * ### Step 2: The Critical Insight - The Largest Block Dictates the Pace ###
 *
 * The "replace all" action is applied to all blocks of spaces in the string
 * simultaneously in each step.
 *
 *   - A small block of spaces (e.g., 2 spaces) will be resolved quickly (in 1 action).
 *   - A larger block of spaces (e.g., 8 spaces) will take longer (3 actions).
 *
 * The process only stops when ALL blocks are resolved (i.e., contain no "  " pairs).
 * Therefore, the total number of actions required for the entire string is determined
 * by the single block of spaces that takes the most actions to resolve. This will
 * always be the largest block of consecutive spaces.
 *
 *
 * ### Final O(L) Algorithm (where L is the length of the string) ###
 *
 * The problem elegantly reduces to a simple, two-step algorithm:
 *
 * 1.  **Find the Maximum Length:**
 *     - Iterate through the input string once to find the maximum number of
 *       consecutive spaces. Let this be `S_max`.
 *
 * 2.  **Apply the Logarithm:**
 *     - The total number of actions is `ceil(log₂(S_max))`.
 *
 * This can be calculated using floating-point math (`ceil(log2(S_max))`) or, more
 * robustly, with a simple integer loop that simulates the halving process on `S_max`.
 *
 * Example: `S_max = 9`
 *   actions = 0
 *   while (9 > 1): actions++, S_max = (9+1)/2 = 5
 *   while (5 > 1): actions++, S_max = (5+1)/2 = 3
 *   while (3 > 1): actions++, S_max = (3+1)/2 = 2
 *   while (2 > 1): actions++, S_max = (2+1)/2 = 1. Loop terminates.
 *   Final actions = 4.  (Which is `ceil(log₂(9))`).
 *
 * This approach solves the problem efficiently with a single pass over the string.
 *
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



namespace algorithms::onlinejudge::maths::excessive_space_removal
{
    /** https://onlinejudge.org/external/124/12416.pdf */
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
          
        std::string line;
        while (std::getline(std::cin, line)) {
          int max_spaces = 0;
          int current_spaces = 0;
          for (char c : line) {
            if (std::isspace(c)) {
              current_spaces++;
              max_spaces = std::max(max_spaces, current_spaces);
            } else {
              current_spaces = 0;
            }
          }
          // actions based on max_spaces
          std::cout << std::ceil(std::log2(max_spaces)) << '\n';
        }  
    }
}