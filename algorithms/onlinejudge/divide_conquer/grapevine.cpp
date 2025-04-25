#include "../debug.h"
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>






typedef std::vector<int> vi;
typedef std::vector<vi> vvi;


// Precompute diagonals (↘ direction)
vvi precomputeDiagonals(const vvi& props, int N, int M) 
{
    vvi diagonals(N + M - 1); // index = r - c + (M - 1)
    for(int r = 0; r < N; ++r)
      for(int c = 0; c < M; ++c) {
          int diag_idx = r - c + (M - 1);
          diagonals[diag_idx].push_back(props[r][c]);
      }
    return diagonals;
}

namespace algorithms::onlinejudge::divide_conquer::grapevine
{
    /** https://onlinejudge.org/external/121/12192.pdf, 
     * the input array has special sorted properties; use lower bound to speed up the search */
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        int N, M;
        while(std::cin >> N >> M and (N or M))
        {
            vvi props(N, vi(M)); // row-wise
            for(int i = 0; i < N; i++)
              for(int j = 0; j < M; j++)
                  std::cin >> props[i][j];

            vvi diagonals = precomputeDiagonals(props, N, M);

            int queries, from, to;
            std::cin >> queries;
            while(queries-- > 0)
            {
                int max_square = 0;
                std::cin >> from >> to;
                for(int r = 0; r < N; r++)
                {
                     auto it = std::lower_bound(props[r].begin(), props[r].end(), from);
                     if(it == props[r].end()) continue;
                     int c = it - props[r].begin();

                     int diag_idx = r - c + (M - 1);
                     const vi& diag = diagonals[diag_idx];

                     auto lw_it = std::lower_bound(diag.begin(), diag.end(), *it);
                     auto up_it = std::upper_bound(diag.begin(), diag.end(), to);
                     int dist = up_it - lw_it;
                     max_square = std::max(max_square, dist);
                }
                std::cout << (max_square != INT32_MIN ? max_square : 0) << std::endl;
            }
            printf("-\n");
        }
    }
}