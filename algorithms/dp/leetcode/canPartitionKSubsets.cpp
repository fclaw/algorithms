#include <vector>
#include <bitset>
#include <unordered_map>

namespace algorithms::dp::leetcode
{
    /*
      https://leetcode.com/problems/partition-to-k-equal-sum-subsets
      Given an integer array nums and an integer k, 
      return true if it is possible to divide this array 
      into k non-empty subsets whose sums are all equal.
      https://leetcode.com/problems/find-minimum-time-to-finish-all-jobs - has much in common
    */
    const int MAX_LENGTH = 16;
    int SIZE;
    int SIDE_SIZE;
    int K;
    bool dfs(const std::vector<int>& xs, std::bitset<MAX_LENGTH> mask, int side, int c, std::unordered_map<int, bool>& memo)
    {
        if(c == K)
          return true;

        if(side > SIDE_SIZE)
          return false;
        
        if(auto i = memo.find((int)mask.to_ulong()); i != memo.end())
          return (*i).second; 

        bool ans = false;
        for(int i = 0; i < SIZE && !mask.all() && !ans; i++)
        {
            if(mask.test(i)) continue;
            mask.set(i);
            if(side + xs[i] == SIDE_SIZE)
                ans |= memo[(int)mask.to_ulong()] = dfs(xs, mask, 0, c + 1, memo);
            ans |= memo[(int)mask.to_ulong()] = dfs(xs, mask, side + xs[i], c, memo);
            mask.set(i, false);
        }
        return ans;
    }

    bool canPartitionKSubsets(std::vector<int> nums, int k) 
    {
        SIZE = nums.size();
        K = k;
        int perimeter = std::reduce(nums.begin(), nums.end());
        if(SIZE < k || (perimeter % k))
          return false;
        SIDE_SIZE = perimeter / K;
        std::sort(nums.begin(), nums.end(), std::greater<int>());
        std::bitset<MAX_LENGTH> mask;
        std::unordered_map<int, bool> memo;
        return dfs(nums, mask, 0, 0, memo);
    }
}