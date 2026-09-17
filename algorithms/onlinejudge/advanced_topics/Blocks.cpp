/*
───────────────────────────────────────────────────────────────
🧳 UVa 10559 Blocks, https://onlinejudge.org/external/105/10559.pdf, rt: s
───────────────────────────────────────────────────────────────
* ============================================================================
 * 🧠 INTERVAL DP: The Chain Propagation Mechanism ("Passing the Torch")
 * ============================================================================
 * 
 * 1. THE PROBLEM: Linking Multiple Distant Identical Elements
 * -----------------------------------------------------------
 * Consider a sequence with 3 or more separated identical items:
 *     [A_l] ... (gap 1) ... [A_k] ... (gap 2) ... [A_m]
 * 
 * Ideally, we want to clear (gap 1) and (gap 2) so that ALL three 'A's 
 * collapse into a single contiguous block: [A_l, A_k, A_m], which can then 
 * be eliminated together in ONE single move (or scored as (c_l + c_k + c_m)^2).
 * 
 * 2. THE FATAL TRAP: Premature Termination (The Broken Chain)
 * ------------------------------------------------------------
 * A common naive recurrence attempts:
 *     cost = 1 + dp(l + 1, k - 1) + dp(k + 1, r)
 *                                   ▲
 *                                   └── 🚨 THE SEVERED LINK!
 * 
 * Why this fails:
 *   • Adding '+ 1' prematurely declares: "I am throwing away pair (A_l, A_k) 
 *     right now as a closed, finished move."
 *   • Jumping to 'k + 1' permanently excludes A_k from the future!
 *   • A_m (the 3rd item) is now completely isolated in the right subproblem.
 *   • RESULT: The chain is capped at strictly 2 elements! Triples and 
 *     quadruples are permanently lost.
 * 
 * 3. THE RELAY MECHANISM: "Passing the Torch" via dp(k, r)
 * -------------------------------------------------------
 * The correct formulation preserves the chain:
 * 
 *     cost = dp(l + 1, k - 1)  +  dp(k, r)
 *                                 ▲
 *                                 └── 🔦 THE TORCH IS PASSED!
 * 
 * How the chain reaction propagates:
 *   Step 1: The gap [l + 1 ... k - 1] is completely eradicated as its own 
 *           subproblem via `dp(l + 1, k - 1)`.
 *   Step 2: With the middle junk gone, A_l and A_k physically touch!
 *   Step 3: We do NOT pay +1 move yet. A_l is absorbed into A_k.
 *   Step 4: In the remaining subproblem [k, r], A_k becomes the NEW LEADER 
 *           at the front of the interval.
 *   Step 5: When dp(k, r) evaluates, A_k looks across (gap 2), finds A_m, 
 *           and absorbs it too!
 * 
 * Inductive Propagation:
 *     A_l  ──(absorb)──►  A_k  ──(absorb)──►  A_m  ──(absorb)──► ... ──► FINALE
 * 
 * 4. GENERALIZATION (2D vs 3D):
 * -----------------------------
 * • In 2D Flat Cost (UVa 11523 - Recycling, cost = 1 move):
 *       dp(l + 1, k - 1) + dp(k, r)
 *   (A_k acts as the positional placeholder; no baggage needed).
 * 
 * • In 3D Convex Reward (LeetCode 546 - Remove Boxes, reward = K^2):
 *       dp(l + 1, k - 1, 0) + dp(k, r, cnt + freq[l])
 *   (A_k inherits the accumulated physical mass 'cnt + freq[l]' of the snowball!).
 * ============================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using vi = std::vector<int>;


constexpr int MAX = 200;

int cache[MAX + 1][MAX + 1][MAX + 1];

int dp(int left, int right, int cnt, const vi& boxes, const vi& freq) {

  if(left > right) {
    return 0;
  }
  
  if(left == right) {
    return (freq[left] + cnt) * (freq[left] + cnt);
  } 

  if(~cache[left][right][cnt]) {
    return cache[left][right][cnt];
  }

  int best = (freq[left] + cnt) * (freq[left] + cnt) + dp(left + 1, right, 0, boxes, freq);
 
  for(int k = left + 1; k <= right; ++k) {
    if(boxes[k] == boxes[left]) {
      int new_cnt = cnt + freq[left];
      best = std::max(best, dp(left + 1, k - 1, 0, boxes, freq) + dp(k, right, new_cnt, boxes, freq));
    }
  }
  
  return (cache[left][right][cnt] = best);
}


namespace algorithms::onlinejudge::advanced_topics::blocks
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
          int n;
          std::cin >> n;
          vi boxes(n);
          for(int i = 0; i < n; ++i) {
            std::cin >> boxes[i];
          }

          vi unique_boxes;
          vi freq;

          for (int i = 0; i < (int)boxes.size(); ) {
            int j = i;
            // Find the end of consecutive identical elements:
            while (j < (int)boxes.size() && boxes[j] == boxes[i]) j++;

            unique_boxes.push_back(boxes[i]);
            freq.push_back(j - i); // Count of this block!

            i = j; // Jump directly to the next distinct element
          }

          std::memset(cache, -1, sizeof cache);
          printf("Case %d: %d\n", t_case++, dp(0, unique_boxes.size() - 1, 0, unique_boxes, freq));
        }
    }
}