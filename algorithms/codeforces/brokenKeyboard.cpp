#include <vector>
#include <cstdio>
#include <iostream>

namespace algorithms::codeforces
{
    // https://codeforces.com/problemset/problem/1272/C
    int solve_1272_c(std::string s, std::vector<std::string> xs)
    {
        int n = s.size();
        std::vector<int> dp(n, 0);
        for(int i = 0; i < n; i++)
          if(auto j = std::find(xs.begin(), xs.end(), s.substr(i, 1)); j != xs.end()) // O(n * k), considering that k <= 26 complexity remains linear
            dp[i] = 1;

        int f = 0;
        int l = 0;
        int ans = 0;
        while(l < dp.size())
        {
            while(l < dp.size() && dp[l] != 0) l++;
            ans += ((l - f) * (l - f + 1)) / 2;
            f = ++l;
        };

        return ans;
    }

     void submit_1272_c()
     {
         int n, k;
         scanf("%d %d", &n, &k);
         char tmp[n];
         scanf("%s\n", tmp);
         std::string s(tmp, n);
         std::vector<std::string> xs(k);
         for (int i = 0; i < k; i++)
         {
            char tmp[1];
            scanf("%s", tmp);
            xs[i] = std::string(tmp, 1);
         }

         printf("%d\n", solve_1272_c(s, xs));  
     }
}

