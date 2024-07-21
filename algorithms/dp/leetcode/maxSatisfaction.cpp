#include <vector>
#include <iostream>

namespace algorithms::leetcode::dp
{
    // https://leetcode.com/problems/reducing-dishes
    // chef has collected data on the satisfaction level of his n dishes. Chef can cook any dish in 1 unit of time.
    // Like-time coefficient of a dish is defined 
    // as the time taken to cook that dish including previous dishes 
    // multiplied by its satisfaction level i.e. time[i] * satisfaction[i].
    // Return the maximum sum of like-time coefficient that the chef can obtain after preparing some amount of dishes.
    // Dishes can be prepared in any order and the chef can discard some dishes to get this maximum value.
    int maxSatisfaction(std::vector<int> xs) 
    { 
        int n = xs.size();
        std::sort(xs.begin(), xs.end());

        int ans = 0;
        int idx = 0;
        while(idx < n && xs[idx] < 0)
          idx++; 
        
        int i = idx;
        int coeff = 1;
        while(i < n)
        {
            ans += coeff * xs[i];
            coeff++;
            i++;
        };

        int j = idx - 1;
        while(j >= 0)
        {
            int tmp = 0;
            int coeff = 1;
            for(int k = j; k < n; k++)
              tmp += coeff++ * xs[k];

            if(tmp > ans)
              ans = tmp;

            if(tmp < 0)
              break;

            j--;  
        };

        return ans;
    }
}