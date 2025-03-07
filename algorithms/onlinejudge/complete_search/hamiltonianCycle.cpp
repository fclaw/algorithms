#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>



namespace algorithms::onlinejudge::complete_search::hamiltonian_cycle
{
    /** https://onlinejudge.org/external/7/775.pdf, 
     backtracking suﬃces because the search space cannot be that big; 
     in a dense graph, it is more likely to have a Hamiltonian cycle, so we can prune early; 
     we do NOT have to find the best one like in TSP problem */
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
    }
}