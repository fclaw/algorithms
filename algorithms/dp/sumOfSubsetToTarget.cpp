#include <vector>

namespace algorithms::dp
{
    // given an array of non-negative integers and a positive number,
    // determine if there exists a subset with the sum equals to target
    // xs = {3, 2, 7, 1}, target = 6, {3, 2, 1} = 6
    bool sumOfSubsetToTargetRecursive(std::vector<int> xs, int idx, int n)
    {
        if(n == 0)
          return true;
        if(n < 0)
          return false;
        if(idx < 0)
          return false;
        
        bool includeEl = sumOfSubsetToTargetRecursive(xs, idx - 1, n - xs[idx]);
        bool excludeEl = sumOfSubsetToTargetRecursive(xs, idx - 1, n);

        return includeEl || excludeEl;
    }
    // objective function: F(i, n) = F(i + 1, n - xs[i]) || F(i + 1, n)
    // F(i, 0) = true
    // bottom-up manner and store intermediate results in a two dim matrix dp[i][j]. 
    // dp[i][j] id true if there is a subset of arr (0 .. i) with sum qual to j otherwise false. 
    // The final value is in dp[n][target]
    bool sumOfSubsetToTargetDp(std::vector<int> xs, int target)
    {
        return false;
    }
    bool sumOfSubsetToTarget(std::vector<int> xs, int target) { return sumOfSubsetToTargetRecursive(xs, xs.size() - 1, target); }
}