#include <vector>

namespace algorithms::dp
{
    // There are N stations ni a route, starting from 0 ot N-1. A train moves from first station 0() to last station (N-1) 
    // in only forward direction. The cost of ticket between any two stations is fixed, 
    // Find the minimum cost of travel from station 0 to station n -1.
    // cost[i][j] is cost of ticket from station i to station .j 
    // Since we are not moving backward, cost [1] [j] does not make any sense when i > j and hence they are all -1. If i == j, 
    // then we are at the same station where we want to go, therefore al the diagonal elements are zeros.
    // objective function: MinCost(i, j) = n
    // MinCost(i, i) = 0 there is no cost charged between the same stations
    // MinCost(i, i) = min(fares(i, i + 1) + MinCost(i + 1, j), MinCost(i, i + 2) + MinCost(2, j), ... , fares(j - 1, j) + MinCost(i, j - 1))
    int minTravelCostDp(std::vector<std::vector<int>> fares)
    {
        int n = fares[0].size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));
      
        for (size_t i = 0; i < n - 1; i++)
          for (size_t j = i + 1; j < n; j++)
            dp[i][j] = fares[i][j];

        // the answer is placed in dp(0, n - 1) cell
        for (size_t start = 0; start <= n - 1; start++)
          for (size_t end = start + 1; end <= n; end++)
            for (size_t k = start + 1; k < end; k++)   
              dp[start][end] = std::min(dp[start][end], dp[start][k] + dp[k][end]);

        return dp[0][n - 1];

    }

    int minTravelCostDpImproved(std::vector<std::vector<int>> fares)
    {
        int n = fares[0].size();
        std::vector<int> dp(n, INT32_MAX);
        dp[0] = 0;
        dp[1] = fares[0][1];

        for (size_t station = 2; station < n; station++)
          for (size_t midpoint = 1; midpoint < station; midpoint++)
            dp[station] = std::min(dp[station], dp[midpoint] + fares[midpoint][station]);

        return dp[n - 1];
    }

    int minTravelCostRecursive(std::vector<std::vector<int>> fares, int from, int to)
    {
        if(from == to || from == to - 1)
          return fares[from][to];
        
        int minCost = fares[from][to];
        for (size_t k = from + 1; k < to; k++)
         minCost = std::min(minCost, minTravelCostRecursive(fares, from, k) + minTravelCostRecursive(fares, k, to));
        return minCost;
    }

    int minTravelCost(std::vector<std::vector<int>> fares) { return minTravelCostDp(fares); }

}