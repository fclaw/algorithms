#include "../debug.h"
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>




typedef std::vector<int> vi;


namespace algorithms::onlinejudge::divide_conquer::marble
{
    /** https://onlinejudge.org/external/104/10474.pdf, simple: use sort and then lower bound  */
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        int N, q, c = 1;
        while(std::cin >> N >> q && N && q)
        {
            vi marbles(N);
            for(int i = 0; i < N; i++)
              std::cin >> marbles[i];
            std::sort(marbles.begin(), marbles.end());
            printf("CASE# %d:\n", c++);
            int v;

            while(q--)
            {
                std::cin >> v;
                auto it = std::lower_bound(marbles.begin(), marbles.end(), v);
                if(it == marbles.end())
                  printf("%d not found\n", v);
                else
                {
                    int pos = (int)(it - marbles.begin());
                    marbles[pos] == v ? printf("%d found at %d\n", v, pos + 1) : printf("%d not found\n", v);
                }
            }
        }  
    }
}