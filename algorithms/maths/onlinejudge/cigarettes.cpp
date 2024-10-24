#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>

namespace algorithms::maths::onlinejudge::cigarettes
{
    int BUTTS;
    void maxCigarettes(int curr, int& total)
    {
        int smoked = BUTTS * (curr / BUTTS);
        if(smoked == 0)
        {
            total += curr;
            return;
        }
        
        total += smoked;
        int left = curr % BUTTS;
        curr = curr / BUTTS + left;
        maxCigarettes(curr, total);
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) assert(std::freopen(file.value(), "r", stdin) != nullptr);
        int c, b;
        while(std::cin >> c >> b)
        {
            int total = 0;
            BUTTS = b;
            maxCigarettes(c, total);
            printf("%d\n", total);
        }
    }
}