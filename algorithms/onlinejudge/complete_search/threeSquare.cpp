#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <tuple>
#include <unordered_map>






namespace algorithms::onlinejudge::complete_search::three_square
{
    /** https://onlinejudge.org/external/113/11342.pdf, 
     * pre-calculate squared values from 0 to 224, use
     * 3 nested loops to generate the answers; use map to avoid duplicates */
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        std::unordered_map<int, std::tuple<int, int, int>> targets;
        for(int i = 0; i <= 224; i++)
          for(int j = 0; j <= 224; j++) 
            for(int k = 0; k <= 224; k++)
            {
                int t = i * i + j * j + k * k;
                auto tpl = std::make_tuple(i, j, k);
                if(!targets.count(t) || 
                   (targets.count(t) && 
                    targets.at(t) > tpl))
                  targets[t] = tpl;
            }
  
        int tc;
        std::cin >> tc;
        while(tc--)
        {
            int target;
            std::cin >> target;
            if(targets.count(target))
            {
                auto [a, b, c] = targets.at(target);
                printf("%d %d %d\n", a, b, c);
            } else printf("-1\n");
        }
    }
}