#include <vector>
#include <unordered_map>
#include <iostream>


void printViaDp(std::vector<std::vector<int>> dp)
{
    for ( const auto &row : dp )
    {
        for ( const auto &s : row ) 
          std::cout << std::setw(5) << s << ' ';
        std::cout << std::endl;
    }
}

namespace algorithms::dp::leetcode
{
    // https://leetcode.com/problems/delete-and-earn
    /*
       You are given an integer array nums. 
       You want to maximize the number of points you get by performing the following operation any number of times:
       Pick any nums[i] and delete it to earn nums[i] points. 
       Afterwards, you must delete every element equal to nums[i] - 1 and every element equal to nums[i] + 1.
       Return the maximum number of points you can earn by applying the above operation some number of times
    */   
    int rec(std::vector<int> xs, int first, int last, std::unordered_map<int, int> freq, std::vector<std::vector<int>>& memo)
    {
        // boundary case
        if(first >= last)
          return 0;

        if(memo[first][last] != -1)
          return memo[first][last];

        int reward = 0;
        int is_taken = 0;
        for (int i = first; i < last; i++)
        {
            if(is_taken == xs[i])
              continue;

            is_taken = xs[i];

            int cnt = freq[xs[i]];
            int left_cnt = freq[xs[i] - 1];
            int right_cnt = freq[xs[i] + 1];

            int left_reward = rec(xs, first, i - left_cnt, freq, memo);
            int right_reward = rec(xs, i + cnt + right_cnt + 1, last, freq, memo);
            reward = std::max(reward, left_reward + cnt * xs[i] + right_reward);
        }
        return memo[first][last] = reward;
    }

    int viaDp(std::vector<int> xs)
    {
        int n = xs.size();
        std::vector<std::vector<int>> dp(n + 2, std::vector<int>(n + 2, 0));

        for(int i = 1; i <= n; i++)
          dp[i][i] = xs[i - 1];

        for(int left = 1; left <= n - 1; left++) // left
          for(int right = left; right <= n; right++)
              for(int i = left; i < right; i++)
              {
                  std::cout << "i: " << i << 
                    "left: " << left << ", right: " << right <<
                  ", xs[i]: " << xs[i] << ", dp[left][i - 2]: " << dp[left][i - 2] << ", dp[i + 2][right]: " << dp[i + 2][right] << std::endl;
                  dp[left][right] = std::max(dp[left][right], dp[left][i - 2] + xs[i] + dp[i + 2][right]);
              }

        printViaDp(dp);      

        return dp[1][n];
    }

    int deleteAndEarn(std::vector<int> nums)
    { 
        std::sort(nums.begin(), nums.end()); // n * log(n)
        std::unordered_map<int, int> freq;
        int n = nums.size();

        std::vector<std::vector<int>> memo(n + 1, std::vector<int>(n + 1, -1));

        for(auto n : nums) // n
          freq[n]++;

        // return rec(nums, 0, n, freq, memo);
        return viaDp(nums);
    }
}