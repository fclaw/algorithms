/*
───────────────────────────────────────────────────────────────
🧳 UVa 11825 Hackers’ Crackdown, https://onlinejudge.org/external/118/11825.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




int get_max_damaged_services(const vvi& network) {
  return 1;
}


namespace algorithms::onlinejudge::advanced_topics::hackers_crackdown
{

    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value()) {
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }
        }

        int N, M, t_case = 1;
        while(stdin_read(N) && N) {
          vvi network(N);
          for(int u = 0; u < N; ++u) {
            stdin_read(M);
            for(int m = 0; m < M; ++m) {
              int v;
              stdin_read(v);
              network[u].push_back(v);
            }
          }
          printf("Case %d: %d\n", t_case++, get_max_damaged_services(network));
        }
    }
}