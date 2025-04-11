#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>




typedef std::vector<int> vi;
typedef std::unordered_map<int, int> mii;
typedef std::unordered_map<int, mii> mimiii;


namespace algorithms::onlinejudge::complete_search::cube_rotation
{

    /** https://onlinejudge.org/external/2/253.pdf, try all, similar problem in UVa 11959  */
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);        
    }
}