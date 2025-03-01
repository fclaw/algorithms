#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>



namespace algorithms::onlinejudge::complete_search::string_popping
{
    /** https://onlinejudge.org/external/12/1261.pdf, 
     * a simple backtracking problem; 
     * but we use a set<string>to prevent the same state (a substring) from being checked twice) */
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
    }
}