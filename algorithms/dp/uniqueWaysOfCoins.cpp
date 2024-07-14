#include <vector>
#include <iostream>
#include <iomanip>

using UniqueWaysOfCoinsDp = std::vector<std::vector<int>>;

void printUniqueWaysOfCoinsDp(UniqueWaysOfCoinsDp dp)
{
    for ( const auto &row : dp )
    {
        for ( const auto &s : row ) 
          std::cout << std::setw(5) << s << ' ';
        std::cout << std::endl;
    }
}

namespace algorithms::dp
{
    int uniqueWaysOfCoins(int target, std::vector<int> coins)
    { 
        int n = coins.size();
        UniqueWaysOfCoinsDp dp(target + 1, std::vector<int>(n, 0));
        
        for(int i = 0; i < n; i++)
            dp[0][i] = 1;



        /*
         	Transition function:
            i >= 1: f[i][1] = f[i-1][1]
            i >= 2: f[i][2] = f[i-1][1] + f[i-2][2]
            i >= 3: f[i][3] = f[i-1][1] + f[i-2][2] + f[i-3][3]
            i >= 5: f[i][5] = f[i-1][1] + f[i-2][2] + f[i-3][3] + f[i-5][5]
        */
        for (int t = 1; t <= target; t++)
          for(int c = 0; c < n; c++)
            for (int k = 0; k <= c; k++)
              if(t - coins[k] >= 0)
                dp[t][c] += dp[t - coins[k]][k];

        printUniqueWaysOfCoinsDp(dp);

        return dp[target][n - 1];
    }
}