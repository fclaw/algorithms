#include "../debug.h"
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>





const double eps = 1e-9;


namespace algorithms::onlinejudge::divide_conquer::solve_it
{
    /** https://onlinejudge.org/external/103/10341.pdf,(bisection method discussed in this section; for alternative
     * solutions, see https://algorithmist.com/wiki/UVa_10341_-_Solve_It  */
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
          
    }
}