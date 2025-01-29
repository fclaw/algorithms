#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>


namespace algorithms::onlinejudge::easy::relational_operators
{
    // https://onlinejudge.org/external/111/11172.pdf
    
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) assert(std::freopen(file.value(), "r", stdin) != nullptr);
        int tests, x, y;
        std::cin >> tests;
        while(tests--)
        {
            std::cin >> x >> y;
            if(x > y) printf(">\n");
            else if(x < y) printf("<\n");
            else printf("=\n");
        }
    }
}