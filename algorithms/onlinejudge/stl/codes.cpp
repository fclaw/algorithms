#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <sstream>
#include <vector>
#include <algorithm>


const std::string Terminate = "#";

namespace algorithms::onlinejudge::stl::codes
{
    // https://onlinejudge.org/external/1/146.pdf, use next permutation
    bool getNextCode(std::string& code) 
    { return std::next_permutation(code.begin(), code.end()); }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        std::string code;
        while(true)
        {
            std::cin >> code;
            if(code == Terminate) break;
            bool ok = getNextCode(code);
            std::cout << (ok ? code : "No Successor") << std::endl;
        }
    }
}