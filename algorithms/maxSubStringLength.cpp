#include <string>
#include <vector>

namespace algorithms::dp
{
    int maxSubStringLength(std::string s)
    {
        int n = s.size();
        // S(i, j) = n
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));

        // init Lower diagonal of matrix is not used
        // as for the diagonal elements they are filled with their value in the original string dp[i][i] = s[i]
        for (size_t i = 0; i < n; i++)
          dp[i][i] = s[i] - '0';
        
        int maxLength = 0;

        for (int l = 2; l <= n; l++)
          for (int left = 0; left < n - l + 1; left++)
          {
              int right = left + l - 1;
              int m = l / 2;
              int left_half = dp[left][right - m];
              int right_half = dp[right - m + 1][right];
              dp[left][right] = left_half + right_half;
              if(l%2 == 0 && right_half == left_half)
                maxLength = std::max(maxLength, l);
          }
   
        return maxLength; // result
    }
}