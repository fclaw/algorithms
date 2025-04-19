#include "../debug.h"
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>



namespace algorithms::onlinejudge::complete_search::network
{
    /** https://onlinejudge.org/external/10/1064.pdf, 
     * LA 3808, WorldFinals Tokyo07, permutation of up to 5 messages, simulation, mind the word ‘consecutive’  */
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
    }
}