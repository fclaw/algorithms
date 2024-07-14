#include <vector>

namespace algorithms::dp
{
    /* count the number of possible (canonical) ways 
      to get value V cents using a list of denominations of n coins. 
      For example 1 above, the answer is 3: {1+1+1+1+1 + 1+1+1+1+1, 5 + 1+1+1+1+1, 5 + 5}.
      Solution: Use these Complete Search recurrence relation: 
      ways(type, value), where value is the same as above 
      but we now have one more parameter type for the index of the coin type that we are currently considering. 
      This second parameter type is important as this solution considers the coin types sequentially. 
      Once we choose to ignore a certain coin type, we should not consider it again to avoid double-counting:
      1. ways(type, 0) = 1 // one way, use nothing
      2. ways(type, <0) = 0 // no way, we cannot reach negative value
      3. ways(n, value) = 0 // no way, we have considered all coin types ∈ [0..n-1]
      4. ways(type, value) = 
         ways(type + 1, value) + <-- if we ignore this coin type
         ways(type, value - coinValue[type]) <-- plus if we use this coin type
    */
    int ways(std::vector<int> coins, int idx, int target)
    {
        int n = coins.size();
        if(idx >= n || target < 0)
          return 0;

        if(target == 0)
          return 1;

        return ways(coins, idx + 1, target) + ways(coins, idx, target - coins[idx]);   
    }

    int waysToCollectTarget(std::vector<int> coins, int target) { return ways(coins, 0, target); }
}