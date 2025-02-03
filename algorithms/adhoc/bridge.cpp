#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>

namespace algorithms::adhoc::bridge
{
    /** https://onlinejudge.org/external/4/462.pdf */
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        int n;
        while(std::cin >> n && (bool)n)
        {
            vd expenses = vd(n, 0);
            double e;
            for(int i = 0; i < n; i++)
            {
                std::cin >> e;
                expenses[i] = e;
            }
            double ans = makeEqual(expenses);
            printf("$%.2f\n", ans);
        } 
    }
}