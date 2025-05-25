/*
───────────────────────────────────────────────────────────────
🧳 UVa 10819 Trouble of 13-Dots, rt: 0.530s
───────────────────────────────────────────────────────────────

==================================================
  DP Recurrence and Table Initialization Commentary
==================================================

The recurrence:
---------------
We define:
    int knapsack(i, spend) = maximum favour from items[i..n-1] with current spend.

We always include the "skip" option:
    skip = knapsack(i + 1, spend);
    best = max(best, skip);

This guarantees that even if no item is taken, the function returns a valid favour value (≥ 0).
Hence, there is NO NEED to initialise `best = INT32_MIN`, because:
    - The skip case provides a baseline result.
    - This is logically consistent with the base case: if(i == n) return 0.

DP Table Setup:
---------------
To mirror this in bottom-up DP:

    vvi dp(n + 1, vi(max_spend + 1, INT32_MIN));
    dp[0][0] = 0; // Base case: no items, no money spent → 0 favour.

Why INT32_MIN?
    - Represents an unreachable or invalid state.
    - Ensures we don’t accidentally maximise over garbage values.

Transitions only propagate values from valid states, so:
    - We never add to or compare against INT32_MIN directly.
    - Only states with proper spending constraints are considered.

Final Answer:
-------------
After DP is populated, extract the answer as:

    int ans = 0;
    for (int s = 0; s <= max_spend; ++s)
        if (s <= budget || (s > THRESHOLD && s <= budget + extra))
            ans = max(ans, dp[n][s]);

This ensures the final answer respects the mixed budget rule.

Conclusion:
-----------
Using skip as the baseline in recurrence ensures correctness without needing `best = INT32_MIN`.
Using INT32_MIN in the DP table safely marks unreachable states and aligns with the recurrence logic.
*/


#include "../debug.h"
#include "../../aux.h"

#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>
#include <bitset>
#include <unordered_map>
#include <unordered_set>




struct Item
{
    int price;
    int favour_index;
};


std::ostream& operator << 
  (std::ostream& out, const Item& item) 
  { return out << "{" << item.price << ", "  << item.favour_index << "}"; }

bool operator < (const Item& li, const Item& ri) { return li.price < ri.price; }


typedef std::vector<Item> v_item;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;



namespace algorithms::onlinejudge::dp::troubleOf13Dots
{
    /** https://onlinejudge.org/external/108/10819.pdf */
    const int THRESHOLD = 2000;
    const int extra = 200;
    int budget, n; 
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
        
        while(while_read(budget, n))
        {
            int p, f;
            v_item items(n); 
            loop(n, [&items, &p, &f](int i){
               while_read(p, f);
               items[i] = {p, f};
            });

            std::sort(items.begin(), items.end());
            int max_spend = std::max(budget, THRESHOLD) + extra;
            vvi dp(n + 1, vi(max_spend + 1, INT32_MIN));
            dp[0][0] = 0;
            for(int i = 0; i < n; ++i)
              for(int s = 0; s <= max_spend; ++s) {
                  dp[i + 1][s] = dp[i][s]; // skip
                  if(s >= items[i].price && 
                     (s <= budget || 
                      (s > THRESHOLD && 
                       s <= budget + extra)))
                    dp[i + 1][s]  = std::max(dp[i + 1][s], items[i].favour_index + dp[i][s - items[i].price]);
              }
            
            int ans = 0;
            for(int i = 0; i <= max_spend; ++i)
              if(i <= budget || 
                 (i > THRESHOLD && 
                  i <= budget + extra))
                ans = std::max(ans, dp[n][i]);     
            std::cout << ans << std::endl;
        }
    }
}