#include <vector>

namespace algorithms::leetcode::dp
{
    // https://leetcode.com/problems/reducing-dishes
    // chef has collected data on the satisfaction level of his n dishes. Chef can cook any dish in 1 unit of time.
    // Like-time coefficient of a dish is defined 
    // as the time taken to cook that dish including previous dishes 
    // multiplied by its satisfaction level i.e. time[i] * satisfaction[i].
    // Return the maximum sum of like-time coefficient that the chef can obtain after preparing some amount of dishes.
    // Dishes can be prepared in any order and the chef can discard some dishes to get this maximum value.
    int rec(std::vector<int> satisfaction, int first, int last, int ct)
    {
        if(first >= last)
          return 0;

        int ans = 0;
        for (int i = first; i < last; i++)
        {
            int leftToRight = 
               rec(satisfaction, first, i, ct + 1) + 
               rec(satisfaction, i + 1, last, (i - first) * ct);
            int rightToLeft =
               rec(satisfaction, first, i, (last - i - 1) * ct) + 
               rec(satisfaction, i + 1, last, ct + 1);
            ans = std::max(ans, satisfaction[i] * ct + std::max(leftToRight, rightToLeft));
        }
        return ans;
    }

    int maxSatisfaction(std::vector<int> satisfaction) { return rec(satisfaction, 0, satisfaction.size(), 1); }
}