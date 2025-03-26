#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>



namespace algorithms::onlinejudge::complete_search::bishop
{
    /** https://onlinejudge.org/external/8/861.pdf, 
     * backtracking with pruning as in 8-queens recursive backtracking solution; 
     * then pre-calculate the results  */
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
    }
}