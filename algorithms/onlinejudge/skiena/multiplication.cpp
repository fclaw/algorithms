#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

namespace algorithms::onlinejudge::skiena::multiplication
{
    /** https://onlinejudge.org/external/8/847.pdf 
     * Stan and Ollie play the game of multiplication by multiplying an integer p by one of the numbers 2 to
     * 9. Stan always starts with p = 1, does his multiplication, then Ollie multiplies the number, then Stan
     * and so on. Before a game starts, they draw an integer 1 < n < 4294967295 and the winner is who first
     * reaches p ≥ n. */
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
    }
}