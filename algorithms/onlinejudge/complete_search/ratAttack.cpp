#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>






typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<std::tuple<int, int, int>> vtiii;



namespace algorithms::onlinejudge::complete_search::rat_attack
{
    /**  https://onlinejudge.org/external/103/10360.pdf, also solvable using 10242 DP max sum  */
    const int SIZE = 1025;
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int tc;
        std::cin >> tc;
        while(tc--)
        {
            int d, N;
            vtiii rats;
            scanf("%d\n%d\n", &d, &N);
            for(int i = 0; i < N; i++)
            {
                int x, y, p;
                scanf("%d %d %d\n", &x, &y, &p);
                rats.push_back({x, y, p});
            }

            vvi killed(SIZE, vi(SIZE, 0));
            for(auto r : rats) // 20 0000
            {
                int x, y, p;
                std::tie(x, y, p) = r;
                int start_x = x - d < 0 ? x : x - d;
                int start_y = y - d < 0 ? y : y - d;
                int up_i = std::min(x + d, SIZE - 1);
                int up_j = std::min(y + d, SIZE - 1);
                for(int i = start_x; i <= up_i; i++)
                  for(int j = start_y; j <= up_j; j++)
                    killed[i][j] += p;
            }

            int x, y, max_killed = INT32_MIN;
            for(int i = 0; i < SIZE; i++)
              for(int j = 0; j < SIZE; j++)
                if(killed[i][j] > max_killed)
                { max_killed = killed[i][j]; x = i; y = j; }
            printf("%d %d %d\n", x, y, max_killed);
        }  
    }
}