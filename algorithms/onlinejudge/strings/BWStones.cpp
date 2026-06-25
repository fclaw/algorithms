/*
───────────────────────────────────────────────────────────────
🧳 UVa 12855 Black and white stones, https://onlinejudge.org/external/128/12855.pdf, rt: s
───────────────────────────────────────────────────────────────
 * ============================================================================
 * ALGORITHM: O(N) GREEDY TWO-POINTERS (Black and White Stones - UVa 12855)
 * ============================================================================
 * THE PROBLEM:
 * We are given a string S of 'B' (Black) and 'W' (White) stones. We must reorder 
 * them so all 'B's are to the left of all 'W's. 
 * - Swapping ANY two stones costs A.
 * - Swapping ADJACENT stones costs A - B (due to a refund B).
 * 
 * WHY DYNAMIC PROGRAMMING IS DEAD ON ARRIVAL:
 * 1. Let N be the length of S (N <= 5000), and W be the number of White stones.
 * 2. The number of unique string arrangements (states) is the binomial coefficient:
 *         Total States = C(N, W)
 * 3. In the worst-case (W = N/2 = 2500):
 *         Total States = C(5000, 2500) ≈ 10^1500.
 * 4. This is an unfathomably large state-space. Any DP, BFS, or state-based 
 *    search will result in an instant Memory Limit Exceeded (MLE) or TLE.
 * 
 * THE GREEDY INSIGHT:
 * Since we want all 'B's on the left, let N_b be the total number of 'B's.
 * In the final sorted string:
 * - The first N_b positions MUST be occupied by 'B's.
 * - The remaining positions MUST be occupied by 'W's.
 * 
 * Therefore, any 'W' currently in the first N_b positions is MISMATCHED.
 * Any 'B' currently in the remaining positions is MISMATCHED.
 * 
 * THE TWO-POINTER MATCHING:
 * 1. Collect the indices of all mismatched 'W's (from left to right).
 * 2. Collect the indices of all mismatched 'B's (from right to left).
 * 3. Pair them up from the outside-in. For each pair (w_idx, b_idx):
 *    - Option 1 (Direct Swap): Swap them directly. Cost = A.
 *    - Option 2 (Adjacent Slide): Slide the 'B' past the 'W's between them.
 *      The number of 'W's between them is exactly (b_idx - w_idx).
 *      Cost = (b_idx - w_idx) * (A - B).
 * 
 * 4. We take the minimum of these two options for every pair:
 *      Pair Cost = min(A, (b_idx - w_idx) * (A - B))
 * 
 * COMPLEXITY:
 * - Time Complexity:  O(N) — One single pass to count and collect indices.
 * - Space Complexity: O(N) — To store the mismatched indices.
 * ============================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using ll = long long;

char BLACK = 'B';
char WHITE = 'W';



namespace algorithms::onlinejudge::strings::bw_stones
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

        ll penalty, reimbursement;
        std::string stones;
        while(while_read(penalty, reimbursement)) {
          std::cin.ignore();  
          std::getline(std::cin, stones);
          // ....
        }
    }
}