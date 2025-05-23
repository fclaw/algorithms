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
typedef std::pair<int, std::vector<Side>> piv_side;



namespace algorithms::onlinejudge::dp::ferry
{
    /** https://onlinejudge.org/external/102/10261.pdf */
    // f(i, rem_l, rem_r) -> the number of cars already loaded
    // f(i, rem_l, rem_r) = 1 + min(f(i + 1, rem_l - cars(i).l, rem_r), f(i + 1, rem_l, rem_r - cars(i).l)), 
    // if conditions are met: rem_l >= cars(i).l,rem_r >= cars(i).l
    // base case: i == n -> 0
    std::string print(Side s) { return s == Port ? "port" : "starboard"; }
    piv_side def = {0, {}};
    piv_side knapsack(const vi& cars, int i, int rem_l, int rem_r, std::vector<std::vector<piv_side>>& memo)
    {
        if(i == (int)cars.size()) return def;

        if(~memo[i][rem_l].first) return memo[i][rem_l];

        piv_side best = def;
        if(rem_l - cars[i] >= 0) {
          auto left = knapsack(cars, i + 1, rem_l - cars[i], rem_r, memo);
          left.first += 1;
          left.second.push_back(Port);
          if(left.first > best.first) best = left;
        }
        
        if(rem_r - cars[i] >= 0) { 
          auto right = knapsack(cars, i + 1, rem_l, rem_r - cars[i], memo);
          right.first += 1;
          right.second.push_back(Starboard);
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
        std::cin.ignore();
        while(tc--)
        {
            int ferry_l, l;
            std::cin >> ferry_l;
            ferry_l *= 100; // bring it to centimetres
            vi cars;
            while(while_read(l) && l) cars.push_back(l);
            
            int s = (int)cars.size();
            std::vector<std::vector<piv_side>> memo(s + 1, std::vector<piv_side>(ferry_l + 1, {-1, {}}));
            piv_side ans = knapsack(cars, 0, ferry_l, ferry_l, memo);
            std::cout << ans.first << std::endl;
            for(Side s : ans.second) std::cout << print(s) << std::endl;
            if(tc) std::cout << std::endl;
        }  
    }
}