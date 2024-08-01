#include <cstdio>
#include <vector>

namespace algorithms::codeforces
{
    
    int solve_231_a(std::vector<int> xs)
    {
        int ans = 0;
        for(auto x : xs)
          if(x > 4 || x == 3)
            ans += 1;
        return ans;    
    }

    void submit_231_a()
    {
        int n;
        scanf("%d", &n);
        std::vector<int> xs;
        while(--n >= 0)
        {
            int x, y, z;
            int v = 0;
            scanf("%d %d %d", &x, &y, &z);
            if(x == 1)
              v |= (1 << 0);
            if(y == 1)
              v |= (1 << 1);
            if(z == 1)
              v |= (1 << 2);
            xs.push_back(v);
        };
        printf("%d", solve_231_a(xs));
    }
}