#include "../debug.h"
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>






typedef std::vector<int> vi;


// max number of iterations after which the solution ought to be found 
const int IT = 50;


int N;

namespace algorithms::onlinejudge::divide_conquer::monkey
{
    /** https://onlinejudge.org/external/120/12032.pdf, binary search the answer + simulation  */
    bool simulate(const vi& rungs, int k)
    {
        for(int i = 1; i <= N; i++)
        {
            int jump = rungs[i] - rungs[i - 1];
            if(jump > k) return false;      // first check jump > k
            if(jump == k) k--;              // then if exactly k, reduce k
        } 
        return true;
    }
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        int tc, c = 1;
        std::cin >> tc;
        while(tc--)
        {
            std::cin >> N;
            vi rungs(N + 1);
            for(int i = 1; i <= N; i++)
              std::cin >> rungs[i];

            int l = 1, r = rungs.back();

            int k, min_k = INT32_MAX;
            for(int it = 0; it <= IT && l != r; it++)
            {
                k = (l + r) / 2;
                bool canFinish = simulate(rungs, k);
                if(canFinish)
                { min_k = std::min(k, min_k); r = k; }
                else l = k;
            }
            printf("Case %d: %d\n", c++, min_k == INT32_MAX ? r : min_k);
        }
    }
}