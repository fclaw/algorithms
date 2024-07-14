#include <cstdio>
#include <vector>

namespace algorithms::codeforces
{
    // https://codeforces.com/contest/1469/problem/B
    int restoreMax([[maybe_unused]] std::vector<int> xs, [[maybe_unused]] std::vector<int> ys)
    {
        return 0;
    }

     void submit_1469_B()
     {
        int TC;
        scanf("%d", &TC);
        while(--TC >= 0)
        {
            int n, m;
            scanf("%d", &n);
            std::vector<int> reds(n);
            for (int i = 0; i < n; i++)
              scanf("%d", &reds[i]);

            scanf("%d", &m);
            std::vector<int> blues(m);
            for (int i = 0; i < m; i++)
              scanf("%d", &blues[i]);  
            
            printf("%d\n", restoreMax(reds, blues));
        }
     }
}