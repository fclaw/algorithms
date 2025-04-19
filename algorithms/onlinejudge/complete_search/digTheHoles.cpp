#include "../debug.h"
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>



namespace algorithms::onlinejudge::complete_search::dig_the_holes
{
    /**  https://onlinejudge.org/external/114/11412.pdf, next permutation, find one possibility from 6!  */
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
    }
}