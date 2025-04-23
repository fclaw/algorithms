#include "../debug.h"
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>





typedef std::vector<int> vi;

namespace algorithms::onlinejudge::divide_conquer::balls
{
    /** https://onlinejudge.org/external/6/679.pdf, binary search */
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int tc;
        std::cin >> tc;
        while(tc--)
        {
            int depth, drop;
            std::cin >> depth >> drop;

            int it = 1, d = 1;
            --drop;
            while(drop)
            {
                if(!(drop % 2)) it *= 2;
                else it = 2 * it + 1;
                drop /= 2;
                d++;
            }

            while(d++ != depth) it *= 2;
            std::cout << it << std::endl;
        }
        int garbage;
        std::cin >> garbage;
    }
}