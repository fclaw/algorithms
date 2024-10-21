#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>


namespace algorithms::maths::onlinejudge::carry_bit
{
    // https://onlinejudge.org/external/104/10469.pdf
    int add(int x, int y) { return  x ^ y; }

    void submit(std::optional<char*> file)
    {
        if(file.has_value()) assert(std::freopen(file.value(), "r", stdin) != nullptr);
        int x, y;
        while(std::cin >> x >> y) { printf("%d\n", add(x, y)); }
    }
}