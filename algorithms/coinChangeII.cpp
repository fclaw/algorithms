
#include <vector>
#include <iostream>

namespace leetcode::dp
{
    /*
      https://leetcode.com/problems/coin-change-ii
      You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.
      Return the number of combinations that make up that amount. If that amount of money cannot be made up by any combination of the coins, return 0.
      You may assume that you have an infinite number of each kind of coin.
      The answer is guaranteed to fit into a signed 32-bit integer.
      
        Input: amount = 5, coins = [1,2,5]
        Output: 4
        Explanation: there are four ways to make up the amount:
        5=5
        5=2+2+1
        5=2+1+1+1
        5=1+1+1+1+1

        Constraints:
         1 <= coins.length <= 300
         1 <= coins[i] <= 5000
         All the values of coins are unique.
         0 <= amount <= 5000
    */
    int changeDp(int amount, std::vector<int>& coins) 
    {
        std::vector<int> dp(amount + 1);
        dp[0] = 1;
        for(auto c : coins)
          for (auto i = c; i <= amount; i++)
            dp[i] += dp[i - c];

        return dp[amount];
    }

    // for every coin there are two ways to make up a target:
    // target 5, coins [1, 2, 5]
    // 1 try to get a target with only a coin (target: 5, coin: 2, can we make up 5 with only 2 (5 = 2 + 2 + 2 ...) )
    // 2 subtract coin from a target and try making up the leftover with the rest of coins (5 - 2 = 3, coins: [1, 5] )
    // bottom cases: amount becomes zero or negative
    // if amount becomes zero: 1
    // if amount is negative then there is no way to make up amount: 0
    int changeRecursive(int amount, std::vector<int>& coins, int idx) { return 0; }
    int change(int amount, std::vector<int>& coins) { return changeDp(amount, coins); }
}