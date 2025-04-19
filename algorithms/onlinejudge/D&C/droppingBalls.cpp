#include "../debug.h"
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>



namespace algorithms::onlinejudge::divide_and_conquer::dropping_balls
{
    /**   */
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
    }
}