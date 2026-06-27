/*
───────────────────────────────────────────────────────────────
🧳 UVa 11832 Account Book, https://onlinejudge.org/external/118/11832.pdf, rt: s
───────────────────────────────────────────────────────────────
 * ============================================================================
 * THE TWO SUBCLASSES OF DYNAMIC PROGRAMMING: SATISFIABILITY VS. OPTIMIZATION
 * ============================================================================
 * 
 * When designing a Dynamic Programming solution, the problem will always fall 
 * into one of two fundamental architectural classes. Recognizing this class 
 * dictates how you design your state-space, your memo table, and your traceback.
 * 
 * ----------------------------------------------------------------------------
 * CLASS 1: THE "FEASIBILITY / ALL-PATH" CLASS (Satisfiability)
 * ----------------------------------------------------------------------------
 * - Objective: Answer "Is it possible?" or determine properties of the UNION 
 *   of all mathematically valid paths (e.g., "Is this step '+' in ANY valid path?").
 * 
 * - The Challenge: A single optimal path is insufficient. We must explore the 
 *   entire web of valid states without getting lost in dead ends.
 * 
 * - The 2-Pass Pipeline Solution:
 *   1. Pass 1 (Feasibility): Build a boolean table: dp[state] = true/false.
 *      This maps out the valid "highways" of the search space.
 *   2. Pass 2 (Traceback/Union): We run a second DFS that only travels down 
 *      nodes marked `true` in Pass 1. We use a `visited` array to ensure we 
 *      never enter the same state twice, keeping the traversal at O(States) 
 *      while collecting all possible valid decisions.
 * 
 * - Classic Example: Account Book (UVa 11832).
 * 
 * ----------------------------------------------------------------------------
 * CLASS 2: THE "MIN-MAX / OPTIMAL" CLASS (Optimization)
 * ----------------------------------------------------------------------------
 * - Objective: Find the single BEST outcome (shortest, cheapest, most valuable).
 * 
 * - The Benefit: Because we only care about the absolute peak, we can aggressively 
 *   prune. If multiple paths reach the same state, we discard the worse ones 
 *   immediately. We do not need to keep alternative paths alive.
 * 
 * - The 1-Pass + Greedy Traceback Solution:
 *   1. Pass 1 (Optimization): Fill the table with optimal values: dp[state] = min_val.
 *   2. Pass 2 (Reconstruction): To find the actual physical path (e.g., the 
 *      Highways or the Edit Script), we do a single-pass O(N) "greedy" walk 
 *      starting from the end, simply choosing whichever neighbor matches the 
 *      optimal transition equation.
 * 
 * - Classic Examples: Knapsack, Edit Distance (UVa 164), LIS (UVa 10635).
 * ============================================================================
 * 
 * ============================================================================
 * ALGORITHM: ACCOUNT BOOK (UVa 11832) - RECOVERY & MEMOIZATION ARCHITECTURE
 * ============================================================================
 * This problem is solved using a 2-Pass DP (Feasibility + Traceback).
 * Below are the critical, system-level design rules discovered during 
 * debugging that guarantee correctness, prevention of SegFaults, and 0.000s speed.
 * 
 * ----------------------------------------------------------------------------
 * RULE 1: THE "COMPLETE GRAPH" RULE (Base-Case Memoization)
 * ----------------------------------------------------------------------------
 * In a 2-Pass DP, Pass 1 (can_reach) builds a map of the search space (DAG), 
 * and Pass 2 (restore) walks this map to reconstruct the signs.
 * 
 * - THE PITFALL: Returning the base case directly `return curr_sum == F` 
 *   without saving it to `memo[N][sum + OFFSET]`.
 * - THE CONSEQUENCE: The final row of the memo table remains -1 (unmapped). 
 *   When the traceback (Pass 2) reaches the very last element (i = N-1), it 
 *   queries `memo[N]` to see if the final step is valid. It finds -1, thinks 
 *   both '+' and '-' are dead ends, and leaves the last character UNASSIGNED.
 * - THE FIX: Always write your base case results directly into the DP table.
 *   `return memo[i][sum + OFFSET] = (sum == F ? 1 : 0);`
 * 
 * ----------------------------------------------------------------------------
 * RULE 2: THE "BOUNDARY GUARD" IN THE TRACEBACK (Preventing SegFaults)
 * ----------------------------------------------------------------------------
 * In the `restore` function, we must check if we have reached the end of the 
 * transactions BEFORE we do anything else.
 * 
 * - THE PITFALL: Omitting `if (i == figures.size()) return;` at the top.
 * - THE CONSEQUENCE: When i reaches N, the code will continue to execute and 
 *   attempt to check `figures[i]` (which is `figures[N]` -> Out of Bounds!) 
 *   and `memo[i + 1]` (which is `memo[N + 1]` -> Out of Bounds!). 
 *   This triggers an immediate Segmentation Fault (Abort Trap 6).
 * - THE FIX: Explicitly terminate the recursion at the very top of `restore` 
 *   before any array or vector accesses are made.
 * 
 * ----------------------------------------------------------------------------
 * RULE 3: THE "OFFSET" & "STATE REDUCTION"
 * ----------------------------------------------------------------------------
 * Because the cash flow can go negative (down to -40000), we add an OFFSET of 
 * 40000 to the second dimension of our 45x80005 `memo` and `visited` arrays.
 * 
 * To prevent a "Stack Overflow" (SegFault 11) caused by allocating these large 
 * arrays (18 MB total) on the limited CPU Stack, they MUST be declared in the 
 * GLOBAL SCOPE (Data Segment / BSS).
 * ============================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




using vi = std::vector<int>;


enum Sign { PLUS, MINUS, UNDEFINED, UNASSIGNED };

char signToChar(Sign sign) {
  switch(sign) {
    case PLUS:
      return '+';
      break;
    case MINUS:
      return '-';
      break;
    case UNDEFINED:
      return '?';
      break;
    default:
      return '\0';  
  }
}

// Sized safely to handle all constraints
// Memory footprint: 45 * 80005 * 4 bytes ≈ 14 Megabytes (extremely small!)
int memo[45][80005];
bool visited[45][80005];
const int OFFSET = 40000;



bool knapsack(const vi& figures, int i, int curr_sum, int target) {

      // Inside your recursion:
  int memo_sum = curr_sum + OFFSET;

  if(i == (int)figures.size()) {
    return (memo[i][memo_sum] = (curr_sum == target));
  }

  if(~memo[i][memo_sum]) {
    return memo[i][memo_sum];
  }

  bool plus_ans = knapsack(figures, i + 1, curr_sum + figures[i], target);
  bool minus_ans = knapsack(figures, i + 1, curr_sum - figures[i], target);

  return (memo[i][memo_sum] = (plus_ans || minus_ans));
}


void restoreTransactionSeq(const vi& figures, int i, int curr_sum, std::vector<Sign>& signs) {
   

   int memo_sum = curr_sum + OFFSET;

   if(visited[i][memo_sum] || 
      i == (int)figures.size()) {
     return; // already visited
   }
    
   visited[i][memo_sum] = true;

   if(memo[i + 1][curr_sum + figures[i] + OFFSET] == 1) {
      if(signs[i] == UNASSIGNED) {
        signs[i] = PLUS;
      } else if (signs[i] == MINUS) {
        signs[i] = UNDEFINED;
      }
      restoreTransactionSeq(figures, i + 1, curr_sum + figures[i], signs);
   }

   if(memo[i + 1][curr_sum - figures[i] + OFFSET] == 1) {
      if(signs[i] == UNASSIGNED) {
        signs[i] = MINUS;
      } else if (signs[i] == PLUS) {
        signs[i] = UNDEFINED;
      }
      restoreTransactionSeq(figures, i + 1, curr_sum - figures[i], signs);
   }

}



namespace algorithms::onlinejudge::dp::account_book
{
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

        int n, target;
        while(std::cin >> n >> target) {
          if(n == 0 && target == 0) {
            break;
          }
          vi figures(n);
          int sum = 0;
          for(int i = 0; i < n; ++i) {
            std::cin >> figures[i];
            sum += figures[i];
          }

          std::memset(memo, -1, sizeof memo);
          bool is_satisfied = knapsack(figures, 0, 0, target);
          if(is_satisfied) {
            std::vector<Sign> signs(n, UNASSIGNED);
            std::memset(visited, false, sizeof visited);
            restoreTransactionSeq(figures, 0, 0, signs);
            std::string seq;
            for(int i = 0; i < n; ++i) {
              seq += signToChar(signs[i]);
            }
            std::cout << seq << std::endl;
          } else {
            std::cout << "*" << std::endl;
          }
        }
    }
}