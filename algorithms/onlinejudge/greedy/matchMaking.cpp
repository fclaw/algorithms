#include <cstdio>
#include <vector>
#include <algorithm>
#include <optional>

using arr = std::vector<int>;

namespace algorithms::onlinejudge::greedy
{

    std::optional<std::tuple<int, int>> solve(arr bachelors, arr spinsters) 
    {
         
        return std::nullopt;
    }

    void findMatches()
    {
        int N, M;
        while(true)
        {
            scanf("%d %d", &N, &M);
            if(N == 0 && N == 0)
              break;

            arr bachelors(N);
            arr spinsters(M);
            
            int i = 0;
            while(i < N)
            {
                int x;
                scanf("%d", &x);
                bachelors.push_back(x);
                i++;
            };

            int j = 0;
            while(j < M)
            {
                int x;
                scanf("%d", &x);
                spinsters.push_back(x);
                j++;
            };

            auto ans = solve(bachelors, spinsters);
            if(ans.has_value())
            {
                int f, s;
                std::tie(f, s) = ans.value();
                printf("%d %d", f, s); 
            }
            else printf("%d", 0);
        };
    }
}
