#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>

namespace algorithms::adhoc::bridge
{
    /** https://onlinejudge.org/external/4/462.pdf */
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
    }
}