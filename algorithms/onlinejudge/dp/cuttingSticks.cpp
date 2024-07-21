#include <cstdio>
#include <vector>
#include <iostream>
#include <iomanip>
#include <unordered_map>

namespace algorithms::onlinejudge::dp
{
    /*
        How do we tackle this problem? An initial approach might be this Complete Search algorithm: 
        Try all possible cutting points. Before that, we have to select an appropriate state definition for the problem: 
        The (intermediate) sticks. We can describe a stick with its two endpoints: left and right. 
        However, these two values can be very huge and this can complicate the solution later when we want to memoize their values. 
        We can take advantage of the fact that there are only n + 1 smaller sticks after cutting the original stick n times. 
        The endpoints of each smaller stick can be described by 0, the cutting point coordinates, and l. 
        Therefore, we will add two more coordinates so that A = {0, the original A, and l} 
        so that we can denote a stick by the indices of its endpoints in A
        cut(left, right) = min(cut(left, i) + cut(i, right) + (A[right]-A[left])) ∀i ∈ [left+1..right-1]
        try all possible cutting points and pick the best.
        The cost of a cut is the length of the current stick, captured in (A[right]-A[left]). 
        The answer can be found at cut(0, n+1)
    */
    const size_t  N = 10000;
    // std::vector<std::vector<int>> memo(N + 1, std::vector<int>(N + 1, -1));
    std::unordered_map<int, std::unordered_map<int, int>> memo;
    int minCost(int first, int last, std::vector<int>& cuts)
    {
        int n = cuts.size();
        if(first > last)
          return 0;

        if(auto i = memo.find(first); 
           i != memo.end())
          if(auto j = (*i).second.find(last);
             j != (*i).second.end())
            return (*j).second;

        int cost = INT32_MAX;
        for (int i = 0; i < n; i++)
          if(cuts[i] > first && 
             cuts[i] < last)
            cost = std::min(cost, minCost(first, cuts[i], cuts) + minCost(cuts[i], last, cuts) + last - first);

        return memo[first][last] = cost == INT32_MAX ? 0 : cost;
    }

    int minCostDp(int stick, std::vector<int> cuts)
    {
        int n = cuts.size();
        std::vector<std::vector<int>> dp(stick + 1, std::vector<int>(stick + 1, INT32_MAX));
        
         for(int r = 1; r <= stick; r++)
          for(int l = r - 1; l >= 0; l--)
          {
              int cost = INT32_MAX;
              for (int i = 0; i < n; i++)
                if(cuts[i] > l && cuts[i] < r)
                  cost = std::min(cost, r - l + dp[l][cuts[i]] + dp[cuts[i]][r]);
              dp[l][r] = cost == INT32_MAX ? 0 : cost;
          }
          return dp[0][stick];
    }

    void submit_10003()
    {
        int l, n;
        while(scanf("%d", &l), l)
        {
           scanf("%d",&n);
           std::vector<int> cuts(n);
           for(int i = 0; i < n; i++)
             scanf("%d", &cuts[i]);
           printf("The minimum cutting is %d.\n", minCost(0, l, cuts));
       }
    }
}