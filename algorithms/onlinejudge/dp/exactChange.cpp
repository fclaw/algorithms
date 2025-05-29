/*
───────────────────────────────────────────────────────────────
🧳 UVa 11517 exact change, rt: s
───────────────────────────────────────────────────────────────

  Traversal Direction in DP for Coin Change / Knapsack:

  - Unbounded Case (each coin can be reused multiple times):
    → Traverse 'sum' from low to high (upwards).
    → Mirrors recursion that allows reusing the same coin.
    → Example: Unbounded Knapsack / Classic Coin Change.

  - 0/1 Case (each coin can be used only once):
    → Traverse 'sum' from high to low (downwards).
    → Mirrors recursion that moves to the next coin and disallows reuse.
    → Simulates subset combinations.
    → Example: 0/1 Knapsack / Exact Change with distinct coins.

  Choosing the correct direction is essential to avoid overcounting and
  to correctly model the problem's constraints.
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


using namespace std;

struct Ans
{
    int diff;
    int counter;
    int sum;
};


bool operator < (const Ans& lhs, const Ans& rhs) 
{ return lhs.diff < rhs.diff || (lhs.diff == rhs.diff && lhs.counter < rhs.counter); }


bool operator != (const Ans& lhs, const Ans& rhs) 
{ return !(lhs.diff == rhs.diff && lhs.counter == rhs.counter && lhs.sum == rhs.sum); }

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<Ans> v_ans;
typedef std::vector<v_ans> vv_ans;


const int MAX = (int)1e5;
Ans def = {MAX, 0, 0};

namespace algorithms::onlinejudge::dp::exact_change
{
    /** https://onlinejudge.org/external/115/11517.pdf */
    int tc, price, n;
    vv_ans memo;
    Ans coin_change(const vi& coins, int i, int sum)
    {
        if(i == n && sum < price) return def;
        if(sum >= price) {
            Ans res = def;
            res.diff = sum - price;
            return res;
        }
         
        Ans& best = memo[i][sum];
        if(best != def) return best;

        best = def;
        for(int j = i; j < n; ++j) {
          Ans local_ans = coin_change(coins, j + 1, sum + coins[j]);
          local_ans.counter += 1;
          local_ans.sum += coins[j];
          best = std::min(best, local_ans);
        }
        return best;
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
        
        while_read(tc);
        while(tc--)
        {
            while_read(price);
            while_read(n);
            vi coins(n);
            int sum_of_coins = 0;
            loop(n, [&coins, &sum_of_coins] (int i) {
                while_read(coins[i]);
                sum_of_coins += coins[i];
            });

            v_ans dp(sum_of_coins + 1, def);
            dp[0] = {0, 0, 0}; // base case

            for (int c : coins)
              for (int s = sum_of_coins; s >= 0; --s)
                if(s + c <= sum_of_coins &&
                   dp[s].diff != MAX) {
                  Ans new_ans = dp[s];
                  new_ans.sum += c;
                  new_ans.counter += 1;
                  new_ans.diff = new_ans.sum - price;
                  dp[s + c] = std::min(dp[s + c], new_ans);
                }

            Ans best = *std::min_element(dp.begin() + price, dp.end());
            std::cout << best.sum << " " << best.counter << std::endl;
        }  
    }
}