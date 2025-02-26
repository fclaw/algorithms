#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include "../../advanced_ds/unionFind.cpp"


namespace ad = algorithm::advanced_ds;


namespace algorithms::onlinejudge::advanced_ds::war
{
    /** https://onlinejudge.org/external/101/10158.pdf, 
     * advanced usage of disjoint sets with a nice twist; memorize list of enemies */
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
    }
}