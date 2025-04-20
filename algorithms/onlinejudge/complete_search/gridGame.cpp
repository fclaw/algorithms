#include "../debug.h"
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>




typedef std::vector<int> vi;
typedef std::vector<vi> vvi;


namespace algorithms::onlinejudge::complete_search::grid_game
{
    /** https://onlinejudge.org/external/115/11553.pdf, solve by trying all n! permutations  */
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        
        int tc;
        std::cin >> tc;
        while(tc--)
        {
            int D;
            std::cin >> D;
            vvi grid(D, vi(D));
            for(int i = 0; i < D; i++)
              for(int j = 0; j < D; j++)
                std::cin >> grid[i][j];

            vi rows(D);
            std::iota(rows.begin(), rows.end(), 0);

            int win = INT32_MAX, lose = INT32_MIN;
            do
            {
                int sum = 0;
                for(int i = 0; i < D; i++)
                  sum += grid[rows[i]][i];
                if(sum >= 0) win = std::min(win, sum);
                if(sum < 0) lose = std::max(lose, std::abs(sum));
            } while (std::next_permutation(rows.begin(), rows.end()));
            
            std::cout << (lose != INT32_MIN ? -lose : win) << std::endl;
        }
    }
}