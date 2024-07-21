#include <vector>
#include <unordered_map>
#include <iostream>

namespace algorithms::dp::leetcode::delete_and_earn
{
    // https://leetcode.com/problems/delete-and-earn
    /*
       You are given an integer array nums. 
       You want to maximize the number of points you get by performing the following operation any number of times:
       Pick any nums[i] and delete it to earn nums[i] points. 
       Afterwards, you must delete every element equal to nums[i] - 1 and every element equal to nums[i] + 1.
       Return the maximum number of points you can earn by applying the above operation some number of times
    */
    std::unordered_map<int, std::unordered_map<int, int>> memo;
    std::unordered_map<int, int> l_memo;
    std::unordered_map<int, int> freq;
    int rec(std::vector<int>& xs, int first, int last)
    {
        // boundary case
        if(first >= last)
          return 0;

        if(auto i = memo.find(first); 
           i != memo.end())
          if(auto j = (*i).second.find(last);
             j != (*i).second.end())
            return (*j).second;

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

            int left_reward = rec(xs, first, i - left_cnt);
            int right_reward = rec(xs, i + cnt + right_cnt + 1, last);
            reward = std::max(reward, left_reward + cnt * xs[i] + right_reward);
        }
        return memo[first][last] = reward;
    }

    int deleteAndEarnDp(std::vector<int>& xs)
    {
         int n = xs.size();
         std::vector<std::vector<int>> dp(n, std::vector<int>(n + 1, 0));

         for(int right = 1; right <= n; right++)
           for(int left = right - 1; left >= 0; left--)
           {
              int reward = 0;
              int is_taken = 0;
              for(int i = left; i < right; i++)
              {
                 if(is_taken == xs[i])
                    continue;
                 is_taken = xs[i];

                 int cnt = freq[xs[i]];
                 int left_cnt = freq[xs[i] - 1];
                 int right_cnt = freq[xs[i] + 1];

                 int left_reward = i - left_cnt >= 0 ? dp[left][i - left_cnt] : 0;
                 int right_reward = i + cnt + right_cnt + 1 < n ? dp[i + cnt + right_cnt + 1][right] : 0;
                 reward = std::max(reward, left_reward + cnt * xs[i] + right_reward);   
              }  
              dp[left][right] = reward;
           }

         return dp[0][n];
    }
 
    
    // time complexity must be linear to meet the constraint of 10 ^ 4
    int deleteAndEarnDpOpt(std::vector<int>& xs)
    {
        int n = xs.size();
        // answer should be in (1, n)
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1, 0));
         
        for(int r = 1; r <= n; r++)
          for(int l = r - 1; l >= 1; l--)
          {
              int reward = 0;
              for(int i = l; i < r; i++)
              {
                  int left = i - 1 >= 0 ? dp[l][i - 1] : 0;
                  int right = i + 2 < n ? dp[i + 2][r] : 0;
                  reward = std::max(reward, left + i * xs[i] + right);
              }
              dp[l][r] = reward;
          }

          return dp[1][n];
    }

    int linearRec(int s, std::vector<int>& xs)
    {
        int n = xs.size();
        if(s >= n)
          return 0;
          
        if(auto i = l_memo.find(s); 
           i != l_memo.end())
            return (*i).second;

        int reward = 0; 
        for(int i = s; i < n; i++)
          reward = std::max(reward, i * xs[i] + linearRec(i + 2, xs));
        return l_memo[s] = reward;
    }

    int linearDp(std::vector<int>& xs)
    {
        int n = xs.size();
        std::vector<int> dp(n, 0);
        dp[1] = xs[1];
        for(int i = 2; i < n; i++)
          dp[i] = std::max(dp[i - 1], i * xs[i] + dp[i - 2]);

        return dp[n - 1];
    }

    int deleteAndEarn(std::vector<int> nums)
    { 
        int n = nums.size();
        std::sort(nums.begin(), nums.end()); // n * log(n)
        std::vector<int> xs(nums[n - 1] + 1);
 
        for(auto n : nums) // n
          freq[n]++;

        for(int i = 1; i < xs.size(); i++)
          xs[i] = freq[i];
 
        // return deleteAndEarnDpOpt(xs);
        return linearDp(xs);
    }
}