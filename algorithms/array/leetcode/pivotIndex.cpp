#include <vector>

namespace algorithms::array::leetcode
{
    // https://leetcode.com/problems/find-pivot-index
    int pivotIndex(std::vector<int> xs) 
    {
        int n = xs.size();
        std::vector<int> prefixSum(n);
        prefixSum[0] = xs[0];
        for (int i = 1; i < n; i++)
          prefixSum[i] = prefixSum[i - 1] + xs[i];
        
        int ans = -1;
        int i = 0;
        while(i < n)
        {
            int l = i == 0 ? 0 : prefixSum[i - 1];
            int r = i == n - 1 ? 0 : prefixSum[n - 1] - prefixSum[i];

            if(l == r)
            {
              ans = i;
              break;
            }
            i++;
        }
        return ans;
    }
}