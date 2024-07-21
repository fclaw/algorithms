#include <cstdio>
#include <vector>

using ll = long long;

namespace algorithms::codeforces
{
      // https://codeforces.com/problemset/problem/1182/A
      // You have a given integer 𝑛. Find the number of ways to fill all 3 × 𝑛 tiles 
      // with the shape described in the picture below. 
      // Upon filling, no empty spaces are allowed. Shapes cannot overlap
      /*
         Both cases force you to group leftmost 3 × 2
         tiles and fill. By this fact, we should group each 3 × 2
         tiles and fill independently. So the answer is — if 𝑛
         is odd, then the answer is 0 (impossible), otherwise, the answer is 2 ^ (n /2)
         Time complexity is 𝑂(1) with bit operation or 𝑂(𝑛) with iteration.
      */
     ll solve_1182_a(int n) 
     {
          if(n == 2)
            return 2;
          return 2 * solve_1182_a(n - 2);
     }

     ll solve_1182_a_dp(int n)
     {
          std::vector<ll> dp(n + 1, 0);
          dp[2] = 2;
          for(int i = 4; i <= n; i += 2)
            dp[i] = 2 * dp[i - 2];
          return dp[n];
     }

     void submit_1182_a()
     {
         int n;
         scanf("%d", &n);
         if(n % 2 == 1)
           printf("%d", 0);
         else printf("%llu\n", solve_1182_a_dp(n));
     }
}