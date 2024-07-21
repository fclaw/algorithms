#include <vector>
#include <cstdio>
#include <iostream>

namespace algorithms::codeforces
{
    // https://codeforces.com/problemset/problem/1272/C
    int solve_1272_c(std::string s, std::vector<char> xs)
    {
        return 1;
    }

     void submit_1272_c()
     {
         int n, k;
         scanf("%d %d", &n, &k);
         char tmp[n];
         scanf("%s", tmp);
         std::string s(tmp, n);
         std::vector<char> xs(n);
         for (int i = 0; i < k; i++)
           scanf("%c", &xs[i]);
         printf("%d\n", solve_1272_c(s, xs));  
     }
}

