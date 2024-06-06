#include <vector>

using name

// https://leetcode.com/problems/coin-change
/*
The length of the memoization table is amount + 1 because we need to store results for all possible values from 0 up to the target amount. Here’s a detailed explanation:

Range of Subproblems
In the coin change problem, we need to determine the minimum number of coins required for every sub-amount from 0 to the given amount. This includes:

Base Case: The minimum number of coins required to make up 0 amount is 0.
Sub-Amounts: For every amount from 1 to amount, we need to compute the minimum number of coins required.
Memoization Table
To efficiently store and retrieve the results of these subproblems, we use a memoization table. The index of this table represents the sub-amount, and the value at each index represents the minimum number of coins needed to make up that amount.

Index 0: Corresponds to amount 0.
Index 1: Corresponds to amount 1.
...
Index amount: Corresponds to the given target amount.
By having a table of size amount + 1, we ensure that we can store results for all amounts from 0 to amount.

Example
Consider the given amount is 11. The memoization table needs to store results for amounts ranging from 0 to 11. Thus, we need 12 slots in the table:

memo[0]: Minimum coins to make amount 0 (which is 0).
memo[1]: Minimum coins to make amount 1.
...
memo[11]: Minimum coins to make amount 11.
If the table were of size amount (which would be 11 in this case), it would only have slots from 0 to 10, and we wouldn't be able to store the result for the target amount itself.

Correctness
The memoization table of size amount + 1 ensures that:

All Subproblems Are Covered: We can store results for all amounts from 0 up to amount.
Direct Access: We can directly access and update the result for any sub-amount using its value as the index.
*/
int coinChangeSolve(vector<int>& coins, int amount, vector<int>& memo, vector<int>& lastCoin)
{
     if(amount < 0)
       return INT_MAX;
     if(amount == 0)
       return 0;
     if(memo[amount] != -1)
       return memo[amount];

     int minCoins = INT_MAX;
     for(auto c : coins) {
        int tmp = coinChangeSolve(coins, amount - c, memo, lastCoin);
        if (tmp != INT_MAX && tmp + 1 < minCoins) {
            minCoins = tmp + 1;
            lastCoin[amount] = c;  // Track the coin used
        }
     }

     memo[amount] = minCoins;
     return minCoins;
}

std::pair<int, vector<int>> coinChange(vector<int>& coins, int amount)
{ 
   auto memo = vector<int>(amount + 1, -1);
   auto lastCoin = vector<int>(amount + 1, -1);
   vector<int> resultCoins = {};
   auto res = coinChangeSolve(coins, amount, memo, lastCoin);

   // Reconstruct the coins used to form the amount
    int tempAmount = amount;
    while (tempAmount > 0) {
        int coin = lastCoin[tempAmount];
        resultCoins.push_back(coin);
        tempAmount -= coin;
    }

   return std::make_pair(res == INT_MAX ? -1 : res, resultCoins);
}

const int MOD = 1e9 + 7; // Example modulus

int coinAllSolutions(vector<int>& coins, int amount, vector<int>& memo)
{
    if(amount < 0)
      return 0;
    if(amount == 0)
      return 1;
    
    if(memo[amount] != -1)
      return memo[amount];

    int solutions = 0;
    for(auto c : coins)
      solutions += coinAllSolutions(coins, amount - c, memo);

    solutions %= MOD;
    memo[amount] = solutions;
    return solutions;
}