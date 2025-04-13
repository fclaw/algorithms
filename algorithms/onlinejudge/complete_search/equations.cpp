#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include <tuple>



typedef std::vector<std::tuple<int, int, int>> vtiii;


namespace algorithms::onlinejudge::complete_search::equations
{
    /** https://onlinejudge.org/external/115/11565.pdf, 3 nested loops with pruning */
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int tc;
        std::cin >> tc;
        while(tc--)
        {
            int a, b, c;
            scanf("%d %d %d\n", &a, &b, &c);
            
            vtiii solutions;

            //  x + y + z = A
            // xyz = B
            // x ^ 2 + y ^ 2 + z ^ 2 = C
            int l = std::max(a, std::max((int)std::cbrt(b), (int)std::sqrt(c)));
            int s = -l;

            for(int x = s; x <= l; x++)
              for(int y = s; y <= l; y++)
                for(int z = s; z <= l; z++)
                  if((x * y * z == b) &&
                     (x + y + z == a) && 
                     (x * x + y * y + z * z == c) && 
                     x != y && y != z && z != x)  
                    solutions.push_back({x, y, z});
            
            std::sort(solutions.begin(), solutions.end());
            
            if(solutions.empty()) printf("No solution.\n");
            else printf("%d %d %d\n", std::get<0>(solutions.front()), std::get<1>(solutions.front()), std::get<2>(solutions.front()));
        }
    }
}