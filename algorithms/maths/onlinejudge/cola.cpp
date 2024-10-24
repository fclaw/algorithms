#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>

namespace algorithms::maths::onlinejudge::cola
{
    /** https://onlinejudge.org/external/111/11150.pdf */
    // a bottle of Cola for every 3 empty bottles returned
    const int N = 3;
    void maxBottles(int curr, int empty, int borrowed, int& total)
    {
        if(curr == 0) return;
        total += curr;

        if(borrowed > 0)
        { curr -= borrowed; borrowed = 0; }

        empty += (curr % N);
        curr /= N;

        if(curr == 0 && empty > 1)
        {
            while(empty % N != 0)
            { ++empty; ++borrowed; }
        }

        if(curr == 0 && empty >= 3)
        { curr = empty / N; empty = 0; }

        maxBottles(curr, empty, borrowed, total);
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) assert(std::freopen(file.value(), "r", stdin) != nullptr);
        int bottles;
        while(std::cin >> bottles)
        {
            int total = 0;
            maxBottles(bottles, 0, 0, total);
            printf("%d\n", total);
        }
    }
}