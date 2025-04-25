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
                  for(int c = 0; c < M; c++)
                    if(props_r[r][c] >= from &&
                       props_c[c][r] <= to)
                    {
                        auto c_it = std::lower_bound(props_r[r].begin() + c, props_r[r].end(), to + 1);
                        if(c_it == props_r[r].end()) 
                          c_it = props_r[r].end() - 1;
                        auto r_it = std::lower_bound(props_c[c].begin() + r, props_c[c].end(), to + 1);
                        if(r_it == props_c[c].end()) 
                          r_it = props_c[c].end() - 1;
                        int c_d = c_it - props_r[r].begin();
                        int r_d = r_it - props_c[c].begin();
                        bool isf = false;
                        int square = 0;
                        for(int shift = std::min(c_d - c, r_d - r); shift >= 0 && !isf; shift--)
                          if (props_r[r + shift][c + shift] <= to &&
                              props_r[r + shift][c + shift] >= from)
                          { square = shift; isf = true; break; }
                        max_square = std::max(max_square, 1 + square);
                        if(isf) break;
                    }
                std::cout << (max_square != INT32_MIN ? max_square : 0) << std::endl;
            }
            printf("-\n");
        }
    }
}