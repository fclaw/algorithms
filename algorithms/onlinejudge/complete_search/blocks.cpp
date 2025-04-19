#include "../debug.h"
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>



namespace algorithms::onlinejudge::complete_search::blocks
{
    /** https://onlinejudge.org/external/103/10365.pdf, use 3 nested loops with pruning */
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        

        int tc;
        std::cin >> tc;
        while(tc--)
        {
            int cubes;
            std::cin >> cubes;
            int area = INT32_MAX;
            for(int w = 1; w <= cubes; w++)
              for(int l = 1; l <= cubes; l++)
                for(int h = 1; h <= cubes; h++)
                  area = std::min(area, 2 * w * l + 2 * h * w + 2 * h * l);
            std::cout << area << std::endl;  
        }
    }
}