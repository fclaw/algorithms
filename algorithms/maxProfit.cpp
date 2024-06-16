#include <vector>


namespace leetcode::dp
{
    // https://leetcode.com/problems/best-time-to-buy-and-sell-stock
    /*
      You are given an array prices where prices[i] is the price of a given stock on the ith day.
      You want to maximize your profit by choosing a single day to buy one stock and 
      choosing a different day in the future to sell that stock.
      Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.
      Input: prices = [7,1,5,3,6,4]
      Output: 5
      Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
      Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.
    */
   int maxProfitDp(std::vector<int>& prices, int day, std::vector<int>& memo)
   {
        int n = prices.size();
        if(day == n - 2)
          return prices[n - 1] - prices[day];

        if(memo[day] != -1)
          return memo[day];

        auto nextDayProfit = maxProfitDp(prices, day + 1, memo);

        int localMax = 0; 
        for (size_t i = day + 1; i < n; i++)
          localMax = std::max(localMax, prices[i] - prices[day]);

        auto res = std::max(nextDayProfit, localMax);
        memo[day] = res;
        return res;
   }
    int maxProfit(std::vector<int>& prices) 
    {
        if(prices.size() < 2)
          return 0;
      std::vector<int> memo(prices.size() + 1, -1); 
      return maxProfitDp(prices, 0, memo) < 0 ? 0 : maxProfitDp(prices, 0, memo); 
    }
}