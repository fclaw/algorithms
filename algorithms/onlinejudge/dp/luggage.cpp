/*
───────────────────────────────────────────────────────────────
🧳 UVa 10664 - Luggage
───────────────────────────────────────────────────────────────

Problem Summary:
────────────────
You are given the weights of a set of luggage pieces. The task is to determine
whether it is possible to divide them into two groups with equal total weight.

Key Insight:
────────────
If the total weight is odd, partitioning into equal halves is impossible.
If even, the problem reduces to the classic **Subset Sum**:
→ Does there exist a subset whose total weight equals total_sum / 2?

DP Formulation:
───────────────
Let:
  - `target = total_sum / 2`
  - `f(i, curr_sum)` = true if it is possible to reach `curr_sum` using
    items from index `i` onwards.

Base Cases:
  - If `curr_sum == target`: return true (valid subset found).
  - If `i == n` or `curr_sum > target`: return false (out of bounds or overflow).

Transition:
  F(i, curr_sum) =
    f(i + 1, curr_sum)             // skip current item
    OR
    f(i + 1, curr_sum + w[i])      // include current item

Optimisation:
─────────────
- Can be solved using memoisation (2D DP table or unordered_map).
- Or iteratively with a 1D boolean array of size `target + 1`.

Final Answer:
- Whether `f(0, 0)` returns true.

  Transitioning from recursive formulation to bottom-up DP:
  
  Recursive form:
    f(i, curr_w) = f(i + 1, curr_w) 
                   OR 
                   f(i + 1, curr_w + weights[i])

  Goal:
    Convert into dp[i][curr_w] form (where dp[i][w] means: 
    is it possible to reach weight `w` using the first `i` weights)

  Observation:
    In f(i + 1, curr_w + weights[i]), `weights[i]` is *added*
    => in bottom-up DP, we reverse this direction:
       we transition *from* dp[i][curr_w] *to* dp[i + 1][curr_w + weights[i]]
       because we "consider" placing weights[i] in the current subset

  So the bottom-up equivalent is:
    for (int i = 0; i < n; ++i)
      for (int w = 0; w <= target; ++w)
        if (dp[i][w]) {
          dp[i + 1][w] = true;                    // skip weights[i]
          dp[i + 1][w + weights[i]] = true;       // take weights[i]
        }

  Note:
    You must ensure `w + weights[i] <= target` before updating that cell

───────────────────────────────────────────────────────────────
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
#include <sstream>


typedef std::vector<int> vi;
typedef std::vector<bool> vb;
typedef std::vector<vb> vvb;


namespace algorithms::onlinejudge::dp::luggage
{
    /** https://onlinejudge.org/external/106/10664.pdf */
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
        
        int tc;
        std::cin >> tc;
        std::cin.ignore();
        std::string in;
        while(tc--)
        {
            std::getline(std::cin, in);
            std::stringstream ss(in);
            int w;
            vi weighs;
            int total = 0;
            while(ss >> w) 
            { weighs.push_back(w); total += w; }

            if(total % 2) 
            { printf("NO\n"); continue; }

            int target = total / 2;
            int s = (int)weighs.size();
            // f(i, curr_w) = f(i + 1, curr_w) or f(i + 1, curr_w + weighs(i))
            // base case: curr_w == total -> true
            // check termination conditions: curr_w > target -> false
            // the answer lies in dp[s][target];
            vvb dp(s + 1, vb(target + 1, false));
            dp[0][0] = true;
            for(int i = 0; i < s; ++i)
              for(int w = 0; w <= target; ++w) {
                dp[i + 1][w] = dp[i][w];
                if(w >= weighs[i])
                  dp[i + 1][w] = dp[i][w] || dp[i][w - weighs[i]];
              }
            std::cout << (dp[s][target] ? "YES" : "NO") << std::endl;
        }  
    }
}