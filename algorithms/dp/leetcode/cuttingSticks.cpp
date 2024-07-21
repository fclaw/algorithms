#include <vector>
#include <iostream>
#include <iomanip>

using ll = long long;

namespace algorithms::leetcode::dp
{
    // https://leetcode.com/problems/minimum-cost-to-cut-a-stick
    /*
      Given an integer array cuts where cuts[i] denotes a position you should perform a cut at.
      You should perform the cuts in order, you can change the order of the cuts as you wish.
      The cost of one cut is the length of the stick to be cut, the total cost is the sum of costs of all cuts. 
      When you cut a stick, it will be split into two smaller sticks (i.e. the sum of their lengths is the length of the stick before the cut). 
      Please refer to the first example for a better explanation.
      Return the minimum total cost of the cuts.
    */
    ll minCost(int stick, std::vector<int> cuts) 
    {
        std::sort(cuts.begin(), cuts.end());
        int n = cuts.size();
        std::vector<std::vector<ll>> dp(stick + 1, std::vector<ll>(stick + 1, INT64_MAX));
        
        for(int r = 1; r <= stick; r++)
          for(int l = r - 1; l >= 0; l--)
          {
             ll cost = INT64_MAX;
             for (int i = 0; i < n; i++)
               if(cuts[i] > l && 
                  cuts[i] < r)
                 cost = std::min(cost, r - l + dp[l][cuts[i]] + dp[cuts[i]][r]);
             dp[l][r] = cost == INT64_MAX ? 0 : cost;
          }

        return dp[0][stick];
    }
}