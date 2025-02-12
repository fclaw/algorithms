#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <sstream>
#include <vector>


const int R = 4;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
#define loop(x, s, n) for(int x = s; x < n; x++)

namespace algorithms::onlinejudge::arrays::rotated_squares
{
    // https://onlinejudge.org/external/115/11581.pdf, simulate the process
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
    }
}