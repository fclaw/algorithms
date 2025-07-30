
 /*
 ─────────────────────────────────────────────────────────────── 
 🧳 UVa 11138 Nuts and Bolts, rt: s
 ───────────────────────────────────────────────────────────────
 */

#include "../debug.h"
#include "../../aux.h"
#include "tools/mcbm.cpp"
#include <bits/stdc++.h>


namespace mcmb = algorithms::onlinejudge::graph::tools::mcmb;


namespace algorithms::onlinejudge::graph::nuts_and_bolts
{
    /** https://onlinejudge.org/external/111/11138.pdf */
    int t_cases, n, m, t_case = 1;
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
        
        while_read(t_cases);
        while(t_cases--) {
          while_read(n, m);
          mcmb::vvi graph(n);
          for(int bolt = 0; bolt < n; ++bolt) {
            for(int nut = 0; nut < m; ++nut) {
              int is_paired;
              while_read(is_paired);
              if(is_paired) { 
                graph[bolt].push_back(nut); // bolt j is a pair for nut i
              }
            }
          }

          mcmb::kuhn kuhn_s(m); // apply shift of n to the right set
          int max_matching = 0;
          for(int bolt = 0; bolt < n; ++bolt) {
            kuhn_s.visited.assign(n, false);
            if(mcmb::try_kuhn(bolt, graph, kuhn_s)) {
              max_matching++;
            }
          }
          printf("Case %d: a maximum of %d nuts and bolts can be fitted together\n", t_case++, max_matching);
        }
    }
}