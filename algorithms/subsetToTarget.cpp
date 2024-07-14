#include <vector>

namespace algorithms::bits
{
    /*
       Abridged problem statement: 
       Given a list l containing 1 ≤ n ≤ 20 integers, 
       is there a subset of list l that sums to another given integer X?
       We can try all 2 ^ n possible subsets of integers, sum the selected integers for each subset in O(n), 
       and see if the sum of the selected integers equals to X. 
       The overall time complexity is thus O(n × 2 ^ n). 
       For the largest test case when n = 20, this is just 20 × 220 ≈ 21M. 
       This is ‘large’ but still viable (for reason described below).
    */
    bool checkSubsetToTarget(std::vector<int> set, int target)
    {
        int n = set.size();
        bool ans = false;
        for (int i = 0; i < (1 << n); i++)
        {
            int sum = 0;
            for(int j = 0; j < n; j++)
              if(i & (1 << j))
                sum += set[j];
            if(sum == target)
            {
                ans = true;
                break;
            }    
        }
        return ans;
    }
}