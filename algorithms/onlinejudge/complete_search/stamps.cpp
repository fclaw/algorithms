#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>



namespace algorithms::onlinejudge::complete_search::stamps
{
    /** https://onlinejudge.org/external/1/165.pdf, requires some DP too; can be pre-calculated */
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
    }
}