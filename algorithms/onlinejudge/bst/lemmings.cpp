#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>


namespace algorithms::onlinejudge::bst::lemmings
{
    // https://onlinejudge.org/external/9/978.pdf
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) assert(std::freopen(file.value(), "r", stdin) != nullptr);

    }
}