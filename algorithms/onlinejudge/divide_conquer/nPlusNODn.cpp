#include "../debug.h"
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>






typedef std::vector<int> vi;

const int MAX_VAL = 1000000;


namespace algorithms::onlinejudge::divide_conquer::n_plus_node_n
{
    /** https://onlinejudge.org/external/118/11876.pdf, [lower|upper] bound on sorted sequence N */
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        vi divCount(MAX_VAL + 1, 1); // Every number has at least 1 (itself)

        for(int i = 2; i <= MAX_VAL; ++i)
          for(int j = i; j <= MAX_VAL; j += i)
            divCount[j]++; // i divides j

        vi seq(MAX_VAL + 1);
        seq[0] = 1;
        for(int n = 1; n < MAX_VAL; n++)
          seq[n] = seq[n - 1] + divCount[seq[n - 1]];
        
        int tc, c = 1;
        std::cin >> tc;
        while(tc--)
        {
            int first, second;
            std::cin >> first >> second;
            auto f_it = std::lower_bound(seq.begin(), seq.end(), first);
            auto s_it = std::upper_bound(seq.begin(), seq.end(), second);
            printf("Case %d: %d\n", c++, (int)(s_it - f_it));
        }
    }
}