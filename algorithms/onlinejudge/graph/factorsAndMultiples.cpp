
 /*
 ─────────────────────────────────────────────────────────────── 
 🧳 UVa 11159 Factors and Multiples, MIS, but answer is the MCBM,  rt: s
 ───────────────────────────────────────────────────────────────
 */

#include "../debug.h"
#include "../../aux.h"
#include "tools/mcbm.cpp"
#include <bits/stdc++.h>


namespace mcmb = algorithms::onlinejudge::graph::tools::mcmb;


using vi = std::vector<int>;

namespace algorithms::onlinejudge::graph::factors_and_multiples
{
    /** https://onlinejudge.org/external/111/11159.pdf */
    int t_cases, factors_n, multiplies_n;
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
          while_read(factors_n);
          vi factors(factors_n);
          for(int fac = 0; fac < factors_n; ++fac)
            while_read(factors[fac]);
          while_read(multiplies_n);
          vi multiplies(multiplies_n);
          for(int mul = 0; mul < multiplies_n; ++mul)
            while_read(multiplies[mul]);
          
          mcmb::vvi graph(factors_n);
          for(int factor_id = 0; factor_id < factors_n; ++factor_id) {
            for(int multiply_id = 0; multiply_id < multiplies_n; ++multiply_id) {
              int factor = factors[factor_id];
              int multiply = multiplies[multiply_id];
              if(!(multiply % factor)) {
                graph[factor_id].push_back(multiply_id);
              }
            }

          }

          int L_SIZE = factors_n;
          int R_SIZE = multiplies_n;
          mcmb::kuhn kuhn_s(R_SIZE);
          for(int factor_id = 0; factor_id < L_SIZE; ++factor_id) {
            kuhn_s.visited.assign(L_SIZE, false);
            mcmb::try_kuhn(factor_id, graph, kuhn_s);
          }

          dbg(kuhn_s.match);
        }
    }
}