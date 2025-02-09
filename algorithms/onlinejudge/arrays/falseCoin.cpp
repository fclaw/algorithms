#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>

namespace algorithms::onlinejudge::arrays::false_coin
{
    /** https://onlinejudge.org/external/6/665.pdf
     * use 1D boolean flags; all coins are initially potential
     * false coins; if ‘=’, all coins on the left and right are not false coins; 
     * if ‘<’ or ‘>’, all coins not on the left and right are not false coins; 
     * check if there is only one candidate false coin left at the end.
     * use 1D boolean flags; all coins are initially potential false coins; 
     * if ‘=’, all coins on the left and right are not false coins; 
     * if ‘<’ or ‘>’, all coins not on the left and right are not false coins; 
     * check if there is only one candidate false coin left at the end  */
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
    }
}