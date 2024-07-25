#include <vector>
#include <cstdio>
#include <string>
#include <algorithm>
#include <bits/stdc++.h>

using ll = long long;

namespace algorithms::codeforces
{

    enum EVitamins : uint8_t 
    {
      A = 1 << 0,
      B = 1 << 1,
      C = 1 << 2
    };

    //https://codeforces.com/problemset/problem/1042/B
    std::vector<int> memo(8, -1);
    int solve_1042_b(std::vector<std::tuple<int, int>> xs, int mask)
    {
        if(__builtin_popcount(mask) == 3)
          return 0;

        int &sum = memo[mask];
        if(~sum) return memo[mask];

        sum = INT32_MAX;
        for(auto x : xs)
        {
            int cost, d;
            std::tie(cost, d) = x;
            if(d < 3 && !(mask & (1 << d)))
              sum = std::min(sum, cost + solve_1042_b(xs, mask | (1 << d)));

            if(d > 2 && mask != d)
              sum = std::min(sum, cost + solve_1042_b(xs, mask | d));
        }

        return memo[mask] = sum;
    }

     void submit_1042_b()
     {
         int n;
         scanf("%d", &n);
         std::vector<std::tuple<int, int>> xs;
         while(--n >= 0)
         {
            int i;
            std::string s;
            std::cin >> i;
            std::cin >> s;
            int d = 0;
            if(s.size() > 1)
              for(auto t : s)
              {
                if(t == 'A') d |= A;
                else if(t == 'B') d |= B;
                else if(t == 'C') d |= C;
              }
            else
               if(s == "A") d = 0;
               else if(s == "B") d = 1;
               else if(s == "C") d = 2;
    
            xs.push_back({i, d});
         };

         int ans = solve_1042_b(xs, 0);
         printf("%d\n", ans < 0 ? -1 : ans);  
     }
}