#include <cstdio>
#include <vector>

/*
  First, we have to determine the parameters of this problem to be selected to represent distinct states of this problem. 
  There are only two parameters in this problem, n and K. 
  Therefore, there are only 4 possible combinations:
  1. If we do not choose any of them, we cannot represent a state. This option is ignored.
  2. If we choose only n, then we do not know how many numbers ≤ n have been used.
  3. If we choose only K, then we do not know the target sum n.
  4. Therefore, the state of this problem should be represented by a pair (or tuple) (n, K). 
  The order of chosen parameter(s) does not matter, i.e. the pair (K, n) is also OK.
  Next, we have to determine the base case(s). 
  It turns out that this problem is very easy when K = 1.
  Whatever n is, there is only one way to add exactly one number less than or equal to n to get n: Use n itself. 
  There is no other base case for this problem.
  For the general case, we have this recursive formulation which is not too difficult to derive: 
  At state (n,K) where K > 1, we can split n into one number X ∈ [0..n] and n−X,i.e. n = X + (n−X). 
  By doing this, we arrive at the subproblem subproblem(n−X,K−1), 
  i.e. given a number n−X, how many ways can K −1 numbers less than or equal to n−X add up to n − X? We can then sum all these ways.
  These ideas can be written as the following Complete Search recurrence 
    ways(n, K): 
      1. ways(n, 1) = 1
      2. ways(n, K) = S(0, n): ways(n - X, K - 1)
  This problem has overlapping sub-problems. 
  For example, the test case n = 1, K = 3 has overlapping sub-problems: 
  The state (n = 0, K = 1) is reached twice. 
  However, there are only n×K possible states of (n, K). 
  The cost of computing each state is O(n). 
  Thus, the overall time complexity is O(n2 × K). 
  As 1 ≤ n, K ≤ 100, this is feasible. 
  The answer can be found by calling ways(n, K)
*/
namespace algorithms::onlinejudge::dp
{
    int rec(int n, int k, std::vector<std::vector<int>>& memo)
    {
        if(k == 1)
          return 1;
        
        if(memo[n][k] != -1)
          return memo[n][k];

        int acc = 0;
        for (int i = 0; i <= n; i++)
          acc += rec(n - i, k - 1, memo);

        return memo[n][k] = acc % 1000000;
    }

    int dp(int n, int k)
    {
        // answer is in dp[n][k] cell
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(k + 1, 0));

        for (int i = 0; i <= n; i++) // these are the base cases
          dp[i][1] = 1;

        for (int i = 0; i <= n; i++)
          for (int j = 0; j <= k; j++)
            for(int split = 0; split <= n - i; split++)
            {
                dp[i + split][j + 1] += dp[i][j];
                dp[i + split][j + 1] %= 1000000;
            }

        return dp[n][k];
    }

    int countWays(int n, int k)
    {
        std::vector<std::vector<int>> memo(n + 1, std::vector<int>(k + 1, -1));
        return rec(n, k, memo);
    }

    void submit_uva_10943()
    {
        int n, k;
        while(true)
        {
            scanf("%d %d", &n, &k);
            if(n == 0 && k == 0)
              break;
            int ans = countWays(n, k);
            printf("%d\n", ans);
        }
    }
}