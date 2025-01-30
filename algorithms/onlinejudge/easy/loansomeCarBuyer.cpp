#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>


namespace algorithms::onlinejudge::easy::car_Buyer
{
    // https://onlinejudge.org/external/101/10114.pdf, simulate the process
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
    }
}