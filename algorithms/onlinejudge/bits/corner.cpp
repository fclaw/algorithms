#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <bitset>
#include <cmath>



namespace algorithms::onlinejudge::bits::jollybee
{
    
    /** https://onlinejudge.org/external/102/10264.pdf, heavy bitmask manipulation */
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

    }
}