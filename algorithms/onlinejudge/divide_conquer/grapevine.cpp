#include "../debug.h"
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>






typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

namespace algorithms::onlinejudge::divide_conquer::grapevine
{
    /** https://onlinejudge.org/external/121/12192.pdf, 
     * the input array has special sorted properties; use lower bound to speed up the search */
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        int N, M;
        while(scanf("%d %d", &N, &M), N || M)
        {
            vvi props_r(N, vi(M)); // row-wise
            vvi props_c(M, vi(N)); // col-wise
            for(int i = 0; i < N; i++)
              for(int j = 0; j < M; j++)
              {
                  std::cin >> props_r[i][j];
                  // fill col-wise simultaneously
                  props_c[j][i] = props_r[i][j];
              }

            int queries, from, to;
            std::cin >> queries;
            while(queries-- > 0)
            {
                int max_square = 0;
                std::cin >> from >> to;
                for(int r = 0; r < N; r++)
                {
                     auto lw_it = std::lower_bound(props_r[r].begin(), props_r[r].end(), from);
                     if(lw_it == props_r[r].end()) continue;
                     auto up_it = std::upper_bound(props_r[r].begin(), props_r[r].end(), to);
                     if(up_it == props_r[r].end()) 
                       up_it = props_r[r].end() - 1;
                     int c_side = up_it - lw_it;
                     int c = lw_it - props_r[r].begin();
                     auto up_r_it = std::upper_bound(props_c[c].begin(), props_c[c].end(), to);
                     if(up_r_it == props_c[c].end()) 
                       up_r_it = props_c[c].end() - 1;
                     int r_side = (up_r_it - props_c[c].begin()) - r;
                     int s = std::min(c_side, r_side);
                     for(int shift = s; shift >= 0; --shift)
                       if(props_r[r + shift][c + shift] <= to)
                       { max_square = std::max(max_square, 1 + shift);  break; }
                }
                std::cout << (max_square != INT32_MIN ? max_square : 0) << std::endl;
            }
            printf("-\n");
        }
    }
}