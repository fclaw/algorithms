#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <sstream>
#include <vector>
#include <algorithm>



namespace algorithms::onlinejudge::stl::scoreboard
{
    // https://onlinejudge.org/external/102/10258.pdf, multi-fields sorting, use sort
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
    }
}