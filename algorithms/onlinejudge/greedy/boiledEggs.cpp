#include "../debug.h"
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>






typedef long long ll;
typedef std::vector<int> vi;


namespace algorithms::onlinejudge::greedy::boiled_eggs
{
    /** https://onlinejudge.org/external/119/11900.pdf */
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value())
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }

        int tc, c = 1;
        std::cin >> tc;
        while(tc--)
        {
            int N, p, q;
            scanf("%d %d %d\n", &N, &p, &q);
            vi eggs(N);
            for(int i = 0; i < N; i++)
              std::cin >> eggs[i];
           
            // Stopping conditions:
            // 1. We cannot pick more than `p` eggs.
            // 2. The total weight of picked eggs must not exceed `q`.
            // 3. We must not go beyond the available `n` eggs.
            int cnt = 0;
            int weight = 0;
            for(int i = 0; i < N; i++)
              if(weight + eggs[i] <= q && 
                 cnt + 1 <= p)
              { ++cnt; weight += eggs[i]; }
            printf("Case %d: %d\n", c++, cnt);
        }
    }
}