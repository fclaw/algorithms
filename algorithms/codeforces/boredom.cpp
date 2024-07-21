#include <vector>
#include <cstdio>
#include <unordered_map>
#include <iostream>

using ll = long long;

namespace algorithms::codeforces
{

     ll solve_455_a(std::vector<int> nums)
     {
        int n = nums.size();
        std::sort(nums.begin(), nums.end()); // n * log(n)
        std::vector<ll> xs(nums[n - 1] + 1);
        std::unordered_map<int, int> freq;

        for(auto n : nums) // n
          freq[n]++;

        int m = xs.size();

        for(int i = 1; i < m; i++)
          xs[i] = freq[i];

        std::vector<ll> dp(m, 0);
        dp[1] = xs[1];
        for(int i = 2; i < m; i++)
          dp[i] = std::max(dp[i - 1], i * xs[i] + dp[i - 2]);

        return dp[m - 1];
     } 

     void submit_455_a()
     {
         int n;
         scanf("%d", &n);
         std::vector<int> xs(n);
         for (int i = 0; i < n; i++)
           scanf("%d", &xs[i]);
         printf("%llu\n", solve_455_a(xs));  
     }
}