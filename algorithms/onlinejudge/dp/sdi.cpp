#include <vector>
#include <iostream>

namespace algorithms::onlinejudge::dp
{
    /*
      https://onlinejudge.org/external/4/481.pdf
    */
    std::tuple<int, std::vector<int>> hitMaxMissiles(std::vector<int> nums) 
    {
        std::vector<int> dp(nums.size(), 1);
        // dp[0] = 1;
        for (int i = 1; i < dp.size(); i++)
          for (int j = 0; j < i; j++)
            if(nums[i] > nums[j])
              dp[i] = std::max(dp[i], 1 + dp[j]);

        auto first = dp.begin();
        auto last = dp.end();

        auto max_iter = max_element(first, last);
        int pos = max_iter - first;
  
        std::vector<int> lis;
        lis.push_back(nums[pos]);
        int i = pos - 1;
        while(i >= 0)
        {
            if(dp[i] == dp[pos] - 1 && 
               nums[i] < nums[pos])
            { 
                lis.push_back(nums[i]);
                pos = i;
                i--;
            }
            else i--;
        }

        std::reverse(lis.begin(), lis.end());

        return {*max_iter, lis};
    }
}