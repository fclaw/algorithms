#include <cstdio>
#include <vector>
#include <iostream>

namespace algorithms::codeforces
{
    // https://codeforces.com/problemset/problem/617/A
    std::vector<int> moves = {1, 2, 3, 4, 5};
    const int N = 5;
    int solve_617_a(int n)
    {
        int ans = 0;
        int steps_left = n;
        int i = N - 1;
        while(i >= 0)
        {
            ans += steps_left / moves[i];
            int rem = steps_left % moves[i];
            
            if(rem == 0)
              break;

            steps_left = rem;
            i--; 
        }
        return ans;
    }

     void submit_617_a()
     {
         int n;
         scanf("%d", &n);
         printf("%d\n", solve_617_a(n));  
     }
}