/*
================================================================================
 Key Observation for DP State Reduction in Ferry Loading Problem
================================================================================

In the classic ferry loading problem, the state is often represented as:
    f(i, leftRemain, rightRemain) — denoting the maximum number of cars 
    loaded when considering the i-th car, with the remaining space on 
    the left and right sides of the ferry.

However, we can reduce the dimensionality of this state by making the 
following crucial observation:

👉 The total space used by the first `i` cars is fixed and computable 
   via a prefix sum:
       used = prefix_sum[i]

👉 Given that, if we know `leftRemain`, we can deduce `rightRemain` as:
       rightRemain = ferryLength - used + leftRemain

This means the complete state (i, leftRemain, rightRemain) can be uniquely 
determined by just (i, leftRemain), reducing the DP from 3D to 2D.

Benefits:
- Drastically reduces memory usage and number of explored states.
- Enables faster DP lookup and simpler memoisation via 2D vector.

In implementation:
- Use prefix sums to track how much space has been used by the first `i` cars.
- Index the memo table by (i, leftRemain).

  IMPORTANT: Optimization Insight:
  ---------------------

  In the classic ferry loading problem, each car can be loaded on either the port (left) or starboard (right) side of the ferry, 
  each of which has a maximum capacity of 'L'. At each step 'i', we consider the remaining space on both sides to make our decision.

  However, a crucial observation allows us to reduce the DP state:

    - Let `prefix_sum[i]` be the total length of all cars loaded so far (from 0 to i-1).
    - The total available space on the ferry is `2L` (L for each side).
    - If we store only the remaining space on the **port** side, `rem_l`, we can compute the remaining space on the **starboard** side as:

        rem_r = 2L - prefix_sum[i] - rem_l;

  This is valid because the sum of used space on both sides must equal `prefix_sum[i]`.
  Hence, instead of tracking both `rem_l` and `rem_r` explicitly, we only memoise on `(i, rem_l)`, 
  and derive `rem_r` dynamically. This effectively reduces the DP dimension from 3D to 2D,
  significantly improving space complexity and simplifying implementation.
================================================================================
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






enum Side { Port, Starboard };

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<vvi> vvvi;
typedef std::pair<int, std::vector<std::pair<int, Side>>> piv_side;



namespace algorithms::onlinejudge::dp::ferry
{
    /** https://onlinejudge.org/external/102/10261.pdf */
    // f(i, rem_l, rem_r) -> the number of cars already loaded
    // f(i, rem_l, rem_r) = 1 + min(f(i + 1, rem_l - cars(i).l, rem_r), f(i + 1, rem_l, rem_r - cars(i).l)), 
    // if conditions are met: rem_l >= cars(i).l,rem_r >= cars(i).l
    // base case: i == n -> 0
    piv_side def = {0, {}};
    vi prefix_sum;
    int ferry_l, l;
    piv_side knapsack(const vi& cars, int i, int rem_l, std::vector<std::vector<piv_side>>& memo)
    {
        if(i == (int)cars.size()) return def;

        if(~memo[i][rem_l].first) return memo[i][rem_l];

        piv_side best = def;
        if(rem_l - cars[i] >= 0) {
          auto left = knapsack(cars, i + 1, rem_l - cars[i], memo);
          left.first += 1;
          left.second.push_back({i, Port});
          if(left.first > best.first) best = left;
        }
        
        int rem_r = 2 * ferry_l - rem_l - prefix_sum[i];
        if(rem_r >= 0) { 
          auto right = knapsack(cars, i + 1, rem_l, memo);
          right.first += 1;
          right.second.push_back({i, Starboard});
          if(right.first > best.first) best = right;
        }

        return memo[i][rem_l] = best;
    }
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
        while(tc--)
        {
            std::cin >> ferry_l;
            ferry_l *= 100; // bring it to centimetres
            vi cars;
            while(while_read(l) && l) 
              cars.push_back(l);
            
            int s = (int)cars.size();

            if(s > 0) {
              prefix_sum.resize(s);
              prefix_sum[0] = cars[0];
              for (int i = 1; i < s; ++i)
                prefix_sum[i] = prefix_sum[i - 1] + cars[i];
            }

            std::vector<std::vector<piv_side>> memo(s + 1, std::vector<piv_side>(ferry_l + 1, {-1, {}}));
            piv_side ans = knapsack(cars, 0, ferry_l, memo);
            std::cout << ans.first << std::endl;
            auto xs = ans.second;
            std::sort(xs.begin(), xs.end(), [](auto &l, auto &r) {return l.first < r.first; });
            for(auto& x : xs) std::cout << (x.second == Port ? "port" : "starboard") << std::endl;
            if(tc) std::cout << std::endl;
        }  
    }
}